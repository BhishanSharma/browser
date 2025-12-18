#include "browser_window.hpp"
#include <stdexcept>

BrowserWindow::BrowserWindow()
{
    m_app = gtk_application_new(
        "com.example.browser",
        G_APPLICATION_DEFAULT_FLAGS);

    if (!m_app)
    {
        throw std::runtime_error("Failed to create GtkApplication");
    }

    g_signal_connect(m_app, "activate", G_CALLBACK(on_activate), this);
}

BrowserWindow::~BrowserWindow()
{
    g_object_unref(m_app);
}

void BrowserWindow::run(int argc, char **argv)
{
    g_application_run(G_APPLICATION(m_app), argc, argv);
}

void BrowserWindow::on_activate(GtkApplication * /*app*/, gpointer user_data)
{
    auto *self = static_cast<BrowserWindow *>(user_data);
    self->create_ui();
    gtk_window_present(GTK_WINDOW(self->m_window));
}

void BrowserWindow::create_ui()
{
    m_window = gtk_application_window_new(m_app);
    gtk_window_set_default_size(GTK_WINDOW(m_window), 1400, 900);
    gtk_window_set_title(GTK_WINDOW(m_window), "Aurora Browser");

    // Refined modern CSS with proper sizing
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(css_provider,
        "* {"
        "  font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', system-ui, sans-serif;"
        "}"
        "window {"
        "  background: linear-gradient(135deg, #0d0d1a 0%, #1a1a2e 100%);"
        "}"
        ".toolbar {"
        "  background: rgba(25, 25, 40, 0.95);"
        "  backdrop-filter: blur(10px);"
        "  padding: 8px 12px;"
        "  border-bottom: 1px solid rgba(255, 255, 255, 0.06);"
        "}"
        ".url-container {"
        "  background: rgba(40, 40, 60, 0.5);"
        "  border: 1px solid rgba(100, 120, 200, 0.2);"
        "  border-radius: 10px;"
        "  padding: 1px;"
        "  margin: 0 10px;"
        "  transition: all 0.2s ease;"
        "}"
        ".url-container:focus-within {"
        "  background: rgba(45, 45, 65, 0.7);"
        "  border-color: rgba(100, 120, 200, 0.5);"
        "  box-shadow: 0 0 0 2px rgba(100, 120, 200, 0.1);"
        "}"
        ".url-entry {"
        "  background: transparent;"
        "  color: #e0e0e0;"
        "  border: none;"
        "  border-radius: 9px;"
        "  padding: 6px 14px;"
        "  font-size: 13px;"
        "  min-height: 28px;"
        "}"
        ".url-entry:focus {"
        "  outline: none;"
        "}"
        ".nav-button {"
        "  background: rgba(40, 40, 60, 0.4);"
        "  color: #b0b0c0;"
        "  border: 1px solid rgba(255, 255, 255, 0.04);"
        "  border-radius: 8px;"
        "  padding: 6px;"
        "  margin: 0 2px;"
        "  min-width: 32px;"
        "  min-height: 32px;"
        "  transition: all 0.15s ease;"
        "}"
        ".nav-button:hover {"
        "  background: rgba(80, 100, 180, 0.2);"
        "  color: #a0b0ff;"
        "  border-color: rgba(100, 120, 200, 0.3);"
        "}"
        ".nav-button:active {"
        "  background: rgba(60, 80, 160, 0.3);"
        "}"
        ".new-tab-button {"
        "  background: linear-gradient(135deg, #5865f2 0%, #7289da 100%);"
        "  color: #ffffff;"
        "  border: none;"
        "  border-radius: 8px;"
        "  padding: 6px 14px;"
        "  margin: 0 2px;"
        "  font-size: 13px;"
        "  font-weight: 500;"
        "  min-height: 32px;"
        "  transition: all 0.15s ease;"
        "}"
        ".new-tab-button:hover {"
        "  background: linear-gradient(135deg, #6875f5 0%, #8099e6 100%);"
        "  box-shadow: 0 2px 8px rgba(88, 101, 242, 0.3);"
        "}"
        "notebook {"
        "  background: #0d0d1a;"
        "}"
        "notebook > header {"
        "  background: rgba(20, 20, 32, 0.95);"
        "  border-bottom: 1px solid rgba(255, 255, 255, 0.05);"
        "  padding: 4px 6px 0 6px;"
        "  min-height: 36px;"
        "}"
        "notebook > header > tabs {"
        "  margin: 0;"
        "}"
        "notebook > header > tabs > tab {"
        "  background: rgba(30, 30, 45, 0.3);"
        "  color: rgba(255, 255, 255, 0.5);"
        "  border: 1px solid rgba(255, 255, 255, 0.03);"
        "  border-bottom: none;"
        "  border-radius: 8px 8px 0 0;"
        "  padding: 6px 12px;"
        "  margin: 0 2px 0 0;"
        "  font-size: 12px;"
        "  min-height: 32px;"
        "  transition: all 0.15s ease;"
        "}"
        "notebook > header > tabs > tab:hover {"
        "  background: rgba(40, 40, 60, 0.5);"
        "  color: rgba(255, 255, 255, 0.7);"
        "}"
        "notebook > header > tabs > tab:checked {"
        "  background: rgba(20, 20, 35, 0.9);"
        "  color: #ffffff;"
        "  border-top: 2px solid #5865f2;"
        "  border-left-color: rgba(255, 255, 255, 0.08);"
        "  border-right-color: rgba(255, 255, 255, 0.08);"
        "}"
        ".tab-label {"
        "  font-size: 12px;"
        "  font-weight: 400;"
        "}"
        ".tab-icon {"
        "  font-size: 14px;"
        "  margin-right: 4px;"
        "}"
        ".tab-close-button {"
        "  background: transparent;"
        "  color: rgba(255, 255, 255, 0.3);"
        "  border: none;"
        "  border-radius: 6px;"
        "  padding: 2px;"
        "  margin-left: 6px;"
        "  min-width: 18px;"
        "  min-height: 18px;"
        "  transition: all 0.15s ease;"
        "}"
        ".tab-close-button:hover {"
        "  background: rgba(255, 80, 80, 0.2);"
        "  color: #ff6b6b;"
        "}"
    );

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_object_unref(css_provider);

    // Main vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(m_window), vbox);

    // Toolbar
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_add_css_class(toolbar, "toolbar");
    gtk_box_append(GTK_BOX(vbox), toolbar);

    // Navigation buttons group
    GtkWidget *nav_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    
    // Back button
    GtkWidget *back_btn = gtk_button_new_from_icon_name("go-previous-symbolic");
    gtk_widget_add_css_class(back_btn, "nav-button");
    gtk_widget_set_tooltip_text(back_btn, "Back");
    g_signal_connect(back_btn, "clicked", G_CALLBACK(on_back), this);
    gtk_box_append(GTK_BOX(nav_box), back_btn);

    // Forward button
    GtkWidget *forward_btn = gtk_button_new_from_icon_name("go-next-symbolic");
    gtk_widget_add_css_class(forward_btn, "nav-button");
    gtk_widget_set_tooltip_text(forward_btn, "Forward");
    g_signal_connect(forward_btn, "clicked", G_CALLBACK(on_forward), this);
    gtk_box_append(GTK_BOX(nav_box), forward_btn);

    // Reload button
    GtkWidget *reload_btn = gtk_button_new_from_icon_name("view-refresh-symbolic");
    gtk_widget_add_css_class(reload_btn, "nav-button");
    gtk_widget_set_tooltip_text(reload_btn, "Reload");
    g_signal_connect(reload_btn, "clicked", G_CALLBACK(on_reload), this);
    gtk_box_append(GTK_BOX(nav_box), reload_btn);

    // Home button
    GtkWidget *home_btn = gtk_button_new_from_icon_name("go-home-symbolic");
    gtk_widget_add_css_class(home_btn, "nav-button");
    gtk_widget_set_tooltip_text(home_btn, "Home");
    g_signal_connect(home_btn, "clicked", G_CALLBACK(on_home), this);
    gtk_box_append(GTK_BOX(nav_box), home_btn);

    gtk_box_append(GTK_BOX(toolbar), nav_box);

    // URL bar container
    GtkWidget *url_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_add_css_class(url_container, "url-container");
    gtk_widget_set_hexpand(url_container, TRUE);

    m_url_entry = gtk_entry_new();
    gtk_widget_add_css_class(m_url_entry, "url-entry");
    gtk_widget_set_hexpand(m_url_entry, TRUE);
    gtk_entry_set_placeholder_text(GTK_ENTRY(m_url_entry), "Search or enter address");
    g_signal_connect(m_url_entry, "activate", G_CALLBACK(on_url_activate), this);
    
    gtk_box_append(GTK_BOX(url_container), m_url_entry);
    gtk_box_append(GTK_BOX(toolbar), url_container);

    // New tab button
    GtkWidget *new_tab_btn = gtk_button_new_with_label("+ New Tab");
    gtk_widget_add_css_class(new_tab_btn, "new-tab-button");
    gtk_widget_set_tooltip_text(new_tab_btn, "New Tab (Ctrl+T)");
    g_signal_connect(new_tab_btn, "clicked", G_CALLBACK(on_new_tab), this);
    gtk_box_append(GTK_BOX(toolbar), new_tab_btn);

    // Notebook for tabs
    m_notebook = gtk_notebook_new();
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(m_notebook), TRUE);
    gtk_notebook_set_show_border(GTK_NOTEBOOK(m_notebook), FALSE);
    gtk_widget_set_vexpand(m_notebook, TRUE);
    gtk_box_append(GTK_BOX(vbox), m_notebook);

    // Setup download handling
    WebKitWebContext *context = webkit_web_context_get_default();
    g_signal_connect(
        context,
        "download-started",
        G_CALLBACK(BrowserWindow::on_download_started),
        this);

    // Add initial tab
    add_tab();
}

