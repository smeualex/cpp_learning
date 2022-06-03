
# get all the source files
file( GLOB SRCS src/*.cpp)

message(STATUS " ${PROJECT_NAME}  |  Generating executables: ")
# generate an executable for each one
foreach(SRC ${SRCS})
    get_filename_component(EXECUTABLE_NAME ${SRC} NAME_WE)
    # string( REPLACE ".cpp" "" EXECUTABLE_NAME ${SRC})
    message(STATUS " ${PROJECT_NAME}  |     > ${EXECUTABLE_NAME} ")
    add_executable( ${EXECUTABLE_NAME} ${SRC})
endforeach()