cmake_minimum_required(VERSION 3.9)
project(GKOM_Wrench)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-framework OpenGL -Wunused-command-line-argument")

include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/wrench)

file(GLOB_RECURSE SOURCES "wrench/*.cpp")
file(GLOB_RECURSE HEADERS "wrench/*.h*")

add_executable(GKOM_Wrench main.cpp ${SOURCES} ${HEADERS})

target_link_libraries(GKOM_Wrench /usr/local/lib/libGLEW.dylib /usr/local/lib/libSOIL.dylib /usr/local/lib/libglfw.dylib)