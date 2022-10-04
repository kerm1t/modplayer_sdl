cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# "../" --> output directory relative same to running in IDE
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

set (CMAKE_GENERATOR_PLATFORM "x64")

project(modplayer_sdl)

set (SDL2_DIR C:/GIT-copy/modplayer/SDL2-devel-2.24.0-VC/SDL2-2.24.0/cmake)
find_package(SDL2 REQUIRED)

# add WIN32 to remove console window ->
add_executable (modplayer_sdl WIN32 ./src/modplayer.cpp ./src/pocketmod.h ./src/text.cpp ./src/text.h)

include_directories(./src ${SDL2_INCLUDE_DIRS})
target_link_libraries(modplayer_sdl ${SDL2_LIBRARIES})