#include "HomeScreen.h"
#include <iostream>

HomeScreen::HomeScreen(const Font& font) : buttons {
    buttons[0] = TextButton(font, "Dashboard", 22, {40, 120}),
    buttons[1] = TextButton(font, "Movie", 22, {40, 170}),
    buttons[2] = TextButton(font, L"Đặt Vé Online", 22, {40, 220}),
    buttons[3] = TextButton(font, "Music", 22, {40, 270})
}  {}

void HomeScreen::update(const Vector2f& mousePos, bool mousePressed, AppState& state) {
    for (int i = 0; i < BTN_COUNT; i++) {
        buttons[i].update(mousePos);
        if (buttons[i].isClicked(mousePos, mousePressed)) {
            if (i == 2) state = AppState::BOOKING;
            else state = AppState::HOME;
        }
    }
}

void HomeScreen::draw(RenderWindow& window) {
    for (int i = 0; i < BTN_COUNT; i++) buttons[i].draw(window);
}