void BrowserWindow::add_tab()
{
    auto tab = std::make_unique<BrowserTab>();
    WebKitWebView *webview = tab->webview();

    g_signal_connect(
        webview,
        "load-changed",
        G_CALLBACK(BrowserWindow::on_load_changed),
        this);

    g_signal_connect(
        webview,
        "notify::title",
        G_CALLBACK(BrowserWindow::on_title_changed),
        this);

    // Tab label
    GtkWidget *tab_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    
    // Favicon
    GtkWidget *icon = gtk_label_new("🌐");
    gtk_widget_add_css_class(icon, "tab-icon");
    gtk_box_append(GTK_BOX(tab_box), icon);
    
    GtkWidget *label = gtk_label_new("New Tab");
    gtk_widget_add_css_class(label, "tab-label");
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_label_set_max_width_chars(GTK_LABEL(label), 20);
    
    GtkWidget *close_btn = gtk_button_new_from_icon_name("window-close-symbolic");
    gtk_widget_add_css_class(close_btn, "tab-close-button");
    gtk_widget_set_tooltip_text(close_btn, "Close");
    gtk_button_set_has_frame(GTK_BUTTON(close_btn), FALSE);
    
    gtk_box_append(GTK_BOX(tab_box), label);
    gtk_box_append(GTK_BOX(tab_box), close_btn);

    // Container for webview
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(container, TRUE);
    gtk_widget_set_vexpand(container, TRUE);

    GtkWidget *webview_widget = tab->widget();
    gtk_widget_set_hexpand(webview_widget, TRUE);
    gtk_widget_set_vexpand(webview_widget, TRUE);

    gtk_box_append(GTK_BOX(container), webview_widget);

    int page_num = gtk_notebook_append_page(
        GTK_NOTEBOOK(m_notebook),
        container,
        tab_box);

    // Connect close button
    g_object_set_data(G_OBJECT(close_btn), "page-num", GINT_TO_POINTER(page_num));
    g_signal_connect(close_btn, "clicked", G_CALLBACK(on_close_tab), this);

    // Switch to new tab
    gtk_notebook_set_current_page(GTK_NOTEBOOK(m_notebook), page_num);

    tab->load_uri("https://www.google.com");
    m_tabs.push_back(std::move(tab));
}

