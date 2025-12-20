// ============================================================================
// browser_window.cpp - Custom tab bar in header with toolbar below
// ============================================================================
#include "core/browser_window.hpp"
#include "core/browser_config.hpp"
#include "../styles/browser_styles.hpp"
#include "../ui/browser_toolbar.hpp"
#include "../ui/browser_tab_label.hpp"
#include "../utils/url_utils.hpp"
#include <stdexcept>

BrowserWindow::BrowserWindow()
{
    m_app = gtk_application_new("com.example.browser", G_APPLICATION_DEFAULT_FLAGS);
    if (!m_app)
    {
        throw std::runtime_error("Failed to create GtkApplication");
    }
    g_signal_connect(m_app, "activate", G_CALLBACK(on_activate), this);
    m_current_tab_index = 0;
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

    gtk_window_set_default_size(
        GTK_WINDOW(m_window),
        BrowserConfig::DEFAULT_WINDOW_WIDTH,
        BrowserConfig::DEFAULT_WINDOW_HEIGHT);

    // std::string title = std::string(BrowserConfig::BROWSER_NAME) +
    //                     " v" + BrowserConfig::BROWSER_VERSION;
    // gtk_window_set_title(GTK_WINDOW(m_window), title.c_str());

    apply_styles();

    // Create header bar with tabs
    GtkWidget *header = gtk_header_bar_new();
    gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(header), TRUE);
    
    // Create custom tab bar
    create_tab_bar();
    
    // Pack tab bar to start and let it expand across the header (like colspan)
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header), m_tab_bar);
    
    // Remove default title to give full space to tabs
    gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), NULL);
    
    gtk_window_set_titlebar(GTK_WINDOW(m_window), header);

    // Create main vertical layout
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(m_window), vbox);

    // Create toolbar below header
    GtkWidget *toolbar = BrowserToolbar::create(this, &m_url_entry);
    g_signal_connect(m_url_entry, "activate", G_CALLBACK(on_url_activate), this);
    gtk_box_append(GTK_BOX(vbox), toolbar);

    // Create content stack for tab contents
    m_content_stack = gtk_stack_new();
    gtk_widget_set_vexpand(m_content_stack, TRUE);
    gtk_box_append(GTK_BOX(vbox), m_content_stack);

    setup_download_handler();

    // Add initial tab
    add_tab();
}

void BrowserWindow::create_tab_bar()
{
    // Main tab bar container
    m_tab_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_add_css_class(m_tab_bar, "tab-bar");
    gtk_widget_set_hexpand(m_tab_bar, TRUE);  // This makes it expand like colspan

    // Scrolled window for tabs
    GtkWidget *scrolled = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_NEVER);
    gtk_widget_set_hexpand(scrolled, TRUE);  // Allow scrolled window to expand
    gtk_widget_set_margin_start(scrolled, 0);
    gtk_widget_set_margin_end(scrolled, 0);

    // Container for tab buttons
    m_tab_list = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_margin_start(m_tab_list, 0);
    gtk_widget_set_margin_end(m_tab_list, 0);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), m_tab_list);

    gtk_box_append(GTK_BOX(m_tab_bar), scrolled);

    // New tab button at the end
    GtkWidget *new_tab_btn = gtk_button_new_from_icon_name("list-add-symbolic");
    gtk_widget_add_css_class(new_tab_btn, "new-tab-button");
    gtk_widget_set_tooltip_text(new_tab_btn, "New Tab");
    gtk_widget_set_margin_start(new_tab_btn, 0);
    g_signal_connect(new_tab_btn, "clicked", G_CALLBACK(on_new_tab), this);
    gtk_box_append(GTK_BOX(m_tab_bar), new_tab_btn);
}

