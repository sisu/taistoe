cmake_minimum_required(VERSION 2.6)

project(taistoe)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++0x")

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
link_libraries(${OPENGL_LIBRARY} "SDL")
include_directories(${SDL_INCLUDE_DIR})

#add_definitions("-Wall -g")
#add_definitions("-Wall -O2")
#add_definitions("-Wall -g -Wno-unused-result ")
add_definitions("-O2 -g -fno-inline")
#add_definitions("-Wall -g -Wno-unused-result")
#add_definitions("-Wall -Wno-unused-result -Os -fomit-frame-pointer -ffast-math")
add_definitions("-std=c++0x -Wall")

set(sources main.cpp physics.cpp draw.cpp Game.cpp Area.cpp util.cpp)

#MESSAGE( STATUS "flags : ${OPENGL_LIBRARY}" )

add_executable(taistoe ${sources})