BrowserTab *BrowserWindow::current_tab()
{
    int page = gtk_notebook_get_current_page(GTK_NOTEBOOK(m_notebook));
    if (page < 0 || page >= static_cast<int>(m_tabs.size()))
    {
        return nullptr;
    }
    return m_tabs[page].get();
}

void BrowserWindow::on_new_tab(GtkButton *, gpointer user_data)
{
    static_cast<BrowserWindow *>(user_data)->add_tab();
}

void BrowserWindow::on_close_tab(GtkButton *button, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    int page_num = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "page-num"));
    
    if (browser->m_tabs.size() <= 1) {
        return;
    }
    
    gtk_notebook_remove_page(GTK_NOTEBOOK(browser->m_notebook), page_num);
    browser->m_tabs.erase(browser->m_tabs.begin() + page_num);
}

void BrowserWindow::on_back(GtkButton *, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    auto *tab = browser->current_tab();
    if (tab && webkit_web_view_can_go_back(tab->webview()))
    {
        webkit_web_view_go_back(tab->webview());
    }
}

void BrowserWindow::on_forward(GtkButton *, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    auto *tab = browser->current_tab();
    if (tab && webkit_web_view_can_go_forward(tab->webview()))
    {
        webkit_web_view_go_forward(tab->webview());
    }
}

