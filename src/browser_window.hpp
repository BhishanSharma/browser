#pragma once

#include <gtk/gtk.h>
#include <vector>
#include <memory>
#include <webkit/webkit.h>

#include "browser_tab.hpp"

class BrowserWindow
{
public:
    BrowserWindow();
    ~BrowserWindow();

    void run(int argc, char **argv);

private:
    GtkApplication *m_app;
    GtkWidget *m_window;
    GtkWidget *m_notebook;
    GtkWidget *m_url_entry;

    std::vector<std::unique_ptr<BrowserTab>> m_tabs;

    static void on_activate(GtkApplication *app, gpointer user_data);
    static void on_new_tab(GtkButton *, gpointer user_data);
    static void on_close_tab(GtkButton *button, gpointer user_data);
    static void on_url_activate(GtkEntry *, gpointer user_data);
    static void on_back(GtkButton *, gpointer user_data);
    static void on_forward(GtkButton *, gpointer user_data);
    static void on_reload(GtkButton *, gpointer user_data);
    static void on_home(GtkButton *, gpointer user_data);

    void create_ui();
    void add_tab();
    BrowserTab *current_tab();
    
    static void on_download_started(
        WebKitWebContext *context,
        WebKitDownload *download,
        gpointer user_data);

    static void on_download_finished(
        WebKitDownload *download,
        gpointer user_data);

    static void on_load_changed(
        WebKitWebView *webview,
        WebKitLoadEvent load_event,
        gpointer user_data);

    static void on_title_changed(
        WebKitWebView *webview,
        GParamSpec *pspec,
        gpointer user_data);
};