
// ============================================================================
// browser_tab_label.hpp - Tab label creation module
// ============================================================================
#pragma once
#include <gtk/gtk.h>

class BrowserTabLabel {
public:
    static GtkWidget* create(int page_num, void* user_data);
    static void update_title(GtkWidget* tab_label, const char* title);
};
