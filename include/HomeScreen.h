#pragma once
#include "TextButton.h"
#include "AppState.h"
#include <vector>
#include <string>

class HomeScreen {
    private:
        Font& font;
        Texture background, searchbar;
        Sprite sprite1, sprite2;

    public:
        static const int BUTTON_COUNT = 3;
        TextButton buttons[BUTTON_COUNT];
        HomeScreen(Font&);
        void update(Vector2f, bool, AppState&);
        void draw(RenderWindow&);
};