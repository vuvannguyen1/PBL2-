#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Slide {
    private:
        RectangleShape buttonBox;
        Text buttonLabel;
        Text leftArrow, rightArrow;
    public:
        Sprite sprite;
        Slide(const Texture&, const Font&);
        void setPosition(Vector2f);
        void draw(RenderWindow&);
        bool isButtonClicked(Vector2f);
        bool isLeftArrowClicked(Vector2f);
        bool isRightArrowClicked(Vector2f);
};

