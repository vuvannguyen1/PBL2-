#pragma once
#include <SFML/Graphics.hpp>
#include "Slide.h"
#include "HomeScreen.h"
#include "Movie.h"

using namespace sf;
using namespace std;

class DetailScreen : public HomeScreen {
private:
    Font titleFont, detailFont;
    Sprite poster;
    Texture posterTexture;
    
    Text titleText, genreText, durationText, countryText, castText, descriptionText;
    Text ageRatingText, languageText, directorText, statusText, releaseDateText;
    Movie currentMovie;
    vector<Movie> allMovies;

    CircleShape genreIcon;
    CircleShape durationIcon;
    CircleShape countryIcon;
    CircleShape languageIcon;
    CircleShape ageRatingIcon;

    Text detailHeader, synopsisHeader;
public:
    DetailScreen(Font&, int movieIndex, const string& username);

    void update(Vector2f, bool, AppState&);
    void draw(RenderWindow&);
    void loadMovieData(int movieIndex);
};
