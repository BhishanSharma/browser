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
    message(STATUS "Debug build - optimizations disabled")
else()
    add_compile_options(-O3)
    message(STATUS "Release build - optimizations enabled")
endif()

# Find required packages
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(WEBKIT REQUIRED webkitgtk-6.0)

# Source files organized by category
set(CORE_SOURCES
    src/core/browser_window.cpp
    src/core/browser_tab.cpp
)

set(UI_SOURCES
    src/ui/browser_toolbar.cpp
    src/ui/browser_tab_label.cpp
    src/ui/about_dialog.cpp
)

set(UTILS_SOURCES
    src/utils/url_utils.cpp
)

set(MAIN_SOURCE
    src/main.cpp
)

# Combine all sources
set(ALL_SOURCES
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${UI_SOURCES}
    ${UTILS_SOURCES}
)

# Create executable
add_executable(aurora-browser ${ALL_SOURCES})

# Include directories (so #include "core/browser_window.hpp" works)
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

# Compile options
target_compile_options(aurora-browser PRIVATE
    ${GTK4_CFLAGS_OTHER}
    ${WEBKIT_CFLAGS_OTHER}
)

# Install target
install(TARGETS aurora-browser DESTINATION bin)

# Create a 'run' target for convenience
add_custom_target(run
    COMMAND aurora-browser
    DEPENDS aurora-browser
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    COMMENT "Running Aurora Browser..."
)

# Print configuration info
message(STATUS "=========================================")
message(STATUS "Aurora Browser Build Configuration")
message(STATUS "=========================================")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "GTK4 version: ${GTK4_VERSION}")
message(STATUS "WebKitGTK version: ${WEBKIT_VERSION}")
message(STATUS "Source files: ${CMAKE_CURRENT_LIST_DIR}/src/")
message(STATUS "  - Core: ${CORE_SOURCES}")
message(STATUS "  - UI: ${UI_SOURCES}")
message(STATUS "  - Utils: ${UTILS_SOURCES}")
message(STATUS "=========================================")