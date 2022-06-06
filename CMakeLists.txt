cmake_minimum_required(VERSION 3.11)

project(stl_learning VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
if(LOG_CMAKE_VARIABLES)
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_MODULE_PATH              = " ${CMAKE_MODULE_PATH})
endif()

include(CMakeInclude)
include(LogCMakeVariables)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

print_options()

if(LOG_CMAKE_VARIABLES)
    message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> GENERAL VARIABLES OUTPUT <<<<<")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> project: ${PROJECT_NAME} ")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> version: ${PROJECT_VERSION} ")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> os:      ${CMAKE_SYSTEM_NAME} ")
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    PROJECT_BINARY_DIR              = " ${PROJECT_BINARY_DIR})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    GLOBAL_OUTPUT_PATH              = " ${GLOBAL_OUTPUT_PATH})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_SOURCE_DIR                = " ${CMAKE_SOURCE_DIR})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_RUNTIME_OUTPUT_DIRECTORY  = " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_LIBRARY_OUTPUT_DIRECTORY  = " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_ARCHIVE_OUTPUT_DIRECTORY  = " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    bips_BINARY_DIR                 = " ${bips_BINARY_DIR})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    libCommon_BINARY_DIR            = " ${libCommon_BINARY_DIR})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_CROSSCOMPILING            = " ${CMAKE_CROSSCOMPILING})
    message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
    message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> OS SPECIFIC VARIABLES")
    message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_STATIC_LIBRARY_PREFIX            = " ${CMAKE_STATIC_LIBRARY_PREFIX})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_STATIC_LIBRARY_SUFFIX            = " ${CMAKE_STATIC_LIBRARY_SUFFIX})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_SHARED_LIBRARY_PREFIX            = " ${CMAKE_SHARED_LIBRARY_PREFIX})
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_SHARED_LIBRARY_SUFFIX            = " ${CMAKE_SHARED_LIBRARY_SUFFIX})
    message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
    message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_VS_PLATFORM_NAME                 = " ${CMAKE_VS_PLATFORM_NAME})
    message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
    message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
endif()
#print_all_variables()


# clear the output directory
# remove the executables and the generated PDBs
file(GLOB_RECURSE EXECUTABLES_TO_CLEAN 
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/**/*.exe
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/**/*.pdb)

file (REMOVE
    ${EXECUTABLES_TO_CLEAN}
)

# add subdirectories
add_subdirectory(examples)