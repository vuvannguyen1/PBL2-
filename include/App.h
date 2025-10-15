#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "TextButton.h"
#include "HomeScreen.h"
#include "PosterSlider.h"
#include "AppState.h"
#include "LoginScreen.h"
#include "RegisterScreen.h"
#include "AuthService.h"

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
        LoginScreen login;
        AuthService auth;
        RegisterScreen registerScreen;

        bool mousePressed = false;
        Vector2f mousePos;
        string currentUser;

        void processEvents();
        void update(float);
        void render();
};