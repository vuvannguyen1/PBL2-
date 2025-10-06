// #pragma once
// #include <SFML/Graphics.hpp>
// #include <string>
// using namespace sf;
// using namespace std;

// class LoginScreen {
// private:
//     RectangleShape overlay, card;
//     Text title;

//     RectangleShape emailBox, passBox, btn;
//     Text emailPH, passPH, btnText;
//     Text linkForgot, linkCreate, closeX;

//     wstring emailInput, passInput;   // lưu text nhập vào
//     Text emailDisplay, passDisplay;  // text hiển thị
//     bool emailActive = false;
//     bool passActive  = false;

// public:
//     LoginScreen(const Font&);

//     // phải có event để xử lý nhập ký tự
//     bool update(Vector2f mouse, bool mousePressed, const Event& event);

//     void draw(RenderWindow&);
// };

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "AuthService.h"

class LoginScreen {
public:
    LoginScreen(const sf::Font& font, AuthService& auth);

    // return true nếu yêu cầu đóng modal (ESC/click ra ngoài/X)
    bool update(sf::Vector2f mouse, bool mousePressed, const sf::Event& event);

    void draw(sf::RenderWindow& window);

private:
    AuthService& auth;
    // overlay + card
    sf::RectangleShape overlay, card;

    // inputs & labels
    sf::RectangleShape emailBox, passBox, btn;
    sf::Text title, emailPH, passPH, btnText, linkForgot, linkCreate, closeX;
    sf::Text emailDisplay, passDisplay, msg;

    // state
    bool emailActive = false, passActive = false;
    std::wstring emailInput, passInput;

    // helpers
    static std::wstring bullets(std::size_t n);
};
