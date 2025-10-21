#include "SearchBox.h"
#include <iostream>

SearchBox::SearchBox(Font& f, Vector2f position, Vector2f size) 
    : font(f), isActive(false), showSuggestions(false), 
      selectedSuggestion(-1), searchManager(nullptr), showCursor(false) {
    
    // Input box styling (matching dark theme)
    inputBox.setSize(size);
    inputBox.setPosition(position);
    inputBox.setFillColor(Color(40, 40, 40, 220));
    inputBox.setOutlineColor(Color(100, 100, 100));
    inputBox.setOutlineThickness(2.f);
    
    // Input text
    inputText.setFont(font);
    inputText.setCharacterSize(18);
    inputText.setFillColor(Color::White);
    inputText.setPosition(position.x + 15.f, position.y + 10.f);
    
    // Placeholder text
    placeholderText.setFont(font);
    placeholderText.setCharacterSize(18);
    placeholderText.setFillColor(Color(150, 150, 150));
    placeholderText.setString("Search movies...");
    placeholderText.setPosition(position.x + 15.f, position.y + 10.f);
    
    // Suggestion box
    suggestionBox.setFillColor(Color(30, 30, 30, 240));
    suggestionBox.setOutlineColor(Color(100, 100, 100));
    suggestionBox.setOutlineThickness(1.f);
    suggestionBox.setPosition(position.x, position.y + size.y + 2.f);
}

void SearchBox::setSearchManager(MovieSearchManager* manager) {
    searchManager = manager;
}

void SearchBox::handleEvent(const Event& event) {
    if (!isActive) return;
    
    if (event.is<Event::TextEntered>()) {
        const auto& textEvent = *event.getIf<Event::TextEntered>();
        Uint32 unicode = textEvent.unicode;
        
        // Handle backspace
        if (unicode == 8) {
            if (!inputString.empty()) {
                // Handle UTF-8 backspace properly
                size_t len = inputString.length();
                if (len > 0) {
                    // Find the start of the last character
                    size_t pos = len - 1;
                    while (pos > 0 && (inputString[pos] & 0xC0) == 0x80) {
                        pos--;
                    }
                    inputString.erase(pos);
                }
            }
        }
        // Handle printable characters
        else if (unicode >= 32 && unicode < 127) {
            inputString += static_cast<char>(unicode);
        }
        // Handle UTF-8 characters (Vietnamese, etc.)
        else if (unicode >= 128) {
            // Convert unicode to UTF-8
            if (unicode < 0x80) {
                inputString += static_cast<char>(unicode);
            } else if (unicode < 0x800) {
                inputString += static_cast<char>((unicode >> 6) | 0xC0);
                inputString += static_cast<char>((unicode & 0x3F) | 0x80);
            } else if (unicode < 0x10000) {
                inputString += static_cast<char>((unicode >> 12) | 0xE0);
                inputString += static_cast<char>(((unicode >> 6) & 0x3F) | 0x80);
                inputString += static_cast<char>((unicode & 0x3F) | 0x80);
            } else {
                inputString += static_cast<char>((unicode >> 18) | 0xF0);
                inputString += static_cast<char>(((unicode >> 12) & 0x3F) | 0x80);
                inputString += static_cast<char>(((unicode >> 6) & 0x3F) | 0x80);
                inputString += static_cast<char>((unicode & 0x3F) | 0x80);
            }
        }
        
        // Update text display
        inputText.setString(inputString);
        
        // Update suggestions
        if (searchManager && !inputString.empty()) {
            suggestions = searchManager->searchMovies(inputString, 5);
            showSuggestions = !suggestions.empty();
            selectedSuggestion = -1;
        } else {
            showSuggestions = false;
            suggestions.clear();
        }
    }
    
    if (event.is<Event::KeyPressed>()) {
        const auto& keyEvent = *event.getIf<Event::KeyPressed>();
        
        // Handle arrow keys for suggestion navigation
        if (keyEvent.code == Keyboard::Key::Down && showSuggestions) {
            selectedSuggestion = (selectedSuggestion + 1) % suggestions.size();
        } else if (keyEvent.code == Keyboard::Key::Up && showSuggestions) {
            selectedSuggestion--;
            if (selectedSuggestion < 0) selectedSuggestion = suggestions.size() - 1;
        } else if (keyEvent.code == Keyboard::Key::Enter && selectedSuggestion >= 0) {
            // Selection made via Enter key (handled in hasSelectedMovie)
        } else if (keyEvent.code == Keyboard::Key::Escape) {
            isActive = false;
            showSuggestions = false;
        }
    }
}

