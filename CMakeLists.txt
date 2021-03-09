cmake_minimum_required(VERSION 2.8)

project(TicTacToe C)

file(GLOB sources "src/*.c" "src/engine2d/*.c" "src/objects/*.c")
file(GLOB headers "src/*.h" "src/engine2d/*.h" "src/objects/*.h")
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin/data/)

add_compile_options(-Wall -Wextra -pthread -std=c11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${PROJECT_NAME} ${sources} ${headers} src/main.c)
if (UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif (UNIX)

#OpenGL + GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
#theads
find_package (Threads REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

