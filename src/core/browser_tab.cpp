// ============================================================================
// Update src/core/browser_tab.cpp to use custom user agent
// ============================================================================
#include "core/browser_tab.hpp"
#include "core/browser_config.hpp"
#include <stdexcept>

BrowserTab::BrowserTab() {
    // Create webview first
    m_webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    
    if (!m_webview) {
        throw std::runtime_error("Failed to create WebKitWebView");
    }
    
    // Get and configure settings
    WebKitSettings* settings = webkit_web_view_get_settings(m_webview);
    
    // Enable features
    webkit_settings_set_enable_javascript(settings, TRUE);
    webkit_settings_set_enable_webaudio(settings, FALSE);
    webkit_settings_set_enable_webgl(settings, TRUE);
    webkit_settings_set_enable_media_stream(settings, TRUE);
    webkit_settings_set_enable_developer_extras(settings, TRUE);
    
    // Set custom user agent - THIS IS THE KEY LINE!
    webkit_settings_set_user_agent(
        settings, 
        BrowserConfig::get_user_agent().c_str()
    );
}

BrowserTab::~BrowserTab() = default;

GtkWidget* BrowserTab::widget() const {
    return GTK_WIDGET(m_webview);
}

WebKitWebView* BrowserTab::webview() const {
    return m_webview;
}

void BrowserTab::load_uri(const char* uri) {
    if (!uri || !*uri) return;
    webkit_web_view_load_uri(m_webview, uri);
}
