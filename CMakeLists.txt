cmake_minimum_required(VERSION 3.20)
project(Browser VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/browser_window.cpp
    src/browser_tab.cpp
)

# Create executable
add_executable(browser ${SOURCES})

# Platform-specific configuration
if(WIN32)
    # Windows configuration
    target_compile_definitions(browser PRIVATE _WIN32_WINNT=0x0A00)
    
    # For MSVC
    if(MSVC)
        target_compile_options(browser PRIVATE /W4 /WX)
        # Set subsystem to windows for GUI app (no console)
        # Remove the next line if you want console output
        set_target_properties(browser PROPERTIES WIN32_EXECUTABLE TRUE)
    else()
        # For MinGW/GCC on Windows
        target_compile_options(browser PRIVATE -Wall -Wextra -Werror)
    endif()
    
    # Find GTK4 on Windows (requires vcpkg or manual installation)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    pkg_check_modules(WEBKIT REQUIRED webkitgtk-6.0)
    
    target_include_directories(browser PRIVATE ${GTK4_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS})
    target_link_libraries(browser PRIVATE ${GTK4_LIBRARIES} ${WEBKIT_LIBRARIES})
    target_link_directories(browser PRIVATE ${GTK4_LIBRARY_DIRS} ${WEBKIT_LIBRARY_DIRS})
    
elseif(UNIX AND NOT APPLE)
    # Linux configuration
    target_compile_options(browser PRIVATE -Wall -Wextra -Werror)
    
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    pkg_check_modules(WEBKIT REQUIRED webkitgtk-6.0)
    
    target_include_directories(browser PRIVATE ${GTK4_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS})
    target_link_libraries(browser PRIVATE ${GTK4_LIBRARIES} ${WEBKIT_LIBRARIES})
    
elseif(APPLE)
    # macOS configuration
    target_compile_options(browser PRIVATE -Wall -Wextra -Werror)
    
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    pkg_check_modules(WEBKIT REQUIRED webkitgtk-6.0)
    
    target_include_directories(browser PRIVATE ${GTK4_INCLUDE_DIRS} ${WEBKIT_INCLUDE_DIRS})
    target_link_libraries(browser PRIVATE ${GTK4_LIBRARIES} ${WEBKIT_LIBRARIES})
endif()

# Installation
install(TARGETS browser DESTINATION bin)