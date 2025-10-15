#include "App.h"
#include "DetailScreen.h"
#include <fstream>
#include <sstream>

App::App() : 
    window(VideoMode({1728, 972}), L"CiNeXíNè", Style::Titlebar | Style::Close),
    font("../assets/Montserrat_SemiBold.ttf"),
    home(font),
    slider(font, window),
    auth("../data/users.csv"),
    login(font, auth),
    registerScreen(font, auth)
    { 
        window.setFramerateLimit(60);
        
        Image icon("../assets/icon.png");
        window.setIcon(icon);

        auth.ensureFile();
        auth.ensureSampleUser();

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

    while (auto optEvent = window.pollEvent()) {
        const Event& event = *optEvent;
        if (event.is<Event::Closed>()) window.close();
        if (event.is<Event::MouseButtonPressed>()) mousePressed = true;

        mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

        switch (state) {
            case AppState::HOME:
                home.setLoggedUser(currentUser);
                home.update(mousePos, mousePressed, state);
                break;

            case AppState::LOGIN:
                if (login.update(mousePos, mousePressed, event, currentUser, state)) {
                    home.setLoggedUser(currentUser);
                    state = AppState::HOME;
                }
                break;
            
            case AppState::REGISTER:
                if (registerScreen.update(mousePos, mousePressed, event))
                    state = AppState::LOGIN;

            default:
                break;
        }

    slider.handleEvent(mousePos, mousePressed, state);
    }
}

void App::update(float dt) {
    slider.update(dt, window);
}

void App::render() {
    window.clear(Color::Black);

    switch (state) {
        case AppState::HOME:
            home.draw(window);
            slider.draw(window);
            home.drawDropdown(window);
            break;

        case AppState::LOGIN:
            home.draw(window);
            slider.draw(window);
            login.draw(window);
            break;

        case AppState::REGISTER:
            home.draw(window);
            slider.draw(window);
            registerScreen.draw(window);
            break;

        case AppState::MOVIE_DETAILS: {
            DetailScreen detail(font, slider.getSelectedSlide(), currentUser);
            detail.update(mousePos, mousePressed, state);
            detail.draw(window);
            break;
        }

        default:
            break;
    }

    window.display();
}

// 