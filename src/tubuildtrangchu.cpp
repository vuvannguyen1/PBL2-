#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "UI.h"
#include "TextButton.h"
#include "BookingScreen.h"
#include "HomeScreen.h"
#include "PosterSlider.h"

int main() {
    RenderWindow window(
        VideoMode({1728u, 972u}),
        L"CINEXíNè",
        Style::Titlebar | Style::Close
    );

    window.setFramerateLimit(60);
    Image icon("../assets/icon.png");
    window.setIcon(icon);

    Font font("../assets/Montserrat_SemiBold.ttf");

    AppState state = AppState::HOME;
    HomeScreen home(font);
    BookingScreen booking(font);

    vector<Texture> textures;
    vector<Slide> slides;

    vector<string> paths = {
        "../assets/posters/blue-beetle.png",
        "../assets/posters/dao-pho-va-piano.png",
        "../assets/posters/dune-part-two.png",
        "../assets/posters/godzilla-x-kong.png",
        "../assets/posters/inside-out.png",
        "../assets/posters/lat-mat-48h.png",
        "../assets/posters/mai.png"
    };

    for (auto& p : paths) {
        Texture tex(p);
        textures.push_back(tex);
    }

    for (auto& tex : textures) {
        Slide slide(tex, font);

        FloatRect bounds = slide.sprite.getGlobalBounds();
        slide.setPosition({
            (window.getSize().x - bounds.size.x) / 2.f,
            (window.getSize().y - bounds.size.y) / 2.f
        });

        slides.push_back(slide);
    }

    Clock clock;
    float animTime = 0.5f;
    float elapsed = animTime; 
    int currentIndex = 0, targetIndex = 0, prevIndex = 0;
    bool animating = false;
    bool clickedDot = false;

    auto easeInOutCubic = [](float x) {
        return (x < 0.5f) ? 4*x*x*x : 1 - pow(-2*x+2, 3)/2;
    };

    Text leftArrow(font, "<", 50);
    Text rightArrow(font, ">", 50);
    leftArrow.setFillColor(Color::White);
    rightArrow.setFillColor(Color::White);

    leftArrow.setPosition({50.f, window.getSize().y / 2.f - 25.f});
    rightArrow.setPosition({window.getSize().x - 80.f, window.getSize().y / 2.f - 25.f});

    vector<CircleShape> dots;
    float dotRadius = 8.f;
    float spacing = 25.f;
    float totalWidth = (textures.size() - 1) * spacing;
    float startX = (window.getSize().x - totalWidth) / 2.f;
    float yPos = window.getSize().y - 50.f;

    for (size_t i = 0; i < textures.size(); ++i) {
        CircleShape dot(dotRadius);
        dot.setFillColor(Color(120, 120, 120));
        dot.setPosition({startX + i * spacing, yPos});
        dots.push_back(dot);
    }

    while (window.isOpen()) {
        bool mousePressed = false;

        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();
            else if (auto mouse = event->getIf<Event::MouseButtonPressed>()) {
                Vector2f clickPos = {(float)mouse->position.x, (float)mouse->position.y};
                mousePressed = true;

                if (!animating) {
                    if (leftArrow.getGlobalBounds().contains(clickPos)) {
                        prevIndex = currentIndex;
                        targetIndex = (currentIndex > 0) ? currentIndex - 1 : slides.size() - 1;
                        animating = true;
                        elapsed = 0;
                    }
                    if (rightArrow.getGlobalBounds().contains(clickPos)) {
                        prevIndex = currentIndex;
                        targetIndex = (currentIndex + 1) % slides.size();
                        animating = true;
                        elapsed = 0;
                    }
                    for (size_t i = 0; i < dots.size(); ++i) {
                        if (dots[i].getGlobalBounds().contains(clickPos) && i != currentIndex) {
                            prevIndex = currentIndex;
                            targetIndex = (int)i;
                            animating = true;
                            elapsed = 0;
                            clickedDot = true;
                        }
                    }
                    if (slides[currentIndex].isButtonClicked(clickPos)) {
                        cout << "Xem chi tiết phim index: " << currentIndex << endl;
                    }
                }
            }
        }

        float dt = clock.restart().asSeconds();
        if (animating) {
            elapsed += dt;
            float t = min(elapsed / animTime, 1.f);
            float p = easeInOutCubic(t);

            float W = (float)window.getSize().x;
            int dir = 0, steps = 1;

            if (clickedDot) {
                // Quy tắc mới khi click dot
                dir = (targetIndex > prevIndex) ? 1 : -1;
                steps = abs(targetIndex - prevIndex);
            } else {
                // Trường hợp bấm arrow vẫn giữ wrap-around
                int delta = targetIndex - prevIndex;
                if (delta >  (int)slides.size()/2)  delta -= slides.size();
                if (delta < -(int)slides.size()/2) delta += slides.size();
                dir = (delta > 0) ? 1 : -1;
                steps = abs(delta);
            }

            slides[prevIndex].setPosition({
                W/2 - slides[prevIndex].sprite.getGlobalBounds().size.x/2 - dir * p * W * steps,
                (window.getSize().y - slides[prevIndex].sprite.getGlobalBounds().size.y)/2.f
            });

            slides[targetIndex].setPosition({
                W/2 - slides[targetIndex].sprite.getGlobalBounds().size.x/2 + dir * (1-p) * W * steps,
                (window.getSize().y - slides[targetIndex].sprite.getGlobalBounds().size.y)/2.f
            });

            if (t >= 1.f) {
                currentIndex = targetIndex;
                animating = false;
                clickedDot = false;
            }
        } else {
            auto& s = slides[currentIndex];
            s.setPosition({
                (window.getSize().x - s.sprite.getGlobalBounds().size.x)/2.f,
                (window.getSize().y - s.sprite.getGlobalBounds().size.y)/2.f
            });
        }
        
        Vector2f mouse(Mouse::getPosition(window));

        if (state == AppState::HOME) {
            home.update(mouse, mousePressed, state);
            home.draw(window);
        } 
        else if (state == AppState::BOOKING) {
            booking.update(mouse, mousePressed, state);
            booking.draw(window);
        }

        if (animating) {
            slides[prevIndex].draw(window);
            slides[targetIndex].draw(window);
        } else {
            slides[currentIndex].draw(window);
        }

        window.draw(leftArrow);
        window.draw(rightArrow);
        for (size_t i = 0; i < dots.size(); i++) {
            dots[i].setFillColor(i==currentIndex ? Color::White : Color(120,120,120));
            window.draw(dots[i]);
        }        

        window.display();
    }
}

