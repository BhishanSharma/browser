// ============================================================================
// src/core/browser_config.hpp - Browser configuration (HEADER ONLY)
// ============================================================================
#pragma once
#include <string>

namespace BrowserConfig {
    // Browser identity
    inline constexpr const char* BROWSER_NAME = "Aurora Browser";
    inline constexpr const char* BROWSER_VERSION = "0.1.0";
    inline constexpr const char* BROWSER_CODENAME = "Aurora";
    
    // Build custom user agent string
    inline std::string get_user_agent() {
        return "Mozilla/5.0 (X11; Linux x86_64) "
               "AppleWebKit/605.1.15 (KHTML, like Gecko) "
               "AuroraBrowser/0.1.0 "
               "Chrome/120.0.0.0 "
               "Safari/605.1.15";
    }
    
    // Default settings
    inline constexpr const char* DEFAULT_HOMEPAGE = "https://www.google.com";
    inline constexpr const char* DEFAULT_SEARCH_ENGINE = "https://www.google.com/search?q=";
    inline constexpr int DEFAULT_WINDOW_WIDTH = 1400;
    inline constexpr int DEFAULT_WINDOW_HEIGHT = 900;
}