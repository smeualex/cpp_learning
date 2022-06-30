
# get all the source files
file( GLOB SRCS 
    src/*.cpp
)

# set common runtime output directory
set_runtime_directory(alg_sorting)

if (MSVC)
    add_compile_options(/MP)
else()
    add_compile_options(-Wall -pedantic)
endif()


message(STATUS " ${PROJECT_NAME}  |  Generating executables: ")
# generate an executable for each one
foreach(SRC ${SRCS})
    get_filename_component(EXECUTABLE_NAME ${SRC} NAME_WE)
    # string( REPLACE ".cpp" "" EXECUTABLE_NAME ${SRC})
    message(STATUS " ${PROJECT_NAME}  |     > ${EXECUTABLE_NAME} ")
    add_executable( ${EXECUTABLE_NAME} ${SRC})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
endforeach()