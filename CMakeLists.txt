cmake_minimum_required(VERSION 3.11)

project(cpp_learning VERSION 1.1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH 
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

include(CMakeInclude)
include(LogCMakeVariables)

# log options and variables
print_options()
print_project_variables()

# Only for extreme cases - prints out a lot of stuff
# print_all_variables()

# clear the output directory
# remove the executables and the generated PDBs
file(GLOB_RECURSE EXECUTABLES_TO_CLEAN 
    bin/**/*.exe
    bin/**/*.pdb)

if(EXECUTABLES_TO_CLEAN)
    file (REMOVE
        ${EXECUTABLES_TO_CLEAN}
    )
endif()

# add subdirectories to the build
add_subdirectory(std)
add_subdirectory(design_patterns)
add_subdirectory(algorithms)
add_subdirectory(codility_lessons)
add_subdirectory(data_structures)