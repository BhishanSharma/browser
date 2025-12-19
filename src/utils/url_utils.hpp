
// ============================================================================
// url_utils.hpp - URL handling utilities
// ============================================================================
#pragma once
#include <string>

namespace UrlUtils {
    std::string normalize_url(const std::string& input);
    std::string get_download_path(const char* uri);
}
