#include "DetailScreen.h"
#include <locale>
#include <codecvt>
#include <sstream>

// Helper function to wrap text to fit within a maximum width
wstring wrapText(const wstring& text, const Font& font, unsigned int fontSize, float maxWidth) {
    if (text.empty()) return text;
    
    Text testText(font, L"", fontSize);
    wstring wrappedText = L"";
    wstring currentLine = L"";
    
    // Split by existing newlines first
    wstring remainingText = text;
    size_t pos = 0;
    
    while (pos < remainingText.length()) {
        size_t newlinePos = remainingText.find(L'\n', pos);
        if (newlinePos == wstring::npos) newlinePos = remainingText.length();
        
        wstring segment = remainingText.substr(pos, newlinePos - pos);
        
        // Process each word in the segment
        wstringstream ss(segment);
        wstring word;
        
        while (ss >> word) {
            wstring testLine = currentLine.empty() ? word : currentLine + L" " + word;
            testText.setString(testLine);
            
            if (testText.getLocalBounds().size.x <= maxWidth) {
                currentLine = testLine;
            } else {
                if (!currentLine.empty()) {
                    wrappedText += currentLine + L"\n";
                }
                currentLine = word;
            }
        }
        
        if (newlinePos < remainingText.length()) {
            // Add current line and newline
            if (!currentLine.empty()) {
                wrappedText += currentLine + L"\n";
                currentLine = L"";
            }
        }
        
        pos = newlinePos + 1;
    }
    
    // Add the last line
    if (!currentLine.empty()) {
        wrappedText += currentLine;
    }
    
    return wrappedText;
}

DetailScreen::DetailScreen(Font& font, int movieIndex, const string& username) : 
    HomeScreen(font),
    poster(posterTexture),
    titleText(font, L"", 36),
    genreText(font, L"", 22),
    durationText(font, L"", 22),
    countryText(font, L"", 22),
    castText(font, L"", 22),
    descriptionText(font, L"", 20),
    ageRatingText(font, L"", 22),
    languageText(font, L"", 22),
    directorText(font, L"", 22),
    statusText(font, L"", 22),
    releaseDateText(font, L"", 22)
{
    setLoggedUser(username);
    
    // Load movie data from CSV
    loadMovieData(movieIndex);
    
    // Set positions for all text elements with proper spacing for wrapped text
    titleText.setPosition({804, 120});
    ageRatingText.setPosition({804, 170});
    genreText.setPosition({804, 200});
    durationText.setPosition({804, 230});
    countryText.setPosition({804, 260});
    languageText.setPosition({804, 290});
    directorText.setPosition({804, 320});
    castText.setPosition({804, 350});        // Cast có thể xuống nhiều dòng
    releaseDateText.setPosition({804, 420}); // Cách xa hơn để tránh cast text
    statusText.setPosition({804, 450});
    descriptionText.setPosition({804, 480}); // Description ở cuối và có thể dài

    poster.setPosition({168, 126});
    poster.setScale({0.36f, 0.36f});
}

void DetailScreen::loadMovieData(int movieIndex) {
    // Load all movies from CSV
    allMovies = loadMoviesFromCSV("../data/movies.csv");
    
    if (allMovies.empty()) {
        cout << "❌ Không thể tải dữ liệu phim từ CSV!" << endl;
        return;
    }
    
    // Get the selected movie (validate index)
    if (movieIndex >= 0 && movieIndex < allMovies.size()) {
        currentMovie = allMovies[movieIndex];
    } else {
        cout << "⚠️ Chỉ số phim không hợp lệ: " << movieIndex << endl;
        if (!allMovies.empty()) {
            currentMovie = allMovies[0]; // Fallback to first movie
        } else {
            return;
        }
    }
    
    // Convert string to wstring for SFML Text
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    
    // Update all text elements with movie data
    titleText.setString(converter.from_bytes(currentMovie.title));
    
    wstring ageRating = L"Độ tuổi: " + converter.from_bytes(currentMovie.age_rating);
    ageRatingText.setString(ageRating);
    
    wstring genres = L"Thể loại: " + converter.from_bytes(currentMovie.genres);
    genreText.setString(genres);
    
    wstring duration = L"Thời lượng: " + converter.from_bytes(currentMovie.duration_min) + L" phút";
    durationText.setString(duration);
    
    wstring country = L"Quốc gia: " + converter.from_bytes(currentMovie.country);
    countryText.setString(country);
    
    wstring language = L"Ngôn ngữ: " + converter.from_bytes(currentMovie.language);
    languageText.setString(language);
    
    wstring director = L"Đạo diễn: " + converter.from_bytes(currentMovie.director);
    directorText.setString(director);
    
    // ✅ Wrap cast text to fit in display area (max width ~520px)
    wstring cast = L"Diễn viên: " + converter.from_bytes(currentMovie.cast);
    wstring wrappedCast = wrapText(cast, castText.getFont(), castText.getCharacterSize(), 520.0f);
    castText.setString(wrappedCast);
    
    wstring releaseDate = L"Khởi chiếu: " + converter.from_bytes(currentMovie.release_date);
    releaseDateText.setString(releaseDate);
    
    wstring status = L"Trạng thái: " + converter.from_bytes(currentMovie.status);
    statusText.setString(status);
    
    // ✅ Wrap description/synopsis text to fit in display area (max width ~520px)
    wstring synopsis = converter.from_bytes(currentMovie.synopsis);
    wstring wrappedSynopsis = wrapText(synopsis, descriptionText.getFont(), descriptionText.getCharacterSize(), 520.0f);
    descriptionText.setString(wrappedSynopsis);
    
    // Load poster image
    if (posterTexture.loadFromFile(currentMovie.poster_path)) {
        poster.setTexture(posterTexture);
    } else {
        cout << "⚠️ Không thể tải poster: " << currentMovie.poster_path << endl;
    }
}

void DetailScreen::update(Vector2f mouse, bool mousePressed, AppState& state) {
    HomeScreen::update(mouse, mousePressed, state);
} 

void DetailScreen::draw(RenderWindow& window) {
    HomeScreen::draw(window);

    // Draw all text elements
    window.draw(titleText);
    window.draw(ageRatingText);
    window.draw(genreText);
    window.draw(durationText);
    window.draw(countryText);
    window.draw(languageText);
    window.draw(directorText);
    window.draw(castText);
    window.draw(releaseDateText);
    window.draw(statusText);
    window.draw(descriptionText);
    window.draw(poster);
}