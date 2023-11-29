cmake_minimum_required(VERSION 3.0)
project(application)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

include_directories(
    ${CMAKE_SOURCE_DIR}
)

link_libraries(
    pthread
    grpc++
    protobuf
    /usr/local/lib/libjemalloc.so
)


file(GLOB GENERATED_FILES ${CMAKE_SOURCE_DIR}/src/generated/*.cc)

add_executable(
    server
    src/grpc_server.cpp
    ${GENERATED_FILES}
)

add_executable(
    client
    src/grpc_client.cpp
    ${GENERATED_FILES}
)