// ============================================================================
// browser_toolbar.hpp - Toolbar creation module
// ============================================================================
#pragma once
#include <gtk/gtk.h>

class BrowserWindow;

class BrowserToolbar {
public:
    static GtkWidget* create(BrowserWindow* browser, GtkWidget** url_entry_out);

private:
    static GtkWidget* create_nav_buttons(BrowserWindow* browser);
    static GtkWidget* create_url_bar(GtkWidget** url_entry_out);
    static GtkWidget* create_new_tab_button(BrowserWindow* browser);
};
