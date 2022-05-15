cmake_minimum_required(VERSION 3.8)

project("Fibonacci_Service" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/)

add_subdirectory(grpc)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ SUB_SOURCES)

add_executable(${PROJECT_NAME} ${SUB_SOURCES} server/main.cpp)
target_link_libraries (${PROJECT_NAME} grpc++_unsecure)


add_executable(${PROJECT_NAME}_client ${SUB_SOURCES} client/main.cpp)
target_link_libraries (${PROJECT_NAME}_client grpc++_unsecure)