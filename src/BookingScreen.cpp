#include "BookingScreen.h"
using namespace std;

BookingScreen::BookingScreen(const Font& font)
: title(font, "Select Seats", 22),
  screenLbl(font, "SCREEN", 16),
  legend(font, "Legend: Green = Available | Gray = Booked | Yellow = Selected", 16),
  searchHint(font, "Search movie, time...", 18),
  movieHdr(font, "Now Showing", 22),
  logo(font, L"CINExínè", 30)
{
    // Panel box
    box.setSize({600.f, 630.f});
    box.setPosition({380.f, 90.f});
    box.setFillColor(Color(24, 24, 28));
    box.setOutlineThickness(2);
    box.setOutlineColor(Color(60, 60, 70));

    // Title
    title.setFillColor(Color(220, 220, 230));
    title.setPosition(box.getPosition() + Vector2f{16.f, 12.f});

    logo.setFillColor(Color(20, 118, 172));
    logo.setPosition({30, 15});

    // Seats
    Vector2f seatOrigin = box.getPosition() + Vector2f{32.f, 80.f};
    Vector2f seatSize   = {38.f, 32.f};

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            seats[r][c].rect.setSize(seatSize);
            seats[r][c].rect.setPosition(
                {seatOrigin.x + c * (seatSize.x + 8.f), seatOrigin.y + r * (seatSize.y + 10.f)}
            );
            seats[r][c].booked = (r == 2 && (c == 5 || c == 6)) || (r == 3 && c % 4 == 0) || (r == 6 && c > 8);
            seats[r][c].selected = false;
            seats[r][c].rect.setFillColor(seats[r][c].booked ? Color(100,100,110) : Color(40,160,80));
            seats[r][c].rect.setOutlineThickness(2);
            seats[r][c].rect.setOutlineColor(Color(70,70,80));
        }
    }

    // Screen
    screen.setSize({box.getSize().x - 52.f, 4.f});
    screen.setPosition(box.getPosition() + Vector2f{30.f, 64.f});
    screen.setFillColor(Color(0,170,255));

    screenLbl.setFillColor(Color(180,220,255));
    screenLbl.setPosition(screen.getPosition() + Vector2f{screen.getSize().x/2.f - 36.f, -24.f});

    // Legend
    legend.setFillColor(Color(200,200,210));
    legend.setPosition(box.getPosition() + Vector2f{30.f, box.getSize().y - 46.f});

    // ----- Search Bar -----
    searchBar.setSize({400.f, 40.f});
    searchBar.setPosition({260.f, 15.f});
    searchBar.setFillColor(sf::Color(32,32,38));
    searchBar.setOutlineThickness(2);
    searchBar.setOutlineColor(sf::Color(80,80,90));

    searchHint.setFillColor(sf::Color(160,160,170));
    searchHint.setPosition(searchBar.getPosition() + sf::Vector2f{12.f, 8.f});

    moviePanel.setSize({340.f, 720.f - 90.f});
    moviePanel.setPosition({20.f, 90.f});
    moviePanel.setFillColor(sf::Color(24,24,28));
    moviePanel.setOutlineThickness(2);
    moviePanel.setOutlineColor(sf::Color(60,60,70));

    movieHdr.setFillColor(sf::Color(220,220,230));
    movieHdr.setPosition(moviePanel.getPosition() + sf::Vector2f{16.f, 12.f});
}

void BookingScreen::update(Vector2f mouse, bool mousePressed, AppState& state) {
    if (mousePressed) {
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (seats[r][c].rect.getGlobalBounds().contains(mouse) && !seats[r][c].booked) {
                    seats[r][c].selected = !seats[r][c].selected;
                    seats[r][c].rect.setFillColor(seats[r][c].selected ? Color(230,200,60) : Color(40,160,80));
                }
            }
        }
    }
}

void BookingScreen::draw(RenderWindow& window) {
    window.draw(box);
    window.draw(title);
    window.draw(screen);
    window.draw(screenLbl);
    window.draw(legend);
    window.draw(searchBar);
    window.draw(searchHint);
    window.draw(movieHdr);
    window.draw(moviePanel);
    window.draw(logo);

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            window.draw(seats[r][c].rect);
        }
    }
}
