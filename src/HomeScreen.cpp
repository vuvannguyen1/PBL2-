#include "HomeScreen.h"

HomeScreen::HomeScreen(Font& f)
: font(f),
  buttons{
      TextButton(font, L"CiNeXíNè", 50, Vector2f(60.f, 40.f)),
      TextButton(font, L"Đăng nhập | Đăng ký", 22, Vector2f(1360.f, 50.f)),
      TextButton(font, L"Đặt vé ngay", 23, Vector2f(1150.f, 50.f))
  },
  background("../assets/background.png"),
  searchbar("../assets/search_bar.png"),
  sprite1(background),
  sprite2(searchbar)
{
    Color accent(20, 118, 172);

    sprite2.setPosition({720.f, 50.f});
    sprite2.setScale({0.2f, 0.2f});

    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].setOutlineColor(accent);
        buttons[i].setOutlineThickness(i == 0 ? 5.f : 2.f);
    }
}

void HomeScreen::update(Vector2f mouse, bool mousePressed, AppState& state) {
    for (int i = 0; i < BUTTON_COUNT; i++) {
        buttons[i].update(mouse);

        if (buttons[i].isClicked(mouse, mousePressed)) {
            switch (i) {
                case 0: state = AppState::HOME; break;
                case 1: state = AppState::LOGIN; break;
                case 2: state = AppState::BOOKING; break;
            }
        }
    }
}

void HomeScreen::draw(RenderWindow& window) {
    window.draw(sprite1);
    window.draw(sprite2);
    for (int i = 0; i < BUTTON_COUNT; i++)
        buttons[i].draw(window);
}
