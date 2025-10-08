#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Slide.h"

using namespace std;
using namespace sf;

class PosterSlider {
private:
    vector<Texture> textures;
    vector<Slide> slides;
    vector<CircleShape> dots;

    Text leftArrow, rightArrow;
    Font font;
    RectangleShape rightButton, leftButton;

    int currentIndex = 0;
    int targetIndex = 0;
    bool animating = false;
    bool clickedDot = false;
    float animTime = 0.35;
    float elapsed = 0;
    float easeInOutCubic(float x) const;
public:
    PosterSlider(Font&, RenderWindow&);
    void loadPosters(const vector<string>&, const Font&);
    void update(float, RenderWindow&);
    void draw(RenderWindow&);
    void handleEvent(const Vector2f&, bool);
    const Sprite& getSlidePosterSprite(int) const;
};
