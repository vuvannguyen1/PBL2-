#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class TextButton {
    private:
        Text text;
        bool hovered = false;
    public:
        TextButton(const Font&, const String&, unsigned int, Vector2f);
        void update(const Vector2f&);
        bool isClicked(const Vector2f&, bool) const;
        void draw(RenderWindow&) const;
};