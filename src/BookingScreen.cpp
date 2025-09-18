#include "BookingScreen.h"

BookingScreen::BookingScreen(const Font& font) : title(font, "Booking UI here!", 28) {
    box.setSize({500, 400});
    box.setFillColor(Color(30, 40, 70));
    box.setPosition({450, 100});

    title.setFillColor(sf::Color::White);
    title.setPosition({500, 120});
}

void BookingScreen::update() {
    // sau này thêm logic: chọn ghế, nút confirm...
}

void BookingScreen::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(title);
}



