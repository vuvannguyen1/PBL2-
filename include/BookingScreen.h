#pragma once
#include <SFML/Graphics.hpp>
#include "HomeScreen.h"
using namespace sf;

struct MovieCard {
    sf::RectangleShape box;
    sf::Text title;
    bool selected = false;

    MovieCard(const Font& font, const String& name) 
        : title(font, name, 20) {
        title.setFillColor(Color(230, 230, 240));
    }
};

struct Seat {
    RectangleShape rect;
    bool booked;
    bool selected;
};

class BookingScreen {
private:
    static const int ROWS = 8;
    static const int COLS = 12;

    Seat seats[ROWS][COLS]; 
    RectangleShape box, screen, searchBar, moviePanel;
    Text title, screenLbl, legend, searchHint, movieHdr, logo;

public:
    BookingScreen(const Font&);
    void update(Vector2f, bool, AppState&);
    void draw(RenderWindow&);
};
