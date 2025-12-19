```
sudo apt install -y \
  build-essential \
  pkg-config \
  libgtk-4-dev \
  libwebkitgtk-6.0-dev
```

```
./build_cmake.sh
./build/browser
```

rm -rf build  # Clean everything
```

## Updated Project Structure:
```
browser/
├── CMakeLists.txt          ← NEW
├── build_cmake.sh          ← NEW
├── build.sh                (keep for simple builds)
├── build/                  (auto-generated)
│   ├── genoma-browser      (executable)
│   └── ... (cmake files)
└── src/
    ├── main.cpp
    ├── browser_window.hpp
    ├── browser_window.cpp
    ├── browser_tab.hpp
    ├── browser_tab.cpp
    ├── browser_styles.hpp
    ├── browser_toolbar.hpp
    ├── browser_toolbar.cpp
    ├── browser_tab_label.hpp
    ├── browser_tab_label.cpp
    ├── url_utils.hpp
    └── url_utils.cpp