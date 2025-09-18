#include <SFML\Graphics.hpp>
#include "UI.h"
using namespace std;
using namespace sf;

PillButton::PillButton(const Font& font, const wstring& str, unsigned int size = 20) : label(font, str, size) {}

void PillButton::draw(RenderWindow& w) {
    box.setFillColor(hover ? Color(255, 80, 80) : Color(230, 40, 40));
    w.draw(box);
    w.draw(label);
}

