#!/usr/bin/env bash
# build.sh - Linux/macOS build script
set -euo pipefail

echo "Building for Linux/macOS..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build
cmake --build . -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "Build complete!"
echo "Run './build/browser' to start the application."