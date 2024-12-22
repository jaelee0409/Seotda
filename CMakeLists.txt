cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

# Set build type (either Debug or Release)
set(CMAKE_BUILD_TYPE Debug)

# Make sure the proper macro is defined
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
endif()

project(Seotda)

# Find the SDL2 package
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Automatically collect all .cpp files in src
file(GLOB SOURCES
    src/*.cpp
)

# Create the executable
add_executable(Seotda ${SOURCES})

# Link the SDL2 and SDL2_image libraries
target_link_libraries(Seotda 
    SDL2::SDL2 
    SDL2_image::SDL2_image
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)

# Define SDL_MAIN_HANDLED to prevent SDL2 from defining its own main
add_definitions(-DSDL_MAIN_HANDLED)