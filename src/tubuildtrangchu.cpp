#include <SFML/Graphics.hpp>
#include <iostream>
#include "UI.h"
using namespace std;
using namespace sf;

int main() {
    auto modes = VideoMode::getFullscreenModes();
    VideoMode mode = modes[0];
    RenderWindow window(mode, L"CINEMA");

    const sf::Color BgDark3(13, 22, 51);
    Font font("C:/Windows/Fonts/times.ttf");
    Text text(font, L"CINEMA UI", 30);
    text.setFillColor(Color::Yellow);

    PillButton cta(font, L"ĐẶT VÉ NGAY", 20);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) window.close();
        }

        window.clear(BgDark3);
        window.draw(text);


        window.display();
    }
}

    
// }

// #include <SFML/Graphics.hpp>
// #include <bits/stdc++.h>
// using namespace std;

// struct MovieCard {
//     sf::RectangleShape box;
//     sf::Text title;
//     bool selected = false;

//     MovieCard(const sf::Font& font, const std::string& name) 
//         : title(font, name, 20) {
//         title.setFillColor(sf::Color(230,230,240));
//     }
// };

// struct Seat {
//     sf::RectangleShape rect;
//     bool booked = false;
//     bool selected = false;
// };

// static bool pointIn(const sf::FloatRect& r, const sf::Vector2f& p) {
//     return r.contains(p);
// }

// int main() {
//     sf::RenderWindow window(sf::VideoMode({1280, 720}), L"CINEMA");

//     const sf::Font font("C:/Windows/Fonts/times.ttf");

//     // ----- Header -----
//     sf::Text title(font, L"Cine xí nè", 36);
//     title.setFillColor(sf::Color(240, 240, 240));
//     title.setOutlineColor(sf::Color(0, 170, 255));
//     title.setOutlineThickness(2);
//     title.setPosition({24, 14});

//     sf::RectangleShape topBar({1280.f, 70.f});
//     topBar.setFillColor(sf::Color(18, 18, 22));
//     topBar.setPosition({0, 0});

//     // ----- Search Bar -----
//     sf::RectangleShape searchBar({400.f, 40.f});
//     searchBar.setPosition({260.f, 15.f});
//     searchBar.setFillColor(sf::Color(32,32,38));
//     searchBar.setOutlineThickness(2);
//     searchBar.setOutlineColor(sf::Color(80,80,90));

//     sf::Text searchHint(font, "Search movie, time...", 18);
//     searchHint.setFillColor(sf::Color(160,160,170));
//     searchHint.setPosition(searchBar.getPosition() + sf::Vector2f{12.f, 8.f});

//     // ----- Primary Panels -----
//     // Left: Movie list
//     sf::RectangleShape moviePanel({340.f, 720.f - 90.f});
//     moviePanel.setPosition({20.f, 90.f});
//     moviePanel.setFillColor(sf::Color(24,24,28));
//     moviePanel.setOutlineThickness(2);
//     moviePanel.setOutlineColor(sf::Color(60,60,70));

//     sf::Text movieHdr(font, "Now Showing", 22);
//     movieHdr.setFillColor(sf::Color(220,220,230));
//     movieHdr.setPosition(moviePanel.getPosition() + sf::Vector2f{16.f, 12.f});

//     // Middle: Seat map
//     sf::RectangleShape seatPanel({600.f, 720.f - 90.f});
//     seatPanel.setPosition({380.f, 90.f});
//     seatPanel.setFillColor(sf::Color(24,24,28));
//     seatPanel.setOutlineThickness(2);
//     seatPanel.setOutlineColor(sf::Color(60,60,70));

//     sf::Text seatHdr(font, "Select Seats", 22);
//     seatHdr.setFillColor(sf::Color(220,220,230));
//     seatHdr.setPosition(seatPanel.getPosition() + sf::Vector2f{16.f, 12.f});

//     // Right: Cart / Showtime
//     sf::RectangleShape cartPanel({260.f, 720.f - 90.f});
//     cartPanel.setPosition({1000.f, 90.f});
//     cartPanel.setFillColor(sf::Color(24,24,28));
//     cartPanel.setOutlineThickness(2);
//     cartPanel.setOutlineColor(sf::Color(60,60,70));

//     sf::Text cartHdr(font, "Your Booking", 22);
//     cartHdr.setFillColor(sf::Color(220,220,230));
//     cartHdr.setPosition(cartPanel.getPosition() + sf::Vector2f{16.f, 12.f});

//     // ----- Movie Cards -----
//     vector<string> movieNames = {"Dune II", "Oppenheimer", "Inside Out 2", "Spider-Verse", "Top Gun: Maverick"};
//     vector<MovieCard> movies;
//     float y = moviePanel.getPosition().y + 50.f;
//     for (int i = 0; i < (int)movieNames.size(); ++i) {
//         MovieCard m(font, movieNames[i]); // phải truyền font + text vào
//         m.box.setSize({moviePanel.getSize().x - 24.f, 86.f});
//         m.box.setPosition({moviePanel.getPosition().x + 12.f, y});
//         m.box.setFillColor(sf::Color(34,34,40));
//         m.box.setOutlineThickness(2);
//         m.box.setOutlineColor(sf::Color(70,70,80));

