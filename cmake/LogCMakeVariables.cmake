###############################################################################
# Print ALL Cmake variables
#      - can be used for debugging purposes
#      - generates a lot of output data
###############################################################################
macro(print_all_variables)
    message(STATUS " ${PROJECT_NAME}  |  print_all_variables ----------------------------------------")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS " ${PROJECT_NAME}  |     > ${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS " ${PROJECT_NAME}  |  print_all_variables ----------------------------------------")
endmacro()

###############################################################################
# Print only some part of project specific variables
#      - -DLOG_CMAKE_VARIABLES=ON must be passed
###############################################################################
macro(print_project_variables)
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
endmacro()