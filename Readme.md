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

### Pre-built Binaries (Recommended)

Download the latest release for your platform from the [Releases](https://github.com/yourusername/browser/releases) page:
- **Linux:** `browser-linux-x64.tar.gz`
- **Windows:** `browser-windows-x64.zip`

All releases are automatically built and tested by GitHub Actions.

### Building from Source

#### Linux (Ubuntu/Debian)

1. **Install dependencies:**
   ```bash
   sudo apt update
   sudo apt install build-essential pkg-config \
                    libgtk-4-dev libwebkitgtk-6.0-dev
   ```

2. **Clone and build:**
   ```bash
   git clone https://github.com/yourusername/browser.git
   cd browser
   chmod +x build.sh
   ./build.sh
   ```

3. **Run:**
   ```bash
   ./build/browser
   ```

### Windows

**Recommended:** Download pre-built Windows executables from the [Releases](https://github.com/yourusername/browser/releases) page.

Releases are automatically built by GitHub Actions whenever code is pushed or a new release is created.

#### Building from Source (Windows)

If you want to build locally on Windows:

1. **Install MSYS2:** Download from https://www.msys2.org/

2. **Open MSYS2 MinGW 64-bit terminal and install dependencies:**
   ```bash
   pacman -Syu
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gtk4 \
             mingw-w64-x86_64-webkitgtk6 mingw-w64-x86_64-pkg-config
   ```

3. **Build:**
   ```bash
   mkdir -p build
   g++ -std=c++20 -Wall -Wextra -O2 \
       src/main.cpp src/browser_window.cpp src/browser_tab.cpp \
       $(pkg-config --cflags --libs gtk4 webkitgtk-6.0) \
       -o build/browser.exe
   ```

4. **Run:**
   ```bash
   ./build/browser.exe
   ```

### macOS

1. **Install dependencies:**
   ```bash
   brew install cmake gtk4 webkitgtk
   ```

2. **Clone and build:**
   ```bash
   git clone https://github.com/yourusername/browser.git
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
├── .github/
│   └── workflows/
│       └── build.yml          # GitHub Actions CI/CD
├── src/
│   ├── main.cpp              # Application entry point
│   ├── browser_window.cpp    # Main window implementation
│   ├── browser_window.h      # Window header
│   ├── browser_tab.cpp       # Tab management
│   └── browser_tab.h         # Tab header
├── build/                    # Build output (generated)
├── build.sh                  # Linux build script
└── README.md                 # This file
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

The build.sh script handles all configuration automatically. For custom builds:

```bash
# Debug build
g++ -std=c++20 -g -O0 \
    src/main.cpp src/browser_window.cpp src/browser_tab.cpp \
    $(pkg-config --cflags --libs gtk4 webkitgtk-6.0) \
    -o build/browser

# Release build with optimizations (default)
g++ -std=c++20 -O2 \
    src/main.cpp src/browser_window.cpp src/browser_tab.cpp \
    $(pkg-config --cflags --libs gtk4 webkitgtk-6.0) \
    -o build/browser
```

### Clean Build

```bash
rm -rf build
./build.sh
```

### Continuous Integration

This project uses GitHub Actions for automated builds. On every push:
- ✅ Linux executable is built and tested
- ✅ Windows executable is built with MSYS2
- ✅ Artifacts are uploaded for download
- ✅ Releases are automatically created with binaries

See `.github/workflows/build.yml` for the full CI/CD pipeline.

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
- Open an issue on [GitHub Issues](https://github.com/yourusername/browser/issues)
- Check existing issues for solutions
- Provide detailed information about your system and the problem

## Authors

* **Your Name** - *Initial work*

## Version History

* 1.0.0 (Initial Release)
  * Basic browser functionality
  * Tabbed interface
  * Cross-platform support

---

Made with ❤️ using C++20, GTK4, and WebKitGTK