#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AppState.h"
using namespace sf;
using namespace std;

class AccountScreen {
private:
    // UI Components
    Text welcomeText;
    RectangleShape logoutBtn;
    Text logoutBtnText;
    
    // User data
    string currentUser;
    
    // Hover effect
    bool isLogoutHovered = false;
    
public:
    AccountScreen(const Font&);
    
    void setCurrentUser(const string&);
    void update(Vector2f, bool, AppState&);
    void draw(RenderWindow&);
};