//         m.title.setPosition(m.box.getPosition() + sf::Vector2f{14.f, 12.f});
//         movies.push_back(m);
//         y += 100.f;
//     }
//     int selectedMovie = -1;

//     // ----- Showtimes (simple pills) -----
//     vector<string> times = {"10:00", "12:30", "15:00", "17:40", "20:15"};
//     vector<sf::RectangleShape> timePills;
//     vector<sf::Text> timeLabels;
//     float tx = cartPanel.getPosition().x + 16.f, ty = cartPanel.getPosition().y + 50.f;
//     for (auto &t : times) {
//         sf::RectangleShape pill({80.f, 34.f});
//         pill.setPosition({tx, ty});
//         pill.setFillColor(sf::Color(34,34,40));
//         pill.setOutlineThickness(2);
//         pill.setOutlineColor(sf::Color(70,70,80));
//         timePills.push_back(pill);

//         sf::Text label(font, t, 18);
//         label.setFillColor(sf::Color(210,210,220));
//         label.setPosition(pill.getPosition() + sf::Vector2f{12.f, 6.f});
//         timeLabels.push_back(label);

//         tx += 90.f;
//         if (tx + 80.f > cartPanel.getPosition().x + cartPanel.getSize().x - 16.f) {
//             tx = cartPanel.getPosition().x + 16.f;
//             ty += 44.f;
//         }
//     }
//     int selectedTime = -1;

//     // ----- Seat Map -----
//     const int ROWS = 8, COLS = 12;
//     vector<vector<Seat>> seats(ROWS, vector<Seat>(COLS));
//     sf::Vector2f seatOrigin = seatPanel.getPosition() + sf::Vector2f{32.f, 80.f};
//     sf::Vector2f seatSize   = {38.f, 32.f};
//     float gapX = 8.f, gapY = 10.f;

//     // fake booked pattern
//     auto booked = [&](int r, int c) {
//         return (r == 2 && (c==5 || c==6)) || (r==3 && c%4==0) || (r==6 && c>8);
//     };

//     for (int r=0; r<ROWS; ++r) {
//         for (int c=0; c<COLS; ++c) {
//             Seat s{};
//             s.rect.setSize(seatSize);
//             s.rect.setPosition({seatOrigin.x + c*(seatSize.x+gapX), seatOrigin.y + r*(seatSize.y+gapY)});
//             s.booked = booked(r, c);
//             s.selected = false;
//             s.rect.setFillColor(s.booked ? sf::Color(100,100,110) : sf::Color(40,160,80));
//             s.rect.setOutlineThickness(2);
//             s.rect.setOutlineColor(sf::Color(70,70,80));
//             seats[r][c] = s;
//         }
//     }

//     // Screen banner
//     sf::RectangleShape screen({seatPanel.getSize().x - 60.f, 4.f});
//     screen.setPosition(seatPanel.getPosition() + sf::Vector2f{30.f, 64.f});
//     screen.setFillColor(sf::Color(0, 170, 255));

//     sf::Text screenLbl(font, "SCREEN", 16);
//     screenLbl.setFillColor(sf::Color(180, 220, 255));
//     screenLbl.setPosition(screen.getPosition() + sf::Vector2f{screen.getSize().x/2.f - 36.f, -24.f});

//     // Legend
//     sf::Text legend(font, "Legend:  \nGreen = Available  |  Gray = Booked  |  Yellow = Selected", 16);
//     legend.setFillColor(sf::Color(200,200,210));
//     legend.setPosition(seatPanel.getPosition() + sf::Vector2f{30.f, seatPanel.getSize().y - 46.f});

//     // ----- Cart Summary -----
//     sf::Text cartLines(font, "", 18);
//     cartLines.setFillColor(sf::Color(210,210,220));
//     cartLines.setPosition(cartPanel.getPosition() + sf::Vector2f{16.f, ty + 8.f});

//     sf::RectangleShape payBtn({cartPanel.getSize().x - 32.f, 44.f});
//     payBtn.setPosition(cartPanel.getPosition() + sf::Vector2f{16.f, cartPanel.getSize().y - 60.f});
//     payBtn.setFillColor(sf::Color(0,170,255));
//     sf::Text payLbl(font, "Pay Now", 20);
//     payLbl.setFillColor(sf::Color::Black);
//     payLbl.setPosition(payBtn.getPosition() + sf::Vector2f{payBtn.getSize().x/2.f - 42.f, 8.f});

//     auto recalcSummary = [&](){
//         // Collect selected seats
//         vector<pair<int,int>> sel;
//         for (int r=0; r<ROWS; ++r) for (int c=0; c<COLS; ++c)
//             if (seats[r][c].selected) sel.push_back({r,c});
//         int pricePer = 70000; // mock
//         int total = (int)sel.size() * pricePer;
//         string m = (selectedMovie==-1? "Movie: (none)\n" : "Movie: " + movieNames[selectedMovie] + "\n");
//         m += "Time : " + (selectedTime==-1? string("(none)") : timeLabels[selectedTime].getString().toAnsiString()) + "\n";
//         m += "Seats: ";
//         if (sel.empty()) m += "(none)\n";
//         else {
//             for (size_t i=0;i<sel.size();++i){
//                 m += string(1, 'A' + sel[i].first) + to_string(sel[i].second+1);
//                 if (i+1<sel.size()) m += ", ";
//             }
//             m += "\n";
//         }
//         m += "Total: " + to_string(total) + " VND";
//         cartLines.setString(m);
//     };
//     recalcSummary();

