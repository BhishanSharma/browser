#!/usr/bin/env bash
set -euo pipefail

CXX=g++
CXXFLAGS="-std=c++20 -Wall -Wextra -Werror"
LIBS=$(pkg-config --cflags --libs gtk4 webkitgtk-6.0)

mkdir -p build

$CXX $CXXFLAGS \
  src/main.cpp \
  src/browser_window.cpp \
  src/browser_tab.cpp \
  src/browser_toolbar.cpp \
  src/browser_tab_label.cpp \
  src/url_utils.cpp \
  $LIBS \
  -o build/browser

echo "✅ Build complete. Run './build/browser' to start."