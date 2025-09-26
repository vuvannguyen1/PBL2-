#include "PosterSlider.h"

Slide::Slide(const Texture& tex, const Font& font) : 
    buttonLabel(font, L"Xem chi tiết", 22),
    sprite(tex)
    {
        sprite.setScale({0.36, 0.36});

        buttonBox.setSize({200.f, 50.f});
        buttonBox.setFillColor(Color(0, 0, 0, 180));
        buttonBox.setOutlineThickness(2);
        buttonBox.setOutlineColor(Color::White);

        buttonLabel.setFillColor(Color::White);
}

void Slide::setPosition(Vector2f pos) {
    sprite.setPosition(pos);

    FloatRect sb = sprite.getGlobalBounds();
    Vector2f btnPos = {
        sb.position.x + sb.size.x/2 - buttonBox.getSize().x/2,
        sb.position.y + sb.size.y + 20.f
    };
    buttonBox.setPosition(btnPos);
    buttonLabel.setPosition({btnPos.x + 25.f, btnPos.y + 12.f});
}

void Slide::draw(RenderWindow& window) {
    window.draw(sprite);
    window.draw(buttonBox);
    window.draw(buttonLabel);
}

bool Slide::isButtonClicked(Vector2f mouse) {
    return buttonBox.getGlobalBounds().contains(mouse);
}