// ============================================================================
// browser_tab_label.cpp
// ============================================================================
#include "browser_tab_label.hpp"
#include "../core/browser_window.hpp"

GtkWidget* BrowserTabLabel::create(int /*page_num*/, void* user_data) {
    GtkWidget* tab_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

    // Favicon icon
    GtkWidget* icon = gtk_label_new("🌐");
    gtk_widget_add_css_class(icon, "tab-icon");
    gtk_box_append(GTK_BOX(tab_box), icon);

    // Tab title label
    GtkWidget* label = gtk_label_new("New Tab");
    gtk_widget_add_css_class(label, "tab-label");
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_label_set_max_width_chars(GTK_LABEL(label), 20);
    gtk_box_append(GTK_BOX(tab_box), label);

    // Close button (page_num will be set by caller after notebook append)
    GtkWidget* close_btn = gtk_button_new_from_icon_name("window-close-symbolic");
    gtk_widget_add_css_class(close_btn, "tab-close-button");
    gtk_widget_set_tooltip_text(close_btn, "Close");
    gtk_button_set_has_frame(GTK_BUTTON(close_btn), FALSE);
    g_signal_connect(close_btn, "clicked", G_CALLBACK(BrowserWindow::on_close_tab), user_data);
    gtk_box_append(GTK_BOX(tab_box), close_btn);

    return tab_box;
}

void BrowserTabLabel::update_title(GtkWidget* tab_label, const char* title) {
    if (!tab_label || !GTK_IS_BOX(tab_label)) return;

    // Skip icon, get label (second child)
    GtkWidget* child = gtk_widget_get_first_child(tab_label);
    if (child) child = gtk_widget_get_next_sibling(child);

    if (child && GTK_IS_LABEL(child)) {
        gtk_label_set_text(GTK_LABEL(child), title);
    }
}
