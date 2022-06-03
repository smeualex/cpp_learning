# ------------------------------------------------------------------------
# TO DO LIST:
#     1. Fix copy_binary_dir for BIPS
#     2. Add CTest and CPack steps
#     3. Add possibility to add via cmd line CMake options
#         build.py build --cmake_opts "-DRUN_TESTS=on -DRUN_CPPCHECK=off"
# ------------------------------------------------------------------------
import os
import sys
import logging
import datetime
import argparse
import platform

from subprocess import Popen, PIPE, STDOUT
from shutil import rmtree, copytree

os_name = platform.system();
log = logging.getLogger('build.py')
cwd = os.path.dirname(os.path.realpath(__file__))

'''
Build options for the CMake build generator
Only change these here

!!!! Arguments need to be escaped correctly !!!!

Important Notes:
    1. If the script is executed in a Linux VM and the source directory
    is shared from a Windows host change the build directory to any 
    directory inside the VM to support symlinks.

    If simlinks are not generated the build directory can be ok as a 
    subdirectory of the shared folder residing in the Host system

    2. Leaving the `generator` empty will use the default Compiler on your system
'''

build_options = {
        'Windows': {
            'arch': 'Win32',
            'config': 'Release',
            'generator': '',
            'source-dir': '.',
            'build-dir': 'build' + os.path.sep + 'arch' + os.path.sep + 'config',
            'log-cmake-variables': 'ON'
        },
        'Linux': {
            'arch': 'i386',
            'config': 'Release',
            'generator': '"Unix Makefiles"',
            'source-dir': '/vagrant',
            'build-dir': 'build' + os.path.sep + 'arch' + os.path.sep + 'config',
            'log-cmake-variables': 'ON'
        },
    }

'''
Supported build arch list.
Used in Linux cross-compilation.
'''
ARCH_LIST=['i386', 'i486', 'i586', 'i686', 'armhf']

def set_build_directory():
    '''
    Creates the final build directory.
    Can use already defined keys from the `build_options` directory.
    Replaces any other key found in the `build_options` dictionary with its value except `build-dir`.
    '''
    components = build_options[os_name]['build-dir'].split(os.path.sep)
    replaced_components = []

    for c in components:
        if c != 'build-dir' and c in build_options[os_name]:
            replaced_components.append(build_options[os_name][c])
        else:
            replaced_components.append(c)

    build_options[os_name]['build-dir'] = os.path.sep.join( [str(c) for c in replaced_components] )

def run_process(cmd, is_test_run=False):
    rc = 0

    if not is_test_run:
        if os_name == 'Linux':
            local_cmd = ' '.join(cmd)
        else:
            local_cmd = cmd
        log.info('  > Running command: {}'.format(' '.join(cmd)))

        # rc = subprocess.check_call(local_cmd, stderr=subprocess.STDOUT, shell=True)
        p = Popen(local_cmd, 
            stdout = PIPE, stderr = STDOUT,
            shell = True,
            bufsize = 1,
            universal_newlines=True)
        
        # get the process' output and log it
        while p.poll() is None:
            line = p.stdout.readline().strip()
            log.info(line)
        p.stdout.close()
        p.wait()
    else:
        log.info('  > TEST - Running command: {}'.format(' '.join(cmd)))

    return rc

def cmake_configure(args):
    configCmd = [
        'cmake', 
        '-S', build_options[os_name]['source-dir'],
        '-B', build_options[os_name]['build-dir'],
        '-DCMAKE_BUILD_TYPE='    + build_options[os_name]['config'],
        '-DLOG_CMAKE_VARIABLES=' + build_options[os_name]['log-cmake-variables']
    ]

    if  build_options[os_name]['generator'] != '' :
        configCmd.extend(['-G', build_options[os_name]['generator']])

    # on Windows use the architecture parameter
    if(os_name == 'Windows'):
        configCmd.extend(['-A', build_options[os_name]['arch']])

    # set the toolchain file if it's set through cmd parameters
    # '-DCMAKE_TOOLCHAIN_FILE=/mnt/cmake/toolchains/linux-armhf-gcc8.cmake'
    if args.toolchain != None:
        configCmd.append('-DCMAKE_TOOLCHAIN_FILE='+args.toolchain.name)

    log.info('-- Configuring project: ')
    rc = run_process(configCmd, args.test_run)

def cmake_build(args):
    buildCmd = [
        'cmake', 
        '--build',  build_options[os_name]['build-dir'],
        '--config', build_options[os_name]['config']
    ]

    if(args.clean != None):
        if(args.clean == True):
            buildCmd.append('--clean-first')

    log.info('-- Building project: ')
    rc = run_process(buildCmd, args.test_run)

