add_library(lib STATIC src/server.cpp src/client.cpp src/workingWithStudents.cpp)

target_include_directories(lib PUBLIC include)
target_link_libraries(lib zmq)
