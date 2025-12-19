#!/usr/bin/env bash
# Simple build script for Linux
# For Windows builds, use GitHub Actions (see .github/workflows/build.yml)
set -euo pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

print_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

echo ""
echo "=========================================="
echo "       Browser Build Script (Linux)"
echo "=========================================="
echo ""

# Check for required dependencies
print_info "Checking dependencies..."
missing_deps=()

if ! command_exists pkg-config; then
    missing_deps+=("pkg-config")
fi

if ! command_exists g++; then
    missing_deps+=("build-essential")
fi

if ! pkg-config --exists gtk4 2>/dev/null; then
    missing_deps+=("libgtk-4-dev")
fi

if ! pkg-config --exists webkitgtk-6.0 2>/dev/null; then
    missing_deps+=("libwebkitgtk-6.0-dev")
fi

# Install missing dependencies
if [ ${#missing_deps[@]} -gt 0 ]; then
    print_warning "Missing dependencies: ${missing_deps[*]}"
    read -p "Install missing dependencies? (y/n) " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        print_info "Installing dependencies..."
        sudo apt update
        sudo apt install -y "${missing_deps[@]}"
        print_success "Dependencies installed!"
    else
        print_error "Cannot proceed without dependencies."
        exit 1
    fi
else
    print_success "All dependencies are installed!"
fi

# Build
print_info "Building browser..."

mkdir -p build

CXX=g++
CXXFLAGS="-std=c++20 -Wall -Wextra -Werror -O2"
LIBS=$(pkg-config --cflags --libs gtk4 webkitgtk-6.0)

$CXX $CXXFLAGS \
    src/main.cpp \
    src/browser_window.cpp \
    src/browser_tab.cpp \
    $LIBS \
    -o build/browser

echo ""
echo "=========================================="
print_success "Build complete!"
echo "=========================================="
echo ""
echo "Run your browser with: ./build/browser"
echo ""
print_info "💡 Tip: For Windows builds, push to GitHub and use Actions"
print_info "    See .github/workflows/build.yml for automatic builds"
echo ""