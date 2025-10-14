#include "DetailScreen.h"

DetailScreen::DetailScreen(Font& font, const Slide& slide, const string& username) : 
    HomeScreen(font),
    titleText(font, L"BLUE BEETLE", 36),
    genreText(font, L"Thể loại: Action; Superhero; Sci-Fi", 22),
    durationText(font, L"Thời lượng: 128 phút", 22),
    countryText(font, L"Quốc gia: USA", 22),
    castText(font, L"Diễn viên: Xolo Maridueña; Bruna Marquezine; Susan Sarandon", 22),
    descriptionText(font, L"Chàng trai trẻ Jaime Reyes trở thành siêu anh hùng Blue Beetle.", 22),
    poster(slide.getPosterTexture())
{
    setLoggedUser(username);
    
    titleText.setPosition({904, 150});
    genreText.setPosition({904, 200});
    durationText.setPosition({904, 250});
    countryText.setPosition({904, 300});
    castText.setPosition({904, 350});
    descriptionText.setPosition({904, 400});

    poster.setPosition({268, 126});
    poster.setScale({0.36f, 0.36f});
}

void DetailScreen::update(Vector2f mouse, bool mousePressed, AppState& state) {
    HomeScreen::update(mouse, mousePressed, state);
} 

void DetailScreen::draw(RenderWindow& window) {
    HomeScreen::draw(window);

    window.draw(titleText);
    window.draw(genreText);
    window.draw(durationText);
    window.draw(countryText);
    window.draw(castText);
    window.draw(descriptionText);
    window.draw(poster);
}