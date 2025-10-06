#include "PosterSlider.h"

Slide::Slide(const Texture& tex, const Font& font) : 
    buttonLabel(font, L"Xem chi tiết", 22),
    sprite(tex),
    leftArrow(font, "<", 50),
    rightArrow(font, ">", 50)
    {
        sprite.setScale({0.36, 0.36});

        buttonBox.setSize({200.f, 50.f});
        buttonBox.setFillColor(Color(0, 0, 0, 180));
        buttonBox.setOutlineThickness(2);
        buttonBox.setOutlineColor(Color::White);

        buttonLabel.setFillColor(Color::White);

        leftArrow.setFillColor(Color::White);
        rightArrow.setFillColor(Color::White);
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

    // leftArrow.setPosition({525.f, window.getSize().y / 2.f - 25.f});
    // rightArrow.setPosition({window.getSize().x - 550.f, window.getSize().y / 2.f - 25.f});

    leftArrow.setPosition({pos.x - 100.f, pos.y + sb.size.y / 2});
    rightArrow.setPosition({pos.x + sb.size.x + 50.f, pos.y + sb.size.y / 2});
}

void Slide::draw(RenderWindow& window) {
    window.draw(sprite);
    window.draw(buttonBox);
    window.draw(buttonLabel);

    // tính lại vị trí mũi tên theo cửa sổ
    float centerY = window.getSize().y / 2.f;
    leftArrow.setPosition({525.f, centerY - 25.f});
    rightArrow.setPosition({window.getSize().x - 550.f, centerY - 25.f});

    window.draw(leftArrow);
    window.draw(rightArrow);
}

bool Slide::isButtonClicked(Vector2f mouse) {
    return buttonBox.getGlobalBounds().contains(mouse);
}

bool Slide::isLeftArrowClicked(Vector2f mouse) {
    return leftArrow.getGlobalBounds().contains(mouse);
}

bool Slide::isRightArrowClicked(Vector2f mouse) {
    return rightArrow.getGlobalBounds().contains(mouse);
}