def copy_binary_dir():
    '''
    Copy binary output to a common /bin folder
    The destination folder is: /bin/[config]/[arch]
    '''
    if(os_name == 'Windows'):
        # TODO: fix for BIPS
        # on Windows system we run the script directly
        src_dir = os.path.join(cwd, build_options[os_name]['build-dir'], 'bin')
        dst_dir = os.path.join(cwd, 'bin', build_options[os_name]['config'], build_options[os_name]['arch'])
    elif(os_name == 'Linux'):
        # on Linux system it's called 
        src_dir = os.path.join(build_options[os_name]['build-dir'], 'bin')
        dst_dir = os.path.join('/mnt', 'bin', build_options[os_name]['config'], build_options[os_name]['arch'])
    
    log.info('Copying binary output:')
    log.info('  > SRC: {}'.format(src_dir))
    log.info('  > DST: {}'.format(dst_dir))

    try:
        copytree(src_dir, dst_dir)
    except OSError as e:
        log.error("Error: %s : %s" % 
            (build_options[os_name]['build-dir'],
             e.strerror))

def build(args):
    log.info('Starting build')
    log.info('Build options: ')
    log.info(build_options[os_name])

    cmake_configure(args)
    cmake_build(args)

    #  not needed - if we set up a runtime folder
    # copy_binary_dir()

def delete_build_dir():
    try:
        log.info('Deleting the current build directory: {}'
            .format(build_options[os_name]['build-dir']))
        rmtree(build_options[os_name]['build-dir'])
    except OSError as e:
        log.error("Error: %s : %s" % 
            (build_options[os_name]['build-dir'],
             e.strerror))

def init_argparse() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        usage='%(prog)s [OPTIONS]',
        description='Build script.'
    )

    parser.add_argument('cmd', 
        choices=['build', 'rebuild', 'delete-all'],
        help='Choose one of the commands to perform'
    )

    parser.add_argument(
        '-v', '--version', action='version',
        version=f'{parser.prog} version 1.0.0'
    )
    
    parser.add_argument(
        '--toolchain',
        type=open,
        help='CMake toolchain file for cross compilation'
    )

    parser.add_argument(
        '-t', '--test_run',
        action='store_true',
        help='Generate and print the commands. Do not actually run them'
    )

    parser.add_argument(
        '-c', '--clean',
        action='store_true',
        help='Clean the build first. Run cmake with `--clean-first`'
    )

    parser.add_argument(
        '-a', '--arch',
        type=str,
        help='Build architecture. Overrides default value. Accepted values: i686, armhf'
    )

    parser.add_argument(
        '-b', '--build_dir',
        type=str,
        help='Build directory. Overrides default value.'
    )

    parser.add_argument(
        '-s', '--source_dir',
        type=str,
        help='Source directory. Overrides default value.'
    )


    return parser

def init_logging():
    # set up logging
    now = datetime.datetime.now()
    str_now = now.strftime('%Y%m%d_%H%M%S')
    if os_name == 'Windows':
        log_suffix = 'WIN'
    elif os_name == 'Linux':
        log_suffix = 'LNX'

    # log_file_name = str_now + '_build_' + log_suffix + \
    #     '_' + build_options[os_name]['arch'] + '.log'

    log_file_name = 'build_log__' + build_options[os_name]['arch'] + '.log'

    log_file = os.path.join(cwd, log_file_name)
    logging.basicConfig(
            handlers=[
                    logging.FileHandler(log_file, 'w', 'utf-8'),
                    logging.StreamHandler(sys.stdout)
                ],
            level=logging.DEBUG,
            format='%(asctime)s | %(levelname)5.5s | %(name)10s | %(message)s')

def cd_to_script_location():
    log.info('-- cd into the script\'s location: ' + cwd)
    os.chdir(cwd)

def parse_arguments():
    try:
        parser = init_argparse()
        args = parser.parse_args()
    except FileNotFoundError as e:
        log.info(' -- ERROR : {}'.format(e) )
        exit(1)

    if args.arch != None:
        if  args.arch not in ARCH_LIST:
            log.error('Unsupported architecture: {}'.format(args.arch))
            exit(2)
    
        log.info('Replacing default arch value with cmd line param')
        log.info('  CURRENT VAL: {}'.format(build_options[os_name]['arch']))
        log.info('      CMD VAL: {}'.format(args.arch))
        build_options[os_name]['arch'] = args.arch
    
    if args.build_dir != None:
        log.info('Replacing default build-dir value with cmd line param')
        log.info('  CURRENT VAL: {}'.format(build_options[os_name]['build-dir']))
        log.info('      CMD VAL: {}'.format(args.build_dir))
        build_options[os_name]['build-dir'] = args.build_dir
    
    if args.source_dir != None:
        log.info('Replacing default source-dir value with cmd line param')
        log.info('  CURRENT VAL: {}'.format(build_options[os_name]['source-dir']))
        log.info('      CMD VAL: {}'.format(args.source_dir))
        build_options[os_name]['source-dir'] = args.source_dir

    return args

def main(args):
    if args.cmd == 'delete-all':
        delete_build_dir()

    elif args.cmd == 'build':
        set_build_directory()
        build(args)

        if args.toolchain != None:
            args.toolchain.close()

if __name__ == "__main__":
    cd_to_script_location()
    args = parse_arguments()
    init_logging()
    # we are going
    log.info('')
    log.info('')
    log.info('-' * 80)
    log.info('-- Program started')
    log.info('-- OS: {}'.format(os_name))
    
    main(args)
    
    log.info('')
    log.info('-- Program ended')
    log.info('-' * 80)
    log.info('')
    log.info('')