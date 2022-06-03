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
macro(print_project_specific_variables)
    if(LOG_CMAKE_VARIABLES)
        message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
        message(STATUS " ${PROJECT_NAME}  |  >>>>> PROJECT SPECIFIC VARIABLES")
        message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
        message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_CURRENT_LIST_DIR     = " ${CMAKE_CURRENT_LIST_DIR})
        message(STATUS " ${PROJECT_NAME}  |  >>>>>    CMAKE_CURRENT_SOURCE_DIR   = " ${CMAKE_CURRENT_SOURCE_DIR})
        message(STATUS " ${PROJECT_NAME}  |  >>>>>    PROJECT_SOURCE_DIR         = " ${PROJECT_SOURCE_DIR})
        message(STATUS " ${PROJECT_NAME}  |  >>>>> ")
        message(STATUS " ${PROJECT_NAME}  |  ---------------------------------------------------------------------")
    endif()
endmacro()