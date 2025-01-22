#!/bin/bash

# Define the build directory
BUILD_DIR="build"

# Remove all files in the build directory (be careful with this)
echo "Cleaning build directory..."
rm -rf $BUILD_DIR/*

# Create the build directory if it doesn't exist
echo "Creating build directory..."
mkdir -p $BUILD_DIR

# Navigate to the build directory
cd $BUILD_DIR

# Run CMake with the MinGW Makefiles generator
echo "Running CMake configuration..."
cmake -G "MinGW Makefiles" ..

# Build the project
echo "Building the project..."
cmake --build .

# Check if the executable exists
if [ -f "./SeotdaGame.exe" ]; then
    # Move back to the project root directory to run the executable
    cd ..

    echo "Launching SeotdaGame.exe..."
    ./build/SeotdaGame.exe
else
    echo "Build failed. Executable not found."
fi

# End of script
echo "Build process completed!"
