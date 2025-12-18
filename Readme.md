# Browser

A lightweight, cross-platform web browser built with C++20, GTK4, and WebKitGTK.

## Features

- 🌐 Modern web browsing with WebKit engine
- 📑 Tabbed interface for multiple pages
- 🖥️ Cross-platform support (Linux, Windows, macOS)
- ⚡ Fast and lightweight
- 🎨 Native GTK4 interface

## Screenshots

*Coming soon*

## Requirements

### Linux (Ubuntu/Debian)
- GTK 4.0 or higher
- WebKitGTK 6.0 or higher
- CMake 3.20 or higher
- GCC 11+ or Clang 13+ (C++20 support required)

### Windows
- Visual Studio 2022 (or MinGW-w64 with GCC 11+)
- CMake 3.20 or higher
- GTK4 and WebKitGTK 6.0 (via vcpkg)
- Windows 10 or higher

### macOS
- macOS 11 (Big Sur) or higher
- Xcode 13+ or Clang 13+
- CMake 3.20 or higher
- GTK4 and WebKitGTK (via Homebrew)

## Installation

### Linux (Ubuntu/Debian)

1. **Install dependencies:**
   ```bash
   sudo apt update
   sudo apt install build-essential cmake pkg-config \
                    libgtk-4-dev libwebkitgtk-6.0-dev
   ```

2. **Clone and build:**
   ```bash
   git clone https://github.com/BhishanSharma/browser.git
   cd browser
   chmod +x build.sh
   ./build.sh
   ```

3. **Run:**
   ```bash
   ./build/browser
   ```

### Windows

#### Using vcpkg (Recommended)

1. **Install vcpkg:**
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg integrate install
   ```

2. **Install dependencies:**
   ```powershell
   .\vcpkg install gtk4:x64-windows webkitgtk:x64-windows
   ```

3. **Clone and build:**
   ```powershell
   git clone https://github.com/BhishanSharma/browser.git
   cd browser
   mkdir build
   cd build
   cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]\scripts\buildsystems\vcpkg.cmake
   cmake --build . --config Release
   ```

4. **Run:**
   ```powershell
   .\Release\browser.exe
   ```

#### Alternative: Create build.bat

Create a file named `build.bat`:
```batch
@echo off
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
cd ..
echo Build complete! Run "build\Release\browser.exe"
```

Then run: `build.bat`

### macOS

1. **Install dependencies:**
   ```bash
   brew install cmake gtk4 webkitgtk
   ```

2. **Clone and build:**
   ```bash
   git clone https://github.com/BhishanSharma/browser.git
   cd browser
   chmod +x build.sh
   ./build.sh
   ```

3. **Run:**
   ```bash
   ./build/browser
   ```

## Project Structure

```
browser/
├── src/
│   ├── main.cpp              # Application entry point
│   ├── browser_window.cpp    # Main window implementation
│   ├── browser_window.h      # Window header
│   ├── browser_tab.cpp       # Tab management
│   └── browser_tab.h         # Tab header
├── build/                    # Build output (generated)
├── CMakeLists.txt           # CMake configuration
├── build.sh                 # Linux/macOS build script
├── build.bat                # Windows build script
└── README.md                # This file
```

## Usage

### Basic Navigation
- **New Tab:** Ctrl+T (Cmd+T on macOS)
- **Close Tab:** Ctrl+W (Cmd+W on macOS)
- **Navigate:** Enter URL in address bar and press Enter
- **Reload:** F5 or Ctrl+R (Cmd+R on macOS)
- **Back/Forward:** Use browser navigation buttons

### Keyboard Shortcuts
- `Ctrl+T` / `Cmd+T` - New tab
- `Ctrl+W` / `Cmd+W` - Close current tab
- `Ctrl+R` / `Cmd+R` - Reload page
- `Ctrl+L` / `Cmd+L` - Focus address bar
- `Ctrl+Q` / `Cmd+Q` - Quit application
- `F11` - Toggle fullscreen

## Building from Source

### Configuration Options

You can customize the build with CMake options:

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build with optimizations
cmake -DCMAKE_BUILD_TYPE=Release ..

# Specify installation prefix
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

### Clean Build

```bash
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

## Troubleshooting

### Linux: GTK4/WebKitGTK not found
```bash
# Verify packages are installed
pkg-config --modversion gtk4
pkg-config --modversion webkitgtk-6.0

# If not found, install them
sudo apt install libgtk-4-dev libwebkitgtk-6.0-dev
```

### Windows: vcpkg libraries not found
Ensure you're using the CMake toolchain file:
```powershell
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake
```

### Compiler errors: C++20 not supported
Update your compiler:
- **Linux:** `sudo apt install g++-11` or newer
- **Windows:** Install Visual Studio 2022 or MinGW-w64 11+
- **macOS:** Update Xcode Command Line Tools

### Missing symbols or linking errors
Try a clean rebuild:
```bash
rm -rf build
./build.sh  # or build.bat on Windows
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### Coding Standards
- Follow C++20 best practices
- Use meaningful variable and function names
- Add comments for complex logic
- Ensure code compiles without warnings on all platforms

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with [GTK4](https://gtk.org/) for the user interface
- Powered by [WebKitGTK](https://webkitgtk.org/) for web rendering
- Cross-platform builds with [CMake](https://cmake.org/)

## Roadmap

- [ ] Bookmarks management
- [ ] History tracking
- [ ] Download manager
- [ ] Settings/Preferences panel
- [ ] Extensions support
- [ ] Dark mode
- [ ] Private browsing mode
- [ ] Search engine integration
- [ ] Custom themes

## Support

If you encounter any issues or have questions:
- Open an issue on [GitHub Issues](https://github.com/BhishanSharma/browser/issues)
- Check existing issues for solutions
- Provide detailed information about your system and the problem

## Authors

* **Your Name** - *Bhishan Sharma*

## Version History

* 1.0.0 (Initial Release)
  * Basic browser functionality
  * Tabbed interface
  * Cross-platform support

---

Made with ❤️ using C++20, GTK4, and WebKitGTK