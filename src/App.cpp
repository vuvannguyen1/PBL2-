#include "App.h"

App::App() : 
    window(VideoMode({1728, 972}), L"CiNeXíNè", Style::Titlebar | Style::Close),
    home(font),
    slider(font, window)
    {
        window.setFramerateLimit(60);
        
        Image icon("../assets/icon.png");
        window.setIcon(icon);

        font = Font("../assets/Montserrat_SemiBold.ttf");

        vector<string> paths = {
            "../assets/posters/blue-beetle.png",
            "../assets/posters/dao-pho-va-piano.png",
            "../assets/posters/dune-part-two.png",
            "../assets/posters/godzilla-x-kong.png",
            "../assets/posters/inside-out.png",
            "../assets/posters/lat-mat-48h.png",
            "../assets/posters/mai.png",
            "../assets/posters/tu-chien-tren-khong.png",
            "../assets/posters/spirited-away.png",
            "../assets/posters/bo-gia-remastered.png"
        };
        
        slider.loadPosters(paths, font);
}

void App::run() {
    Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void App::processEvents() {
    mousePressed = false;

    while (auto event = window.pollEvent()) {
        if (event->is<Event::Closed>()) window.close();
        if (event->is<Event::MouseButtonPressed>()) mousePressed = true;
    }

    mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    switch (state) {
        case AppState::HOME:
            home.update(mousePos, mousePressed, state);
            break;
        case AppState::LOGIN:

            break;
        case AppState::REGISTER:

            break;
        case AppState::BOOKING:

            break;
    }
    slider.handleEvent(mousePos, mousePressed);
}

void App::update(float dt) {
    slider.update(dt, window);
}

void App::render() {
    window.clear(Color::Black);

    if (state == AppState::HOME) {
        home.draw(window);
        slider.draw(window);
    }

    window.display();
}