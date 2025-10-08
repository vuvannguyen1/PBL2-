#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "TextButton.h"
#include "HomeScreen.h"
#include "PosterSlider.h"
#include "AppState.h"

class App {
    public:
        App();
        void run();
    private:
        RenderWindow window;
        Font font;
        PosterSlider slider;

        AppState state = AppState::HOME;
        HomeScreen home;

        bool mousePressed = false;
        Vector2f mousePos;

        void processEvents();
        void update(float dt);
        void render();
};