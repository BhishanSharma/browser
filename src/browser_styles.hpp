// ============================================================================
// browser_styles.hpp - CSS styling separated into its own module
// ============================================================================
#pragma once
#include <string>

namespace BrowserStyles {
    inline const char* get_css() {
        return R"(
            * {
                font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', system-ui, sans-serif;
            }
            window {
                background: linear-gradient(135deg, #0d0d1a 0%, #1a1a2e 100%);
            }
            .toolbar {
                background: rgba(25, 25, 40, 0.95);
                backdrop-filter: blur(10px);
                padding: 8px 12px;
                border-bottom: 1px solid rgba(255, 255, 255, 0.06);
            }
            .url-container {
                background: rgba(40, 40, 60, 0.5);
                border: 1px solid rgba(100, 120, 200, 0.2);
                border-radius: 10px;
                padding: 1px;
                margin: 0 10px;
                transition: all 0.2s ease;
            }
            .url-container:focus-within {
                background: rgba(45, 45, 65, 0.7);
                border-color: rgba(100, 120, 200, 0.5);
                box-shadow: 0 0 0 2px rgba(100, 120, 200, 0.1);
            }
            .url-entry {
                background: transparent;
                color: #e0e0e0;
                border: none;
                border-radius: 9px;
                padding: 6px 14px;
                font-size: 13px;
                min-height: 28px;
            }
            .url-entry:focus {
                outline: none;
            }
            .nav-button {
                background: rgba(40, 40, 60, 0.4);
                color: #b0b0c0;
                border: 1px solid rgba(255, 255, 255, 0.04);
                border-radius: 8px;
                padding: 6px;
                margin: 0 2px;
                min-width: 32px;
                min-height: 32px;
                transition: all 0.15s ease;
            }
            .nav-button:hover {
                background: rgba(80, 100, 180, 0.2);
                color: #a0b0ff;
                border-color: rgba(100, 120, 200, 0.3);
            }
            .nav-button:active {
                background: rgba(60, 80, 160, 0.3);
            }
            .new-tab-button {
                background: linear-gradient(135deg, #5865f2 0%, #7289da 100%);
                color: #ffffff;
                border: none;
                border-radius: 8px;
                padding: 6px 14px;
                margin: 0 2px;
                font-size: 13px;
                font-weight: 500;
                min-height: 32px;
                transition: all 0.15s ease;
            }
            .new-tab-button:hover {
                background: linear-gradient(135deg, #6875f5 0%, #8099e6 100%);
                box-shadow: 0 2px 8px rgba(88, 101, 242, 0.3);
            }
            notebook {
                background: #0d0d1a;
            }
            notebook > header {
                background: rgba(20, 20, 32, 0.95);
                border-bottom: 1px solid rgba(255, 255, 255, 0.05);
                padding: 4px 6px 0 6px;
                min-height: 36px;
            }
            notebook > header > tabs {
                margin: 0;
            }
            notebook > header > tabs > tab {
                background: rgba(30, 30, 45, 0.3);
                color: rgba(255, 255, 255, 0.5);
                border: 1px solid rgba(255, 255, 255, 0.03);
                border-bottom: none;
                border-radius: 8px 8px 0 0;
                padding: 6px 12px;
                margin: 0 2px 0 0;
                font-size: 12px;
                min-height: 32px;
                transition: all 0.15s ease;
            }
            notebook > header > tabs > tab:hover {
                background: rgba(40, 40, 60, 0.5);
                color: rgba(255, 255, 255, 0.7);
            }
            notebook > header > tabs > tab:checked {
                background: rgba(20, 20, 35, 0.9);
                color: #ffffff;
                border-top: 2px solid #5865f2;
                border-left-color: rgba(255, 255, 255, 0.08);
                border-right-color: rgba(255, 255, 255, 0.08);
            }
            .tab-label {
                font-size: 12px;
                font-weight: 400;
            }
            .tab-icon {
                font-size: 14px;
                margin-right: 4px;
            }
            .tab-close-button {
                background: transparent;
                color: rgba(255, 255, 255, 0.3);
                border: none;
                border-radius: 6px;
                padding: 2px;
                margin-left: 6px;
                min-width: 18px;
                min-height: 18px;
                transition: all 0.15s ease;
            }
            .tab-close-button:hover {
                background: rgba(255, 80, 80, 0.2);
                color: #ff6b6b;
            }
        )";
    }
}
