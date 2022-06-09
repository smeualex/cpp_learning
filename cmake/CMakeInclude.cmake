set(PROJECT_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installs/${PROJECT_NAME}-${PROJECT_VERSION}")

if(NOT CMAKE_BUILD_TYPE)
    if($ENV{CONFIG})
        set(CMAKE_BUILD_TYPE $ENV{CONFIG})
    message("  ${PROJECT_NAME}  | ## CMAKE_BUILD_TYPE not specified, setting to env. var. CONFIG - ${CMAKE_BUILD_TYPE}.")
    else()
        set(CMAKE_BUILD_TYPE Release)
        message(WARN "  ${PROJECT_NAME}  | ## CMAKE_BUILD_TYPE not specified. Setting to default value - `Release`")
    endif()
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

###############################################################################
# Build options
###############################################################################
option( LOG_CMAKE_VARIABLES "Log cmake variables"                         OFF )
option( BUILD_TESTS         "Build unit tests."                           OFF )
option( RUN_ALL_TESTS       "Run all tests sepparately"                   OFF )
option( RUN_CPPCHECK        "Run Cppcheck static analysis on all sources" OFF )
option( VERBOSE_OUTPUT      "Log verbose build information"               OFF )

# set common runtime output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# set verbose makefile to see the actual build commands sent to the compiler
set(CMAKE_VERBOSE_MAKEFILE on)

###############################################################################
# Log all build options
###############################################################################
macro(print_options)
	message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
	message(STATUS " ${PROJECT_NAME}  |  >>>>> CMake Build Options")
	message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
	message(STATUS " ${PROJECT_NAME}  |  >>>>>    LOG_CMAKE_VARIABLES = " ${LOG_CMAKE_VARIABLES})
	message(STATUS " ${PROJECT_NAME}  |  >>>>>    BUILD_TESTS         = " ${BUILD_TESTS})
	message(STATUS " ${PROJECT_NAME}  |  >>>>>    RUN_ALL_TESTS       = " ${RUN_ALL_TESTS})
	message(STATUS " ${PROJECT_NAME}  |  >>>>>    RUN_CPPCHECK        = " ${RUN_CPPCHECK})
	message(STATUS " ${PROJECT_NAME}  |  >>>>>    DEV_BUILD           = " ${DEV_BUILD})
	message(STATUS " ${PROJECT_NAME}  |  >>>>>    VERBOSE_OUTPUT      = " ${VERBOSE_OUTPUT})
	message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
	message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
endmacro()

