cmake_minimum_required(VERSION 3.16)
project(task1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)

add_executable(server main_server.cpp)
target_link_libraries(server lib)

add_executable(client main_client.cpp)
target_link_libraries(client lib)
