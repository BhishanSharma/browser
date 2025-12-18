#pragma once

#include <webkit/webkit.h>

class BrowserTab {
public:
    BrowserTab();
    ~BrowserTab();

    GtkWidget* widget() const;
    WebKitWebView* webview() const;

    void load_uri(const char* uri);

private:
    WebKitWebView* m_webview;
};
