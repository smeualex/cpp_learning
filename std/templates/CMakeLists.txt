# get all the source files
file( GLOB SRCS 
    src/*.cpp
)
message("")
message(" SRCS1: ${SRCS}")

# remove the template source
list(REMOVE_ITEM SRCS 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/00_template.cpp"
)

message("")
message(" SRCS2: ${SRCS}")
# set common runtime output directory
set_runtime_directory(templates)

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