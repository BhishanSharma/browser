// ============================================================================
// src/ui/about_dialog.cpp
// ============================================================================
#include "ui/about_dialog.hpp"
#include "../core/browser_config.hpp"

void AboutDialog::show(GtkWindow* parent) {
    GtkWidget* dialog = gtk_about_dialog_new();
    
    gtk_about_dialog_set_program_name(
        GTK_ABOUT_DIALOG(dialog), 
        BrowserConfig::BROWSER_NAME
    );
    
    gtk_about_dialog_set_version(
        GTK_ABOUT_DIALOG(dialog), 
        BrowserConfig::BROWSER_VERSION
    );
    
    gtk_about_dialog_set_comments(
        GTK_ABOUT_DIALOG(dialog),
        "A modern web browser built with GTK4 and WebKitGTK\n\n"
        "Features:\n"
        "• Fast and lightweight\n"
        "• Modern UI with dark theme\n"
        "• Multi-tab browsing\n"
        "• Download manager\n"
        "• Custom user agent"
    );
    
    gtk_about_dialog_set_website(
        GTK_ABOUT_DIALOG(dialog),
        "https://github.com/BhishanSharma/browser"
    );
    
    gtk_about_dialog_set_website_label(
        GTK_ABOUT_DIALOG(dialog),
        "Visit Project Website"
    );
    
    gtk_about_dialog_set_logo_icon_name(
        GTK_ABOUT_DIALOG(dialog),
        "web-browser"
    );
    
    const char* authors[] = {
        "Bhishan Sharma <bhishan.bulder@gmail.com>",
        nullptr
    };
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
    
    gtk_about_dialog_set_copyright(
        GTK_ABOUT_DIALOG(dialog),
        "Copyright © 2025 Bhishan Sharma"
    );
    
    gtk_about_dialog_set_license_type(
        GTK_ABOUT_DIALOG(dialog),
        GTK_LICENSE_MIT_X11
    );
    
    gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    
    gtk_window_present(GTK_WINDOW(dialog));
}