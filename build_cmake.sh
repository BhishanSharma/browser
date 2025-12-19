#!/usr/bin/env bash
# build_cmake.sh

set -euo pipefail

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build (use all CPU cores)
cmake --build . -j$(nproc)

echo ""
echo "✅ Build complete!"
echo "Run: ./build/aurora-browser"