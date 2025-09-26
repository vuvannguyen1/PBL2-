#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Slide {
    private:
        // Sprite sprite;
        RectangleShape buttonBox;
        Text buttonLabel;
    public:
        Sprite sprite;
        Slide(const Texture&, const Font&);
        void setPosition(Vector2f);
        void draw(RenderWindow&);
        bool isButtonClicked(Vector2f);
};

