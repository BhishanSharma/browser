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
├── CMakeLists.txt
├── build_cmake.sh
├── build.sh
├── README.md                    (add this!)
├── .gitignore                   (add this!)
├── build/                       (auto-generated)
└── src/
    ├── main.cpp
    ├── core/                    ← Core browser logic
    │   ├── browser_window.hpp
    │   ├── browser_window.cpp
    │   ├── browser_tab.hpp
    │   └── browser_tab.cpp
    ├── ui/                      ← UI components
    │   ├── browser_toolbar.hpp
    │   ├── browser_toolbar.cpp
    │   ├── browser_tab_label.hpp
    │   └── browser_tab_label.cpp
    ├── styles/                  ← Styling
    │   └── browser_styles.hpp
    └── utils/                   ← Utilities
        ├── url_utils.hpp
        └── url_utils.cpp