#include "ui/app.hpp"

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>

void runApp() {
    using namespace ftxui;
    auto document = hbox({
        text("Hash Cracker") | border,
        text(" — ready") | border,
    });
    auto screen = Screen::Create(Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
    std::cout << std::endl;
}
