@echo off
echo Building for Windows...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake (adjust generator as needed)
REM For Visual Studio 2022:
cmake .. -G "Visual Studio 17 2022" -A x64

REM Or for MinGW:
REM cmake .. -G "MinGW Makefiles"

REM Build
cmake --build . --config Release

echo.
echo Build complete!
echo Run "build\Release\browser.exe" to start the application.

cd ..