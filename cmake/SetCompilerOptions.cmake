###############################################################################
# SET COMPILER OPTIONS
###############################################################################
if(WIN32)
    
# enable /std:c++latest for MSVC 2015 - v140 toolset
    if (MSVC_VERSION EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            if(${VERBOSE_OUTPUT})
                message(STATUS " ${PROJECT_NAME}  | MSVC 2015 - Enabling '/std::c++latest' compiler options")
            endif()
            add_compile_options("/std:c++latest")
        endif()
    endif()

    # enable parallel build
    if(${VERBOSE_OUTPUT})
        message(STATUS " ${PROJECT_NAME}  | MSVC - Enabling '/MP' for parallel builds")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )

elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-psabi")
    set(CMAKE_CXX_STANDARD 17)
endif()