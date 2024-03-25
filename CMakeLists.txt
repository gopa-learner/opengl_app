cmake_minimum_required(VERSION 3.28.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS)

project(
  "OPENGL_BEENCOOK"
  VERSION 1
  DESCRIPTION " A OPENGL LEARNING PROGRAM"
  LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")
set(CMAKE_BUILD_TYPE Debug)
find_package(OpenGL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)

# for my own source code
file(GLOB SOURCE_file CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
message("SOURCE FILES ARE" ${SOURCE_file})
# for my owm header file
file(GLOB HEADER_file CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/header/*.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/header/*.h)

message("header FILES ARE" ${HEADER_file})
# for all linrary
file(GLOB library CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)
message("library FILES ARE" ${library})

add_executable(${PROJECT_NAME} ${SOURCE_file} ${HEADER_file})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header/GLFW
         ${CMAKE_CURRENT_SOURCE_DIR}/header/GL ${CMAKE_CURRENT_SOURCE_DIR}/glm
         ${CMAKE_CURRENT_SOURCE_DIR}/header)
target_link_libraries(${PROJECT_NAME} PRIVATE ${library} glm::glm OpenGL::GLX)

# add_dependencies(${PROJECT_NAME} OpenGL::OpenGL)