// #include <SFML/Graphics.hpp>
// #include <vector>
// #include <string>

// using namespace sf;
// using namespace std;

// void runMovieList() {
//     RenderWindow window(VideoMode({800, 600}), L"Demo Scroll List", Style::Titlebar | Style::Close);

//     Font font("../assets/Montserrat_SemiBold.ttf");
//     vector<Text> movies;
//     vector<string> names = {
//         "Avengers", "Inception", "Avatar", "Oppenheimer",
//         "Batman", "Spiderman", "Interstellar", "Frozen",
//         "Kungfu Panda", "Zootopia", "Elemental", "Inside Out"
//     };

//     // khởi tạo text
//     for (int i = 0; i < (int)names.size(); i++) {
//         Text txt(font, names[i], 24);
//         txt.setFillColor(Color::White);
//         txt.setPosition({100.f, 50.f + i * 40.f}); // khoảng cách 40px
//         movies.push_back(txt);
//     }

//     float scrollOffset = 0.f;

//     while (window.isOpen()) {
//         while (auto event = window.pollEvent()) {
//             if (event->is<Event::Closed>()) window.close();

//             if (auto* wheel = event->getIf<Event::MouseWheelScrolled>()) {
//                 scrollOffset += wheel->delta * 30.f;  // mỗi nấc trượt 30px
//             }
//         }

//         window.clear(Color(20, 37, 61));

//         for (int i = 0; i < (int)movies.size(); i++) {
//             movies[i].setPosition({100.f, 50.f + i * 40.f + scrollOffset});
//             window.draw(movies[i]);
//         }

//         window.display();
//     }
// }

// int main() {
//     runMovieList();
//     return 0;
// }
