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

        // ✅ FIX: Sắp xếp theo đúng thứ tự trong CSV để đồng bộ index
        vector<string> paths = {
            "../assets/posters/tu-chien-tren-khong.png",    // 0: TỬ CHIẾN TRÊN KHÔNG
            "../assets/posters/mai.png",                    // 1: MAI
            "../assets/posters/dao-pho-va-piano.png",       // 2: ĐÀO, PHỞ VÀ PIANO
            "../assets/posters/lat-mat-48h.png",            // 3: LẬT MẶT: 48H
            "../assets/posters/dune-part-two.png",          // 4: DUNE: PART TWO
            "../assets/posters/inside-out.png",             // 5: INSIDE OUT 2
            "../assets/posters/godzilla-x-kong.png",        // 6: GODZILLA X KONG
            "../assets/posters/spirited-away.png",          // 7: SPIRITED AWAY
            "../assets/posters/bo-gia-remastered.png",      // 8: BỐ GIÀ
            "../assets/posters/blue-beetle.png"             // 9: BLUE BEETLE
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
            DetailScreen detail(font, slider.getSelectedIndex(), currentUser);
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