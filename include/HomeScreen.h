#pragma once
#include "TextButton.h"
#include "AppState.h"
#include <vector>
#include <string>

class HomeScreen {
    protected:
        Font& font;
        Texture background, searchbar;
        Sprite sprite1, sprite2;

        bool showDropdown = false;
        RectangleShape dropdownBox;
        TextButton myticketsButton, accountButton, logoutButton;

        string currentUser;
        bool isUserLoggedIn = false;
    public:
        static const int BUTTON_COUNT = 3;
        TextButton buttons[BUTTON_COUNT];
        HomeScreen(Font&);
        void update(Vector2f, bool, AppState&);
        void draw(RenderWindow&);
        void drawDropdown(RenderWindow& window);
        void setLoggedUser(const string& username);
        void updateDropdownPosition();
};