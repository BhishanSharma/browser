// ============================================================================
// url_utils.cpp
// ============================================================================
#include "url_utils.hpp"
#include <glib.h>

std::string UrlUtils::normalize_url(const std::string& input) {
    if (input.find("://") != std::string::npos) {
        return input;
    }

    // Check if it looks like a domain
    if (input.find('.') != std::string::npos && input.find(' ') == std::string::npos) {
        return "https://" + input;
    }

    // Treat as search query
    std::string encoded;
    for (char c : input) {
        encoded += (c == ' ') ? '+' : c;
    }
    return "https://www.google.com/search?q=" + encoded;
}

std::string UrlUtils::get_download_path(const char* uri) {
    const char* home = g_get_home_dir();
    const char* filename = g_path_get_basename(uri);
    return std::string(home) + "/Downloads/" + filename;
}
