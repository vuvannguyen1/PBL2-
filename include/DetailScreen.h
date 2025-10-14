#pragma once
#include <SFML/Graphics.hpp>
#include "Slide.h"
#include "HomeScreen.h"

using namespace sf;
using namespace std;

class DetailScreen : public HomeScreen {
private:
    Sprite poster;
    Text titleText, genreText, durationText, countryText, castText, descriptionText;

public:
    DetailScreen(Font&, const Slide&, const string& username);

    void update(Vector2f, bool, AppState&);
    void draw(RenderWindow&);
};