void BrowserWindow::apply_styles()
{
    GtkCssProvider *css_provider = gtk_css_provider_new();

    // Enhanced CSS with custom tab bar styling
    std::string css = std::string(BrowserStyles::get_css()) + R"(
        .tab-bar {
            background: transparent;
            border: none;
            padding: 0;
            margin: 0;
        }
        
        .tab-button {
            background: rgba(255, 255, 255, 0.08);
            border: none;
            border-radius: 6px 6px 0 0;
            padding: 2px 8px;
            min-width: 100px;
            min-height: 24px;
            color: rgba(255, 255, 255, 0.9);
            margin: 0 1px 0 0;
            transition: all 200ms;
        }
        
        .tab-button:first-child {
            margin-left: 0;
        }
        
        .tab-button:hover {
            background: rgba(255, 255, 255, 0.12);
        }
        
        .tab-button.active {
            background: rgba(255, 255, 255, 0.18);
            color: #ffffff;
        }
        
        .tab-close {
            background: transparent;
            border: none;
            padding: 2px;
            margin-left: 6px;
            min-width: 14px;
            min-height: 14px;
            opacity: 0.6;
            border-radius: 3px;
        }
        
        .tab-close:hover {
            background: rgba(255, 50, 50, 0.4);
            opacity: 1;
        }
        
        .new-tab-button {
            background: transparent;
            border: none;
            border-radius: 4px;
            padding: 4px 8px;
            min-width: 30px;
            margin-left: 4px;
        }
        
        .new-tab-button:hover {
            background: rgba(255, 255, 255, 0.12);
        }
    )";

    gtk_css_provider_load_from_string(css_provider, css.c_str());
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
    int tab_index = m_tabs.size();

    // Connect signals
    g_signal_connect(webview, "load-changed", G_CALLBACK(on_load_changed), this);
    g_signal_connect(webview, "notify::title", G_CALLBACK(on_title_changed), this);

    // Create container for web content
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_hexpand(container, TRUE);
    gtk_widget_set_vexpand(container, TRUE);

    GtkWidget *webview_widget = tab->widget();
    gtk_widget_set_hexpand(webview_widget, TRUE);
    gtk_widget_set_vexpand(webview_widget, TRUE);
    gtk_box_append(GTK_BOX(container), webview_widget);

    // Add to stack with unique name
    std::string stack_name = "tab-" + std::to_string(tab_index);
    gtk_stack_add_named(GTK_STACK(m_content_stack), container, stack_name.c_str());

    // Create custom tab button
    GtkWidget *tab_button = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_add_css_class(tab_button, "tab-button");

    // Tab label
    GtkWidget *label = gtk_label_new("New Tab");
    gtk_label_set_ellipsize(GTK_LABEL(label), PANGO_ELLIPSIZE_END);
    gtk_label_set_max_width_chars(GTK_LABEL(label), 18);
    gtk_widget_set_hexpand(label, TRUE);
    
    // Make label text smaller
    PangoAttrList *attrs = pango_attr_list_new();
    pango_attr_list_insert(attrs, pango_attr_scale_new(PANGO_SCALE_SMALL));
    gtk_label_set_attributes(GTK_LABEL(label), attrs);
    pango_attr_list_unref(attrs);
    
    gtk_box_append(GTK_BOX(tab_button), label);

    // Close button
    GtkWidget *close_btn = gtk_button_new_from_icon_name("window-close-symbolic");
    gtk_widget_add_css_class(close_btn, "tab-close");
    gtk_widget_set_tooltip_text(close_btn, "Close Tab");
    g_object_set_data(G_OBJECT(close_btn), "tab-index", GINT_TO_POINTER(tab_index));
    g_signal_connect(close_btn, "clicked", G_CALLBACK(on_close_tab), this);
    gtk_box_append(GTK_BOX(tab_button), close_btn);

    // Make the whole tab button clickable
    GtkGesture *click = gtk_gesture_click_new();
    g_object_set_data(G_OBJECT(click), "tab-index", GINT_TO_POINTER(tab_index));
    g_object_set_data(G_OBJECT(tab_button), "tab-index-data", GINT_TO_POINTER(tab_index));
    g_signal_connect(click, "released", G_CALLBACK(on_tab_clicked), this);
    gtk_widget_add_controller(tab_button, GTK_EVENT_CONTROLLER(click));

    // Store references
    TabInfo info;
    info.button = tab_button;
    info.label = label;
    info.stack_name = stack_name;
    m_tab_info.push_back(info);

    gtk_box_append(GTK_BOX(m_tab_list), tab_button);

    // Switch to new tab
    switch_to_tab(tab_index);
    tab->load_uri(BrowserConfig::DEFAULT_HOMEPAGE);
    m_tabs.push_back(std::move(tab));
}

