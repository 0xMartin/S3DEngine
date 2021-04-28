cmake_minimum_required(VERSION 3.5)

project(S3DEngine LANGUAGES C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data/)


file(GLOB sources "*.c")
file(GLOB headers "*.h")

add_compile_options(-Wall -Wextra -std=c11)

add_executable(${PROJECT_NAME} test.c)

add_subdirectory(s3d)
target_link_libraries(${PROJECT_NAME} PRIVATE s3d)

