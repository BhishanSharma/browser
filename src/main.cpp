#include "browser_window.hpp"
#include <exception>
#include <iostream>

int main(int argc, char** argv) {
    try {
        BrowserWindow browser;
        browser.run(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
