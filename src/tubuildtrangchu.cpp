#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "TextButton.h"
#include "BookingScreen.h"
#include "HomeScreen.h"
#include "PosterSlider.h"
#include "LoginScreen.h"
#include "AuthService.h"

using namespace sf;
using namespace std;

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

    AuthService auth("../data/users.csv");
    auth.ensureSampleUser();  // testuser/123456

    AppState state = AppState::HOME;
    HomeScreen home(font);
    BookingScreen booking(font);
    LoginScreen login(font, auth);

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
        return (x < 0.5f) ? 4*x*x*x : 1 - pow(-2*x + 2, 3)/2;
    };

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
            else if (auto key = event->getIf<Event::KeyPressed>()) {
                if (key->code == Keyboard::Key::Escape && state == AppState::LOGIN)
                    state = AppState::HOME; // ESC thoát login
            }
            else if (auto mouse = event->getIf<Event::MouseButtonPressed>()) {
                Vector2f clickPos = {(float)mouse->position.x, (float)mouse->position.y};
                mousePressed = true;

                if (state != AppState::LOGIN && !animating) {

                    // 🩵 Kiểm tra mũi tên trái/phải của slide hiện tại
                    if (slides[currentIndex].isLeftArrowClicked(clickPos)) {
                        prevIndex = currentIndex;
                        targetIndex = (currentIndex > 0) ? currentIndex - 1 : slides.size() - 1;
                        animating = true;
                        elapsed = 0;
                    }
                    else if (slides[currentIndex].isRightArrowClicked(clickPos)) {
                        prevIndex = currentIndex;
                        targetIndex = (currentIndex + 1) % slides.size();
                        animating = true;
                        elapsed = 0;
                    }

                    // 🟢 Dots chuyển nhanh
                    for (size_t i = 0; i < dots.size(); ++i) {
                        if (dots[i].getGlobalBounds().contains(clickPos) && i != currentIndex) {
                            prevIndex = currentIndex;
                            targetIndex = (int)i;
                            animating = true;
                            elapsed = 0;
                            clickedDot = true;
                        }
                    }

                    // 🟣 Nút "Xem chi tiết"
                    if (slides[currentIndex].isButtonClicked(clickPos)) {
                        cout << "Xem chi tiết phim index: " << currentIndex << endl;
                    }
                }
            }

            // ====== xử lý LOGIN ======
            if (state == AppState::LOGIN) {
                if (login.update(Vector2f(Mouse::getPosition(window)), mousePressed, *event)) {
                    state = AppState::HOME;
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
                dir = (targetIndex > prevIndex) ? 1 : -1;
                steps = abs(targetIndex - prevIndex);
            } else {
                int delta = targetIndex - prevIndex;
                if (delta > (int)slides.size()/2)  delta -= slides.size();
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
        } 
        else if (state == AppState::BOOKING) {
            booking.update(mouse, mousePressed, state);
        }

        // ==== draw ====
        window.clear(Color::Black);

        if (state == AppState::HOME || state == AppState::LOGIN)
            home.draw(window);
        else if (state == AppState::BOOKING)
            booking.draw(window);

        if (animating) {
            slides[prevIndex].draw(window);
            slides[targetIndex].draw(window);
        } else {
            slides[currentIndex].draw(window);
        }

        // Dots
        for (size_t i = 0; i < dots.size(); i++) {
            dots[i].setFillColor(i==currentIndex ? Color::White : Color(120,120,120));
            window.draw(dots[i]);
        }

        if (state == AppState::LOGIN)
            login.draw(window);

        window.display();
    }
}
