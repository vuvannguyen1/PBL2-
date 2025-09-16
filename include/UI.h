#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class PillButton {
    public:
        RectangleShape box;
        Text label;
        bool hover = false;

        PillButton(const Font&, const wstring&, unsigned int);
        void draw(RenderWindow&);
};