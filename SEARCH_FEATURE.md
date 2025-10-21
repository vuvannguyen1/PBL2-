# Movie Search Feature

## Overview
The movie search feature provides real-time search and autocomplete functionality for finding movies in the CiNeXíNè application. It uses a Trie data structure for efficient prefix-based search and supports Vietnamese characters with case-insensitive matching.

## Components

### 1. Trie Algorithm (`Trie.h`, `Trie.cpp`)
- **Purpose**: Efficient prefix-based string search data structure
- **Features**:
  - Case-insensitive search
  - Vietnamese character support (UTF-8)
  - Prefix matching with `startsWith()`
  - Full word search with `search()`
  - Autocomplete suggestions with `getSuggestions()`
  
### 2. MovieSearchManager (`MovieSearchManager.h`, `MovieSearchManager.cpp`)
- **Purpose**: Manages movie indexing and search operations
- **Features**:
  - Loads movie data into the Trie
  - Maps normalized titles to movie indices
  - Provides fallback substring matching if Trie search yields no results
  - Returns search results with movie titles and indices

### 3. SearchBox (`SearchBox.h`, `SearchBox.cpp`)
- **Purpose**: UI component for search input and autocomplete dropdown
- **Features**:
  - Text input with cursor and placeholder
  - Real-time search as user types
  - Autocomplete dropdown showing up to 5 suggestions
  - Keyboard navigation (Up/Down arrows, Enter to select, Escape to close)
  - Mouse click selection
  - Dark theme styling matching the application
  
## User Interface

### Search Box
- **Location**: Top center of the home screen, overlaying the search bar graphic
- **Size**: 350x40 pixels
- **Position**: (750, 55)
- **Colors**:
  - Background: Dark gray (40, 40, 40, 220 alpha)
  - Border: Light gray (100, 100, 100)
  - Active border: Accent blue (20, 118, 172)
  - Text: White
  - Placeholder: Medium gray (150, 150, 150)

### Autocomplete Dropdown
- **Position**: Directly below the search box
- **Size**: Dynamic based on number of suggestions (40px per suggestion)
- **Features**:
  - Up to 5 suggestions shown
  - Highlighted selection (darker gray background)
  - Hover and keyboard navigation support

## Usage

### For Users
1. Click on the search box at the top of the home screen
2. Start typing a movie title
3. Autocomplete suggestions appear in real-time
4. Use arrow keys (Up/Down) or mouse to select a suggestion
5. Press Enter or click to view the movie details
6. Press Escape to cancel and close the search

### For Developers

#### Initialization
```cpp
// In App.cpp constructor
vector<Movie> movies = loadMoviesFromCSV("../data/movies.csv");
home.initializeSearch(movies);
```

#### Event Handling
```cpp
// In HomeScreen::update()
if (searchBox) {
    if (event) {
        searchBox->handleEvent(*event);
    }
    searchBox->update(mouse, mousePressed);
    
    int movieIdx;
    if (searchBox->hasSelectedMovie(movieIdx)) {
        selectedMovieIndex = movieIdx;
        state = AppState::MOVIE_DETAILS;
    }
}
```

## Technical Details

### String Normalization
- All strings are normalized to lowercase for case-insensitive search
- UTF-8 Vietnamese characters are preserved during normalization
- Non-alphabetic characters are handled gracefully

### Search Algorithm
1. User input is normalized (lowercase)
2. Trie searches for words starting with the input prefix
3. If Trie returns results, they are displayed
4. If no results from Trie, substring matching is used as fallback
5. Results include both movie title and index for navigation

### Performance
- Trie insertion: O(m) where m is the length of the movie title
- Trie search: O(k) where k is the length of the search query
- Autocomplete: O(k + n) where n is the number of suggestions (limited to 5)

## Integration with Existing Features
- Seamlessly integrates with HomeScreen
- Uses existing Movie data structure
- Navigates to DetailScreen on selection
- Maintains dark theme consistency
- Does not interfere with other UI elements (dropdown, buttons)

## Future Enhancements
- Advanced Vietnamese diacritic normalization (á → a, ă → a, etc.)
- Search by genre, director, or actor
- Search history
- Fuzzy matching for typo tolerance
- Extended character set support beyond a-z

## Testing
To test the search feature:
1. Build and run the application
2. Navigate to the home screen
3. Click on the search box
4. Test various search queries:
   - Vietnamese titles: "TỬ CHIẾN", "MAI", "ĐÀO"
   - English titles: "DUNE", "GODZILLA"
   - Partial matches: "LẬT", "BỐ"
5. Verify autocomplete suggestions appear
6. Verify keyboard navigation works (Up/Down/Enter/Escape)
7. Verify clicking a suggestion navigates to detail screen
8. Verify the UI matches the dark theme

## Known Limitations
- Trie currently uses a 26-character array (a-z) for English alphabet
- Vietnamese characters are handled in UTF-8 but not individually indexed
- Search is primarily effective for ASCII/English characters and whole Vietnamese words
- For pure Vietnamese character-by-character prefix matching, the Trie would need to be extended to support the full Unicode character set
