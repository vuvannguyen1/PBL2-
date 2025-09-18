#include "TextButton.h"

TextButton::TextButton(const Font& font, const String& str, unsigned int size, Vector2f pos) : text(font, str, size) {
    text.setPosition(pos);
    text.setFillColor(Color(170, 182, 197));
}

void TextButton::update(const Vector2f& mousePos) {
    if (text.getGlobalBounds().contains(mousePos)) {
        hovered = true;
        text.setFillColor(Color(45, 156, 219));
    }
    else {
        hovered = false;
        text.setFillColor(Color(170, 182, 197));
    }
}

bool TextButton::isClicked(const Vector2f& mousePos, bool mousePressed) const {
    return hovered && mousePressed;
}

void TextButton::draw(RenderWindow& window) const {
    window.draw(text);
}