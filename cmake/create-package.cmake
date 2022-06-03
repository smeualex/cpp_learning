###############################################################################
## CPACK - Common Installer Options
###############################################################################
set(CPACK_PACKAGE_NAME                  "bips")
set(CPACK_PACKAGE_VENDOR                "Bizerba")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   "BIPS - Bizerba Production Software")
#
# Text from "license.txt" is displayed in the installer's license tab
#
set(CPACK_RESOURCE_FILE_LICENSE         "${CMAKE_CURRENT_SOURCE_DIR}/license/License.txt")
set(CPACK_PACKAGE_INSTALL_DIRECTORY     "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR         ${BIPS_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR         ${BIPS_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH         ${BIPS_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})

message(STATUS " ${PROJECT_NAME}  | ----------------------------------------------------------------")
message(STATUS " ${PROJECT_NAME}  | -- CPack - Creating package: ${CPACK_PACKAGE_NAME} - v ${CPACK_PACKAGE_VERSION}")
message(STATUS " ${PROJECT_NAME}  | ----------------------------------------------------------------")

if(DEV_BUILD)
    set(CPACK_PACKAGE_NAME                  "bips_DEV_BUILD")
endif()

if(WIN32 AND NOT UNIX)
    include(package/nsis)
else(UNIX)
    ### find our os (wins, centos, ubuntu, etc) from /etc/os-release
    if(CMAKE_SYSTEM_NAME MATCHES "Linux")
        execute_process (
                COMMAND bash -c "awk -F= '/^ID=/{print $2}' /etc/os-release |tr -d '\n' | tr -d '\"'"
                OUTPUT_VARIABLE outOS
        )
        if(${VERBOSE_OUTPUT})
            message(STATUS " ${PROJECT_NAME}  | Detected Linux ${outOS}")
        endif()
    else()
        message(FATAL " ${PROJECT_NAME}  | Could not detect operating system...")
    endif()
    
    # RPM based distros go here
    if(${outOS} MATCHES "centos")
        include(package/rpm)
    # DEB based distros
    elseif(${outOS} MATCHES "debian")
        include(package/debian)
    endif()
endif()

set(CPACK_PACKAGE_EXECUTABLES "bips" "Bizerba Production Software")

include(CPack)