cmake_minimum_required(VERSION 3.5)

project(S3DEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data/)

add_compile_options(-Wall -Wextra -std=c11)

add_executable(S3DEngine test.cpp)


add_subdirectory(s3d)
target_link_libraries(${PROJECT_NAME} PRIVATE s3d)