void BrowserWindow::on_reload(GtkButton *, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    auto *tab = browser->current_tab();
    if (tab)
    {
        webkit_web_view_reload(tab->webview());
    }
}

void BrowserWindow::on_home(GtkButton *, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    auto *tab = browser->current_tab();
    if (tab)
    {
        tab->load_uri("https://www.google.com");
    }
}

void BrowserWindow::on_url_activate(GtkEntry *entry, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    auto *tab = browser->current_tab();
    if (!tab)
        return;

    const char *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    std::string uri(text);

    // Smart URL handling
    if (uri.find("://") == std::string::npos)
    {
        if (uri.find('.') != std::string::npos && uri.find(' ') == std::string::npos)
        {
            uri = "https://" + uri;
        }
        else
        {
            // URL encode the search query
            std::string encoded;
            for (char c : uri) {
                if (c == ' ') encoded += '+';
                else encoded += c;
            }
            uri = "https://www.google.com/search?q=" + encoded;
        }
    }

    tab->load_uri(uri.c_str());
}

static std::string get_download_path(const char *uri)
{
    const char *home = g_get_home_dir();
    const char *filename = g_path_get_basename(uri);
    return std::string(home) + "/Downloads/" + filename;
}

void BrowserWindow::on_download_started(
    WebKitWebContext *,
    WebKitDownload *download,
    gpointer user_data)
{
    auto *self = static_cast<BrowserWindow *>(user_data);

    WebKitURIRequest *request = webkit_download_get_request(download);
    const char *uri = webkit_uri_request_get_uri(request);
    if (!uri)
        return;

    std::string path = get_download_path(uri);
    std::string destination = "file://" + path;

    webkit_download_set_destination(download, destination.c_str());

    g_signal_connect(
        download,
        "finished",
        G_CALLBACK(BrowserWindow::on_download_finished),
        self);

    g_print("Download started: %s\n", path.c_str());
}

void BrowserWindow::on_download_finished(
    WebKitDownload *,
    gpointer)
{
    g_print("Download completed\n");
}

void BrowserWindow::on_load_changed(
    WebKitWebView *webview,
    WebKitLoadEvent load_event,
    gpointer user_data)
{
    if (load_event != WEBKIT_LOAD_COMMITTED)
        return;

    auto *self = static_cast<BrowserWindow *>(user_data);
    const char *uri = webkit_web_view_get_uri(webview);

    if (uri)
    {
        gtk_editable_set_text(
            GTK_EDITABLE(self->m_url_entry),
            uri);
    }
}

void BrowserWindow::on_title_changed(
    WebKitWebView *webview,
    GParamSpec *,
    gpointer user_data)
{
    auto *self = static_cast<BrowserWindow *>(user_data);
    const char *title = webkit_web_view_get_title(webview);

    if (title)
    {
        // Update window title
        std::string window_title = std::string(title) + " - Aurora Browser";
        gtk_window_set_title(
            GTK_WINDOW(self->m_window),
            window_title.c_str());

        // Update tab label
        int current_page = gtk_notebook_get_current_page(GTK_NOTEBOOK(self->m_notebook));
        GtkWidget *tab_label = gtk_notebook_get_tab_label(
            GTK_NOTEBOOK(self->m_notebook),
            gtk_notebook_get_nth_page(GTK_NOTEBOOK(self->m_notebook), current_page));

        if (tab_label && GTK_IS_BOX(tab_label))
        {
            // Skip the icon, get the label (second child)
            GtkWidget *child = gtk_widget_get_first_child(tab_label);
            if (child) child = gtk_widget_get_next_sibling(child);
            
            if (child && GTK_IS_LABEL(child))
            {
                gtk_label_set_text(GTK_LABEL(child), title);
            }
        }
    }
}