// ============================================================================
// browser_window.cpp - Now much cleaner!
// ============================================================================
#include "browser_window.hpp"
#include "../styles/browser_styles.hpp"
#include "../ui/browser_toolbar.hpp"
#include "../ui/browser_tab_label.hpp"
#include "../utils/url_utils.hpp"
#include <stdexcept>
#include "core/browser_config.hpp"

BrowserWindow::BrowserWindow()
{
    m_app = gtk_application_new("com.example.browser", G_APPLICATION_DEFAULT_FLAGS);
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

void BrowserWindow::on_activate(GtkApplication *, gpointer user_data)
{
    auto *self = static_cast<BrowserWindow *>(user_data);
    self->create_ui();
    gtk_window_present(GTK_WINDOW(self->m_window));
}

void BrowserWindow::create_ui()
{
    m_window = gtk_application_window_new(m_app);

    // Use config constants
    gtk_window_set_default_size(
        GTK_WINDOW(m_window),
        BrowserConfig::DEFAULT_WINDOW_WIDTH,
        BrowserConfig::DEFAULT_WINDOW_HEIGHT);

    // Set window title with version
    std::string title = std::string(BrowserConfig::BROWSER_NAME) +
                        " v" + BrowserConfig::BROWSER_VERSION;
    gtk_window_set_title(GTK_WINDOW(m_window), title.c_str());

    // Apply styles
    apply_styles();

    // Create layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(m_window), vbox);

    // Create toolbar
    GtkWidget *toolbar = BrowserToolbar::create(this, &m_url_entry);
    g_signal_connect(m_url_entry, "activate", G_CALLBACK(on_url_activate), this);
    gtk_box_append(GTK_BOX(vbox), toolbar);

    // Create notebook
    m_notebook = gtk_notebook_new();
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(m_notebook), TRUE);
    gtk_notebook_set_show_border(GTK_NOTEBOOK(m_notebook), FALSE);
    gtk_widget_set_vexpand(m_notebook, TRUE);
    gtk_box_append(GTK_BOX(vbox), m_notebook);

    // Setup download handling
    setup_download_handler();

    // Add initial tab
    add_tab();
}

void BrowserWindow::apply_styles()
{
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(css_provider, BrowserStyles::get_css());
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(css_provider);
}

void BrowserWindow::setup_download_handler()
{
    WebKitWebContext *context = webkit_web_context_get_default();
    g_signal_connect(context, "download-started",
                     G_CALLBACK(on_download_started), this);
}

void BrowserWindow::add_tab()
{
    auto tab = std::make_unique<BrowserTab>();
    WebKitWebView *webview = tab->webview();

    // Connect signals
    g_signal_connect(webview, "load-changed", G_CALLBACK(on_load_changed), this);
    g_signal_connect(webview, "notify::title", G_CALLBACK(on_title_changed), this);

    // Create container
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(container, TRUE);
    gtk_widget_set_vexpand(container, TRUE);

    GtkWidget *webview_widget = tab->widget();
    gtk_widget_set_hexpand(webview_widget, TRUE);
    gtk_widget_set_vexpand(webview_widget, TRUE);
    gtk_box_append(GTK_BOX(container), webview_widget);

    // Create tab label first with temporary page number
    GtkWidget *tab_label = BrowserTabLabel::create(m_tabs.size(), this);

    // Add to notebook
    int page_num = gtk_notebook_append_page(
        GTK_NOTEBOOK(m_notebook),
        container,
        tab_label);

    // Update the close button's page number now that we know it
    GtkWidget *close_btn = gtk_widget_get_last_child(tab_label);
    if (close_btn)
    {
        g_object_set_data(G_OBJECT(close_btn), "page-num", GINT_TO_POINTER(page_num));
    }

    gtk_notebook_set_current_page(GTK_NOTEBOOK(m_notebook), page_num);
    tab->load_uri(BrowserConfig::DEFAULT_HOMEPAGE);
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

// Event handlers
void BrowserWindow::on_new_tab(GtkButton *, gpointer user_data)
{
    static_cast<BrowserWindow *>(user_data)->add_tab();
}

void BrowserWindow::on_close_tab(GtkButton *button, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    if (browser->m_tabs.size() <= 1)
        return;

    int page_num = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "page-num"));
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
    std::string uri = UrlUtils::normalize_url(text);
    tab->load_uri(uri.c_str());
}

void BrowserWindow::on_download_started(WebKitWebContext *, WebKitDownload *download, gpointer user_data)
{
    WebKitURIRequest *request = webkit_download_get_request(download);
    const char *uri = webkit_uri_request_get_uri(request);
    if (!uri)
        return;

    std::string path = UrlUtils::get_download_path(uri);
    std::string destination = "file://" + path;
    webkit_download_set_destination(download, destination.c_str());

    g_signal_connect(download, "finished", G_CALLBACK(on_download_finished), user_data);
    g_print("Download started: %s\n", path.c_str());
}

void BrowserWindow::on_download_finished(WebKitDownload *, gpointer)
{
    g_print("Download completed\n");
}

void BrowserWindow::on_load_changed(WebKitWebView *webview, WebKitLoadEvent load_event, gpointer user_data)
{
    if (load_event != WEBKIT_LOAD_COMMITTED)
        return;

    auto *self = static_cast<BrowserWindow *>(user_data);
    const char *uri = webkit_web_view_get_uri(webview);
    if (uri)
    {
        gtk_editable_set_text(GTK_EDITABLE(self->m_url_entry), uri);
    }
}

void BrowserWindow::on_title_changed(WebKitWebView *webview, GParamSpec *, gpointer user_data)
{
    auto *self = static_cast<BrowserWindow *>(user_data);
    const char *title = webkit_web_view_get_title(webview);
    if (!title)
        return;

    // Update window title with browser name
    std::string window_title = std::string(title) + " - " +
                               BrowserConfig::BROWSER_NAME;
    gtk_window_set_title(GTK_WINDOW(self->m_window), window_title.c_str());

    // Update tab label
    int current_page = gtk_notebook_get_current_page(GTK_NOTEBOOK(self->m_notebook));
    GtkWidget *tab_label = gtk_notebook_get_tab_label(
        GTK_NOTEBOOK(self->m_notebook),
        gtk_notebook_get_nth_page(GTK_NOTEBOOK(self->m_notebook), current_page));

    BrowserTabLabel::update_title(tab_label, title);
}