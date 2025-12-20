// ============================================================================
// browser_toolbar.cpp
// ============================================================================
#include "ui/browser_toolbar.hpp"
#include "../core/browser_window.hpp"

GtkWidget* BrowserToolbar::create(BrowserWindow* browser, GtkWidget** url_entry_out) {
    GtkWidget* toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_add_css_class(toolbar, "toolbar");

    // Add navigation buttons
    GtkWidget* nav_buttons = create_nav_buttons(browser);
    gtk_box_append(GTK_BOX(toolbar), nav_buttons);

    // Add URL bar
    GtkWidget* url_bar = create_url_bar(url_entry_out);
    gtk_box_append(GTK_BOX(toolbar), url_bar);

    return toolbar;
}

GtkWidget* BrowserToolbar::create_nav_buttons(BrowserWindow* browser) {
    GtkWidget* nav_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);

    struct ButtonConfig {
        const char* icon;
        const char* tooltip;
        void (*callback)(GtkButton*, gpointer);
    };

    ButtonConfig buttons[] = {
        {"go-previous-symbolic", "Back", BrowserWindow::on_back},
        {"go-next-symbolic", "Forward", BrowserWindow::on_forward},
        {"view-refresh-symbolic", "Reload", BrowserWindow::on_reload},
        {"go-home-symbolic", "Home", BrowserWindow::on_home}
    };

    for (const auto& btn_config : buttons) {
        GtkWidget* btn = gtk_button_new_from_icon_name(btn_config.icon);
        gtk_widget_add_css_class(btn, "nav-button");
        gtk_widget_set_tooltip_text(btn, btn_config.tooltip);
        g_signal_connect(btn, "clicked", G_CALLBACK(btn_config.callback), browser);
        gtk_box_append(GTK_BOX(nav_box), btn);
    }

    return nav_box;
}

GtkWidget* BrowserToolbar::create_url_bar(GtkWidget** url_entry_out) {
    GtkWidget* url_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_add_css_class(url_container, "url-container");
    gtk_widget_set_hexpand(url_container, TRUE);

    GtkWidget* url_entry = gtk_entry_new();
    gtk_widget_add_css_class(url_entry, "url-entry");
    gtk_widget_set_hexpand(url_entry, TRUE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(url_entry), "Search or enter address");

    gtk_box_append(GTK_BOX(url_container), url_entry);

    *url_entry_out = url_entry;
    return url_container;
}
