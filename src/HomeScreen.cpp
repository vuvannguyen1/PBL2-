#include "HomeScreen.h"

HomeScreen::HomeScreen(Font& f) : font(f),
    buttons{
        TextButton(font, L"Phim Đang Chiếu", 22, Vector2f(40, 120)),
        TextButton(font, L"Vé Của Tôi", 22, Vector2f(40, 170)),
        TextButton(font, L"Đặt Vé", 22, Vector2f(40, 220)),
        TextButton(font, L"Đăng nhập/ Đăng ký", 22, Vector2f(40, 800))
    },
    logo(font, L"CINExínè", 30)
{
    Color sidebar_logo(20, 118, 172);
    Color sidebar(13, 27, 42);

    // sidebar background
    sidebarRect.setSize({340.f, 1080.f});
    sidebarRect.setFillColor(sidebar);
    
    logo.setFillColor(sidebar_logo);
    logo.setPosition({40, 60});
}

void HomeScreen::update(Vector2f mouse, bool mousePressed, AppState& state) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].update(mouse);

        if (buttons[i].isClicked(mouse, mousePressed)) {
            if (i == 2) { // nút Đặt vé Online
                state = AppState::BOOKING;
            } else if (i == 0) { // Dashboard về HOME
                state = AppState::HOME;
            }
        }
    }
}

void HomeScreen::draw(RenderWindow& window) {
    window.draw(sidebarRect);
    window.draw(logo);
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].draw(window);
    }
}