//     // Hover feedback
//     auto setMovieHover = [&](int idx, bool hov){
//         if (idx<0) return;
//         if (movies[idx].selected) {
//             movies[idx].box.setOutlineColor(sf::Color(0,170,255));
//             movies[idx].box.setFillColor(sf::Color(40,40,60));
//         } else if (hov) {
//             movies[idx].box.setOutlineColor(sf::Color(120,120,140));
//             movies[idx].box.setFillColor(sf::Color(40,40,50));
//         } else {
//             movies[idx].box.setOutlineColor(sf::Color(70,70,80));
//             movies[idx].box.setFillColor(sf::Color(34,34,40));
//         }
//     };

//     while (window.isOpen()) {
//         while (auto event = window.pollEvent()) {
//             if (event->is<sf::Event::Closed>()) window.close();

//             if (auto *mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
//                 sf::Vector2f mp{(float)mouse->position.x, (float)mouse->position.y};

//                 // Click movie
//                 for (int i=0;i<(int)movies.size();++i) {
//                     if (pointIn(movies[i].box.getGlobalBounds(), mp)) {
//                         if (selectedMovie != -1) { movies[selectedMovie].selected = false; setMovieHover(selectedMovie, false); }
//                         selectedMovie = i;
//                         movies[i].selected = true;
//                         setMovieHover(i, true);
//                         recalcSummary();
//                     }
//                 }

//                 // Click showtime
//                 for (int i=0;i<(int)timePills.size();++i) {
//                     if (pointIn(timePills[i].getGlobalBounds(), mp)) {
//                         if (selectedTime != -1) {
//                             timePills[selectedTime].setOutlineColor(sf::Color(70,70,80));
//                             timePills[selectedTime].setFillColor(sf::Color(34,34,40));
//                         }
//                         selectedTime = i;
//                         timePills[i].setOutlineColor(sf::Color(0,170,255));
//                         timePills[i].setFillColor(sf::Color(40,40,60));
//                         recalcSummary();
//                     }
//                 }

//                 // Click seat
//                 for (int r=0;r<ROWS;++r) for (int c=0;c<COLS;++c) {
//                     if (pointIn(seats[r][c].rect.getGlobalBounds(), mp) && !seats[r][c].booked) {
//                         seats[r][c].selected = !seats[r][c].selected;
//                         if (seats[r][c].selected) seats[r][c].rect.setFillColor(sf::Color(230,200,60));
//                         else seats[r][c].rect.setFillColor(sf::Color(40,160,80));
//                         recalcSummary();
//                     }
//                 }

//                 // Click Pay
//                 if (pointIn(payBtn.getGlobalBounds(), mp)) {
//                     cout << "[PAY] Processing mock payment...\n";
//                 }
//             }

//             // Hover visuals (movies)
//             // if (event->is<sf::Event::MouseMoved>()) {
//             //     auto mv = event->is<sf::Event::MouseMoved>();
//             //     sf::Vector2f mp{(float)mv.position.x, (float)mv.position.y};
//             //     for (int i=0;i<(int)movies.size();++i) {
//             //         bool hov = pointIn(movies[i].box.getGlobalBounds(), mp);
//             //         setMovieHover(i, hov);
//             //     }
//             // }
//             if (auto* mv = event->getIf<sf::Event::MouseMoved>()) {
//                 sf::Vector2f mp{(float)mv->position.x, (float)mv->position.y};
//                 for (int i = 0; i < (int)movies.size(); ++i) {
//                 bool hov = pointIn(movies[i].box.getGlobalBounds(), mp);
//                 setMovieHover(i, hov);
//                 }
//             }           
//         }

//         window.clear(sf::Color(14,14,18));
//         // Draw
//         window.draw(topBar);
//         window.draw(title);
//         window.draw(searchBar);
//         window.draw(searchHint);

//         window.draw(moviePanel);
//         window.draw(movieHdr);
//         for (auto &m : movies) { window.draw(m.box); window.draw(m.title); }

//         window.draw(seatPanel);
//         window.draw(seatHdr);
//         window.draw(screen);
//         window.draw(screenLbl);
//         for (int r=0;r<ROWS;++r) for (int c=0;c<COLS;++c) window.draw(seats[r][c].rect);
//         window.draw(legend);

//         window.draw(cartPanel);
//         window.draw(cartHdr);
//         for (auto &pill : timePills) window.draw(pill);
//         for (auto &lab  : timeLabels) window.draw(lab);
//         window.draw(cartLines);
//         window.draw(payBtn);
//         window.draw(payLbl);

//         window.display();
//     }
//     return 0;
// }