#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class BookingScreen {
    private:
        RectangleShape box;
        Text title;
    public:
        BookingScreen(const Font&);
        void update();
        void draw(RenderWindow&);
};