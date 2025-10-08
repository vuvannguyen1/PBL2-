#include "PosterSlider.h"
#include <cmath>

PosterSlider::PosterSlider(Font& font, RenderWindow& window) : 
    font(font),
    leftArrow(font, "<", 48),
    rightArrow(font, ">", 48)
{
    rightButton.setSize({60.f, 100.f});
    rightButton.setFillColor(Color(0, 0, 0, 60));
    rightButton.setPosition({1400, (float)window.getSize().y / 2.f - 50.f});

    leftButton.setSize({60.f, 100.f});
    leftButton.setFillColor(Color(0, 0, 0, 60));
    leftButton.setPosition({268, (float)window.getSize().y / 2.f - 50.f});

    leftArrow.setFillColor(Color(255, 255, 255, 180));
    rightArrow.setFillColor(Color(255, 255, 255, 180));
    leftArrow.setPosition(leftButton.getPosition() + Vector2f(20.f, 15.f));
    rightArrow.setPosition(rightButton.getPosition() + Vector2f(20.f, 15.f));
}

void PosterSlider::loadPosters(const vector<string>& paths, const Font& font) {
    textures.clear();
    slides.clear();

    for (auto& p : paths) {
        Texture tex(p);
        textures.push_back(move(tex));
    }

    for (auto& tex : textures) {
        Slide slide(tex, font);
        slides.push_back(move(slide));
    }

    float dotRadius = 7.f;
    float spacing = 25.f;
    float totalWidth = (textures.size() - 1) * spacing;
    float startX = (1700 - totalWidth) / 2.f + 7;
    float yPos = 972 - 45.f;

    dots.clear();
    for (size_t i = 0; i < textures.size(); ++i) {
        CircleShape dot(dotRadius);
        dot.setOutlineThickness(0);
        dot.setOutlineColor(Color::White);
        dot.setFillColor(Color(120, 120, 120));
        dot.setPosition({ startX + i * spacing, yPos });
        dots.push_back(dot);
    }
}

void PosterSlider::update(float dt, RenderWindow& window) {
    if (slides.empty()) return;

    elapsed += dt;
    float t = min(elapsed / animTime, 1.f);
    float p = easeInOutCubic(t);

    float slideWidth = slides[0].getPosterSprite().getGlobalBounds().size.x;
    float centerY = (window.getSize().y - slides[0].getPosterSprite().getGlobalBounds().size.y) / 2.f;
    float centerX = window.getSize().x / 2.f;

    int dir = 0, steps = 1;

    if (clickedDot) {
        dir = (targetIndex > currentIndex) ? 1 : -1;
        steps = abs(targetIndex - currentIndex);
    } 
    else {
        int delta = targetIndex - currentIndex;
        if (delta > (int)slides.size()/2)  delta -= slides.size();
        if (delta < -(int)slides.size()/2) delta += slides.size();
        dir = (delta > 0) ? 1 : -1;
        steps = abs(delta);
    }


    if (animating) {
        // vị trí slide cũ (2 poster hiện tại)
        slides[currentIndex].setPosition({centerX - slideWidth - 20.f - dir * p * slideWidth, centerY});
        int nextOfCurrent = (currentIndex + 1) % slides.size();
        slides[nextOfCurrent].setPosition({centerX + 20.f - dir * p * slideWidth, centerY});

        // vị trí slide mới (2 poster kế tiếp)
        slides[targetIndex].setPosition({centerX - slideWidth - 20.f + dir * (1 - p) * slideWidth, centerY});
        int nextOfTarget = (targetIndex + 1) % slides.size();
        slides[nextOfTarget].setPosition({centerX + 20.f + dir * (1 - p) * slideWidth, centerY});

        if (t >= 1.f) {
            animating = false;
            currentIndex = targetIndex;
            clickedDot = false;
        }
    } 
    else {
        // Khi không animating, hiển thị 2 poster cố định
        slides[currentIndex].setPosition({centerX - slideWidth - 20.f, centerY});
        int nextIndex = (currentIndex + 1) % slides.size();
        slides[nextIndex].setPosition({centerX + 20.f, centerY});
    }
}

void PosterSlider::handleEvent(const sf::Vector2f& mousePos, bool mousePressed) {
    if (animating) return;

    for (size_t i = 0; i < slides.size(); ++i) {
        if (slides[i].isButtonClicked(mousePos, mousePressed)) {
            
            return;
        }
    }

    if (!mousePressed) return;

    if (leftArrow.getGlobalBounds().contains(mousePos) || leftButton.getGlobalBounds().contains(mousePos)) {
        targetIndex = (currentIndex - 1 + slides.size()) % slides.size();
        animating = true;
        elapsed = 0.f;
        return;
    }

    if (rightArrow.getGlobalBounds().contains(mousePos) || rightButton.getGlobalBounds().contains(mousePos)) {
        targetIndex = (currentIndex + 1) % slides.size();
        animating = true;
        elapsed = 0.f;
        return;
    }

    for (size_t i = 0; i < dots.size(); ++i) {
        if (dots[i].getGlobalBounds().contains(mousePos)) {
            targetIndex = i;
            animating = true;
            elapsed = 0.f;
            clickedDot = true;
            return;
        }
    }
}

void PosterSlider::draw(RenderWindow& window) {
    if (slides.empty()) return;

    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

    bool hoverLeft = leftButton.getGlobalBounds().contains(mousePos);
    bool hoverRight = rightButton.getGlobalBounds().contains(mousePos);

    slides[currentIndex].highlightButton(slides[currentIndex].isButtonHovered(mousePos));
    int nextIndex = (currentIndex + 1) % slides.size();
    slides[nextIndex].highlightButton(slides[nextIndex].isButtonHovered(mousePos));

    slides[currentIndex].draw(window);
    slides[nextIndex].draw(window);

    Color idleColor(0, 0, 0, 60);   
    Color hoverColor(0, 0, 0, 180); 
    Color iconIdle(255, 255, 255, 180);
    Color iconHover(255, 255, 255, 255);

    leftButton.setFillColor(hoverLeft ? hoverColor : idleColor);
    rightButton.setFillColor(hoverRight ? hoverColor : idleColor);
    leftArrow.setFillColor(hoverLeft ? iconHover : iconIdle);
    rightArrow.setFillColor(hoverRight ? iconHover : iconIdle);

    window.draw(leftButton);
    window.draw(leftArrow);
    window.draw(rightButton);
    window.draw(rightArrow);

    for (size_t i = 0; i < dots.size(); ++i) {
        bool isHovered = dots[i].getGlobalBounds().contains(mousePos);
        bool isActive = (i == static_cast<size_t>(currentIndex));
        dots[i].setFillColor(isActive ? Color::White : isHovered ? Color(135, 139, 208, 255) : Color(120, 120, 120));
        dots[i].setOutlineColor(Color::White);
        dots[i].setOutlineThickness(isHovered ? 2 : 0);
        window.draw(dots[i]);
    }
}

float PosterSlider::easeInOutCubic(float x) const {
    return (x < 0.5f)
        ? 5.f * x * x * x
        : 1.f - pow(-2.f * x + 2.f, 3.f) / 2.2f;
}

const Sprite& PosterSlider::getSlidePosterSprite(int idx) const {
    return slides[idx].getPosterSprite();
}