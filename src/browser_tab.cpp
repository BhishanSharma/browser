#include "browser_tab.hpp"
#include <stdexcept>

BrowserTab::BrowserTab() {
    m_webview = WEBKIT_WEB_VIEW(webkit_web_view_new());
    if (!m_webview) {
        throw std::runtime_error("Failed to create WebKitWebView");
    }

    WebKitSettings* settings = webkit_web_view_get_settings(m_webview);
    webkit_settings_set_enable_javascript(settings, TRUE);
    webkit_settings_set_enable_webaudio(settings, FALSE);
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
