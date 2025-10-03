#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class LoginScreen {
    public:
        explicit LoginScreen(const Font&);

        // return true nếu muốn đóng (ESC / click ra ngoài / bấm X)
        bool update(Vector2f, bool);
        void draw(RenderWindow&);

    private:
        RectangleShape overlay, card;
        Text title;

        RectangleShape emailBox, passBox, btn;
        Text emailPH, passPH, btnText;
        Text linkForgot, linkCreate, closeX;
};
