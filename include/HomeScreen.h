#pragma once
#include <SFML/Graphics.hpp>
#include "TextButton.h"
using namespace sf;

enum class AppState {
    HOME,
    BOOKING
};

class HomeScreen {
private:
    Font& font;
    Text logo;
    RectangleShape sidebarRect;
    static const int BUTTON_COUNT = 4;
    TextButton buttons[BUTTON_COUNT];

public:
    HomeScreen(Font&);
    void update(Vector2f, bool, AppState&);
    void draw(RenderWindow&);
};