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
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
# for libgl
find_package(OpenGL REQUIRED)

# find_package(ZLIB REQUIRED)


# set variables that are needed
# set(ZLIB_LIBRARIES zlibstatic)
# set(ENABLE_BOOST_WORKAROUND ON)
# set(BUILD_STATIC_LIB ON)
# set(BUILD_ASSIMP_TOOLS  ON)
# set(ASSIMP_BUILD_STATIC_LIB ON)
#

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glm)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/ASSIMP)

# for my own source code
file(GLOB SOURCE_file CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
message("SOURCE FILES ARE"  )

foreach( i  ${SOURCE_file})
  message(${i})
endforeach()

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ASSIMP)
# for my owm header file
file(GLOB HEADER_file CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/header/*.hpp
${CMAKE_CURRENT_SOURCE_DIR}/header/*.h)


message("header FILES ARE" ${HEADER_file})
foreach( i ${HEADER_file}  )
  message(${i})
endforeach()


# for all linrary
file(GLOB library CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.a)
message("library FILES ARE" ${library})
foreach( i ${library})
  message(${i})
endforeach()


add_executable(${PROJECT_NAME}
                                  ${SOURCE_file}
                                  ${HEADER_file}
 )
# target_precompile_headers(${PROJECT_NAME} PRIVATE  ${HEADER_file}  )
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/header/GLFW
         ${CMAKE_CURRENT_SOURCE_DIR}/header/GL
         ${CMAKE_CURRENT_SOURCE_DIR}/header/include
         ${CMAKE_CURRENT_SOURCE_DIR}/glm
         ${CMAKE_CURRENT_SOURCE_DIR}/header
                 )
target_link_libraries(${PROJECT_NAME} PRIVATE assimp  ${library}  glm::glm OpenGL::GLX)


# add_dependencies(${PROJECT_NAME} OpenGL::OpenGL)
