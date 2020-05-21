# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(sender)

# Find required protobuf package
find_package(Protobuf REQUIRED)

add_executable(${PROJECT_NAME} sender.cc)
target_link_libraries(${PROJECT_NAME} PUBLIC msgbook ${Protobuf_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Protobuf_INCLUDE_DIRS})
