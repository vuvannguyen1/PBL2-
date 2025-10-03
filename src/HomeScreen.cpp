#include "HomeScreen.h"

HomeScreen::HomeScreen(Font& f) : font(f),
    buttons{
        TextButton(font, L"CiNeXíNè", 50, Vector2f(60, 40)),
        TextButton(font, L"Đăng nhập | Đăng ký", 22, Vector2f(1360, 50)),
        TextButton(font, L"Đặt vé ngay", 23, Vector2f(1150, 50))
    },
    bg("../assets/background.png"),
    searchbar("../assets/search_bar.png"),
    sprite1(bg),
    sprite2(searchbar)
{
    Color sidebar_logo(20, 118, 172);
    Color sidebar(13, 27, 42);

    sprite2.setPosition({720, 50});
    sprite2.setScale({0.2, 0.2});

    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].setOutlineColor(sidebar_logo);
        if (i == 0) buttons[i].setOutlineThickness({5.f});
        else buttons[i].setOutlineThickness({2.f});
    }
}

void HomeScreen::update(Vector2f mouse, bool mousePressed, AppState& state) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].update(mouse);

        if (buttons[i].isClicked(mouse, mousePressed)) {
            switch (i) {
                case 0: 
                    state = AppState::HOME;
                    break;
                case 1:
                    state = AppState::LOGIN;
                    break;
                case 2:
                    // state = AppState::BOOKING;
                    break;
                default:
                    break;
            }
        }
    }
}

void HomeScreen::draw(RenderWindow& window) {
    window.draw(sprite1);
    window.draw(sprite2);
    for (int i = 0; i < BUTTON_COUNT; i++) buttons[i].draw(window);
}

