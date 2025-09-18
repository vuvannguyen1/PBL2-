#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI.h"
#include "TextButton.h"
#include "BookingScreen.h"
#include "HomeScreen.h"
using namespace std;
using namespace sf;

int main() {
    const Color sidebar_logo(20, 118, 172);
    const Color BgDark3(20, 37, 61);
    const Color sidebar(13, 27, 42);

    auto modes = VideoMode::getFullscreenModes();
    VideoMode mode = modes[0];
    RenderWindow window(mode, L"CINEXINE");
    
    RectangleShape rectangle1({400.f, 1080.f});
    rectangle1.setFillColor(sidebar);

    Font font("C:/Users/Os/Desktop/PBL2/assets/Montserrat_SemiBold.ttf");

    Text text(font, L"CINExínè.", 30);
    text.setFillColor(sidebar_logo);
    text.setPosition({40, 60});

    const int BUTTON_COUNT = 4;
    TextButton buttons[BUTTON_COUNT] = {
        TextButton(font, "Dashboard", 22, Vector2f({40, 120})),
        TextButton(font, "Movie", 22, Vector2f({40, 170})),
        TextButton(font, L"Đặt Vé Online", 22, Vector2f({40, 220})),
        TextButton(font, "Music", 22, Vector2f({40, 270}))
    };

    // AppState state = AppState::HOME;
    // HomeScreen home(font);
    // BookingScreen booking(font);

    while (window.isOpen()) {
        bool mousePressed = false;
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();
            if (event->is<Event::MouseButtonPressed>()) mousePressed = true;
        }
        Vector2f mouse(Mouse::getPosition(window));
        for (int i = 0; i < BUTTON_COUNT; i++) {
            buttons[i].update(mouse);
            // if (buttons[i].isClicked(mouse, mousePressed)) {
            //     if (i == 2) { // nút Đặt Vé Online
            //     state = AppState::BOOKING;
            //     }
            //     else if (i == 0) { // nút Dashboard về HOME
            //     state = AppState::HOME;
            //     }
            // }
        }

        window.clear(BgDark3);
        
        window.draw(rectangle1);

        window.draw(text);

        for (int i = 0; i < BUTTON_COUNT; i++) buttons[i].draw(window);

        // if (state == AppState::HOME) {
        //     home.update(mouse, mousePressed, state);
        //     home.draw(window);
        // } 
        // else if (state == AppState::BOOKING) {
        //     booking.update();
        //     booking.draw(window);
        // }

        window.display();
    }
}

    