void BrowserWindow::switch_to_tab(int index)
{
    if (index < 0 || index >= static_cast<int>(m_tabs.size()))
        return;

    // Remove active class from all tabs
    for (const auto &info : m_tab_info)
    {
        gtk_widget_remove_css_class(info.button, "active");
    }

    // Add active class to selected tab
    gtk_widget_add_css_class(m_tab_info[index].button, "active");

    // Switch stack content
    gtk_stack_set_visible_child_name(GTK_STACK(m_content_stack),
                                     m_tab_info[index].stack_name.c_str());

    m_current_tab_index = index;

    // Update URL bar
    auto *tab = current_tab();
    if (tab)
    {
        const char *uri = webkit_web_view_get_uri(tab->webview());
        if (uri)
        {
            gtk_editable_set_text(GTK_EDITABLE(m_url_entry), uri);
        }
    }
}

BrowserTab *BrowserWindow::current_tab()
{
    if (m_current_tab_index < 0 || m_current_tab_index >= static_cast<int>(m_tabs.size()))
    {
        return nullptr;
    }
    return m_tabs[m_current_tab_index].get();
}

// Event handlers
void BrowserWindow::on_new_tab(GtkButton *, gpointer user_data)
{
    static_cast<BrowserWindow *>(user_data)->add_tab();
}

void BrowserWindow::on_tab_clicked(GtkGestureClick *gesture, int, double, double, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    
    // Try to get index from gesture first, then fall back to button
    int tab_index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(gesture), "tab-index"));
    
    // If gesture doesn't have index (after tab close/reorder), get from button
    if (tab_index == 0)
    {
        GtkWidget *button = gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(gesture));
        if (button)
        {
            tab_index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "tab-index-data"));
        }
    }
    
    browser->switch_to_tab(tab_index);
}

void BrowserWindow::on_close_tab(GtkButton *button, gpointer user_data)
{
    auto *browser = static_cast<BrowserWindow *>(user_data);
    if (browser->m_tabs.size() <= 1)
        return;

    int tab_index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "tab-index"));

    // Remove from UI
    gtk_box_remove(GTK_BOX(browser->m_tab_list), browser->m_tab_info[tab_index].button);

    // Remove from stack
    GtkWidget *child = gtk_stack_get_child_by_name(
        GTK_STACK(browser->m_content_stack),
        browser->m_tab_info[tab_index].stack_name.c_str());
    if (child)
    {
        gtk_stack_remove(GTK_STACK(browser->m_content_stack), child);
    }

    // Remove from vectors
    browser->m_tabs.erase(browser->m_tabs.begin() + tab_index);
    browser->m_tab_info.erase(browser->m_tab_info.begin() + tab_index);

    // Update indices for remaining tabs - we need to recreate gesture controllers
    for (size_t i = tab_index; i < browser->m_tab_info.size(); ++i)
    {
        // Store references
        GtkWidget *tab_btn = browser->m_tab_info[i].button;
        GtkWidget *close = gtk_widget_get_last_child(tab_btn);
        
        // Update close button index
        if (close)
        {
            g_object_set_data(G_OBJECT(close), "tab-index", GINT_TO_POINTER(i));
        }
        
        // Remove old gesture and add new one with updated index
        // Note: We can't easily update the gesture's data after creation,
        // so we'll store the index in the button itself for the gesture to read
        g_object_set_data(G_OBJECT(tab_btn), "tab-index-data", GINT_TO_POINTER(i));
    }

    // Switch to adjacent tab
    if (tab_index >= static_cast<int>(browser->m_tabs.size()))
    {
        browser->switch_to_tab(browser->m_tabs.size() - 1);
    }
    else
    {
        browser->switch_to_tab(tab_index);
    }
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
    if (uri && self->current_tab() && self->current_tab()->webview() == webview)
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

    // Find which tab this webview belongs to
    for (size_t i = 0; i < self->m_tabs.size(); ++i)
    {
        if (self->m_tabs[i]->webview() == webview)
        {
            // Update tab label
            gtk_label_set_text(GTK_LABEL(self->m_tab_info[i].label), title);
            
            // Don't update window title - we want to keep the header clean
            // The window title is only used for the taskbar/window list
            break;
        }
    }
}