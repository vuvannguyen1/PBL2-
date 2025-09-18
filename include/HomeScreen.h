#pragma once
#include <SFML/Graphics.hpp>
#include "TextButton.h"

enum class AppState {
    HOME, 
    BOOKING
};

class HomeScreen {
    private:
        static const int BTN_COUNT = 4;
        TextButton buttons[BTN_COUNT];
    public:
        HomeScreen(const Font&);
        void update(const Vector2f&, bool, AppState&);
        void draw(RenderWindow&);
};