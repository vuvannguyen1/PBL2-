#pragma once
#include "TextButton.h"
#include <vector>
#include <string>
using namespace std;

enum class AppState {
    HOME,
    LOGIN,
    BOOKING
};

class HomeScreen {
    private:
        Font& font;
        Texture bg, searchbar;
        Sprite sprite1, sprite2;

    public:
        static const int BUTTON_COUNT = 3;
        TextButton buttons[BUTTON_COUNT];
        HomeScreen(Font&);
        void update(Vector2f, bool, AppState&);
        void draw(RenderWindow&);
};