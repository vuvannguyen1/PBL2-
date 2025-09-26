#pragma once
#include "TextButton.h"
#include <vector>
#include <string>
using namespace std;

enum class AppState {
    HOME,
    BOOKING
};

class HomeScreen {
    private:
        Font& font;
        Texture bg, searchbar;
        Sprite sprite1, sprite2;
        static const int BUTTON_COUNT = 2;
        TextButton buttons[BUTTON_COUNT];

    public:
        HomeScreen(Font&);
        void update(Vector2f, bool, AppState&);
        void draw(RenderWindow&);
};

