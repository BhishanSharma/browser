cmake_minimum_required(VERSION 3.20)
project(AuroraBrowser VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
add_compile_options(-Wall -Wextra -Werror)

# Debug/Release flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-g -O0)
else()
    add_compile_options(-O3)
endif()

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(WEBKIT REQUIRED webkitgtk-6.0)

# Source files
set(SOURCES
    src/main.cpp
    src/browser_window.cpp
    src/browser_tab.cpp
    src/browser_toolbar.cpp
    src/browser_tab_label.cpp
    src/url_utils.cpp
)

# Create executable
add_executable(aurora-browser ${SOURCES})

# Include directories
target_include_directories(aurora-browser PRIVATE
    ${GTK4_INCLUDE_DIRS}
    ${WEBKIT_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(aurora-browser PRIVATE
    ${GTK4_LIBRARIES}
    ${WEBKIT_LIBRARIES}
)

# Link directories
target_link_directories(aurora-browser PRIVATE
    ${GTK4_LIBRARY_DIRS}
    ${WEBKIT_LIBRARY_DIRS}
)

# Compile options (not definitions)
target_compile_options(aurora-browser PRIVATE
    ${GTK4_CFLAGS_OTHER}
    ${WEBKIT_CFLAGS_OTHER}
)

# Install target (optional)
install(TARGETS aurora-browser DESTINATION bin)

# Print configuration info
message(STATUS "=========================================")
message(STATUS "Aurora Browser Configuration")
message(STATUS "=========================================")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "GTK4 version: ${GTK4_VERSION}")
message(STATUS "WebKitGTK version: ${WEBKIT_VERSION}")
message(STATUS "=========================================")