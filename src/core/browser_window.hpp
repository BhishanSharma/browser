// ============================================================================
// browser_window.hpp - Header with custom tab bar support
// ============================================================================
#ifndef BROWSER_WINDOW_HPP
#define BROWSER_WINDOW_HPP

#include "browser_tab.hpp"
#include <gtk/gtk.h>
#include <vector>
#include <memory>
#include <string>

struct TabInfo
{
    GtkWidget *button;
    GtkWidget *label;
    std::string stack_name;
};

class BrowserWindow
{
public:
    BrowserWindow();
    ~BrowserWindow();

    void run(int argc, char **argv);
    BrowserTab *current_tab();

    // Event handlers (public for callbacks)
    static void on_new_tab(GtkButton *button, gpointer user_data);
    static void on_close_tab(GtkButton *button, gpointer user_data);
    static void on_back(GtkButton *button, gpointer user_data);
    static void on_forward(GtkButton *button, gpointer user_data);
    static void on_reload(GtkButton *button, gpointer user_data);
    static void on_home(GtkButton *button, gpointer user_data);
    static void on_url_activate(GtkEntry *entry, gpointer user_data);
    static void on_tab_clicked(GtkGestureClick *gesture, int n_press, 
                               double x, double y, gpointer user_data);

private:
    void create_ui();
    void create_tab_bar();
    void apply_styles();
    void setup_download_handler();
    void add_tab();
    void switch_to_tab(int index);

    static void on_activate(GtkApplication *app, gpointer user_data);
    static void on_download_started(WebKitWebContext *context,
                                   WebKitDownload *download,
                                   gpointer user_data);
    static void on_download_finished(WebKitDownload *download, gpointer user_data);
    static void on_load_changed(WebKitWebView *webview,
                               WebKitLoadEvent load_event,
                               gpointer user_data);
    static void on_title_changed(WebKitWebView *webview,
                                GParamSpec *pspec,
                                gpointer user_data);

    GtkApplication *m_app;
    GtkWidget *m_window;
    GtkWidget *m_tab_bar;
    GtkWidget *m_tab_list;
    GtkWidget *m_content_stack;
    GtkWidget *m_url_entry;
    
    std::vector<std::unique_ptr<BrowserTab>> m_tabs;
    std::vector<TabInfo> m_tab_info;
    int m_current_tab_index;
};

#endif // BROWSER_WINDOW_HPP