void SearchBox::update(Vector2f mousePos, bool mousePressed) {
    // Update cursor blink
    if (blinkClock.getElapsedTime().asSeconds() > 0.5f) {
        showCursor = !showCursor;
        blinkClock.restart();
    }
    
    // Check if input box is clicked
    if (mousePressed) {
        if (inputBox.getGlobalBounds().contains(mousePos)) {
            isActive = true;
            inputBox.setOutlineColor(Color(20, 118, 172)); // Accent color when active
        } else if (showSuggestions) {
            // Check if a suggestion was clicked
            FloatRect suggestionBounds = suggestionBox.getGlobalBounds();
            if (suggestionBounds.contains(mousePos)) {
                float relativeY = mousePos.y - suggestionBounds.position.y;
                int clickedIndex = static_cast<int>(relativeY / 40.f);
                if (clickedIndex >= 0 && clickedIndex < (int)suggestions.size()) {
                    selectedSuggestion = clickedIndex;
                }
            } else {
                isActive = false;
                showSuggestions = false;
                inputBox.setOutlineColor(Color(100, 100, 100));
            }
        } else {
            isActive = false;
            inputBox.setOutlineColor(Color(100, 100, 100));
        }
    }
    
    // Update suggestion box size based on number of suggestions
    if (showSuggestions && !suggestions.empty()) {
        float boxHeight = suggestions.size() * 40.f;
        suggestionBox.setSize(Vector2f(inputBox.getSize().x, boxHeight));
    }
}

void SearchBox::draw(RenderWindow& window) {
    // Draw input box
    window.draw(inputBox);
    
    // Draw input text or placeholder
    if (inputString.empty() && !isActive) {
        window.draw(placeholderText);
    } else {
        window.draw(inputText);
        
        // Draw cursor if active
        if (isActive && showCursor) {
            FloatRect textBounds = inputText.getGlobalBounds();
            RectangleShape cursor(Vector2f(2.f, 20.f));
            cursor.setPosition(textBounds.position.x + textBounds.size.x + 2.f, inputText.getPosition().y + 5.f);
            cursor.setFillColor(Color::White);
            window.draw(cursor);
        }
    }
    
    // Draw suggestions
    if (showSuggestions && !suggestions.empty()) {
        window.draw(suggestionBox);
        
        suggestionTexts.clear();
        for (size_t i = 0; i < suggestions.size(); i++) {
            Text suggestionText;
            suggestionText.setFont(font);
            suggestionText.setCharacterSize(16);
            suggestionText.setString(suggestions[i].title);
            
            Vector2f pos = suggestionBox.getPosition();
            suggestionText.setPosition(pos.x + 15.f, pos.y + 10.f + i * 40.f);
            
            // Highlight selected suggestion
            if ((int)i == selectedSuggestion) {
                RectangleShape highlight(Vector2f(suggestionBox.getSize().x, 40.f));
                highlight.setPosition(pos.x, pos.y + i * 40.f);
                highlight.setFillColor(Color(60, 60, 60));
                window.draw(highlight);
                suggestionText.setFillColor(Color::White);
            } else {
                suggestionText.setFillColor(Color(200, 200, 200));
            }
            
            window.draw(suggestionText);
        }
    }
}

bool SearchBox::hasSelectedMovie(int& movieIndex) {
    if (selectedSuggestion >= 0 && selectedSuggestion < (int)suggestions.size()) {
        movieIndex = suggestions[selectedSuggestion].movieIndex;
        // Clear after selection
        inputString.clear();
        inputText.setString("");
        showSuggestions = false;
        selectedSuggestion = -1;
        isActive = false;
        return true;
    }
    return false;
}

void SearchBox::clear() {
    inputString.clear();
    inputText.setString("");
    showSuggestions = false;
    selectedSuggestion = -1;
    isActive = false;
    suggestions.clear();
}
