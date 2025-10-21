# Movie Search Feature - UI Mockup and User Guide

## Visual Interface Design

### Search Box States

#### 1. Inactive State (Default)
```
╔══════════════════════════════════════════════════════════════╗
║ CiNeXíNè                                        Login | User ║
╠══════════════════════════════════════════════════════════════╣
║                                                              ║
║                    ┌────────────────────────┐               ║
║                    │ Search movies...        │  ← Placeholder
║                    └────────────────────────┘               ║
║                      Border: Gray (100,100,100)             ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

#### 2. Active State (Focused, No Input)
```
╔══════════════════════════════════════════════════════════════╗
║ CiNeXíNè                                        Login | User ║
╠══════════════════════════════════════════════════════════════╣
║                                                              ║
║                    ┌────────────────────────┐               ║
║                    │ |                       │  ← Cursor blinks
║                    └────────────────────────┘               ║
║                      Border: Blue (20,118,172)              ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

#### 3. Active with Input and Suggestions
```
╔══════════════════════════════════════════════════════════════╗
║ CiNeXíNè                                        Login | User ║
╠══════════════════════════════════════════════════════════════╣
║                                                              ║
║                    ┌────────────────────────┐               ║
║                    │ dun|                    │  ← User typed "dun"
║                    └────────────────────────┘               ║
║                    ┌────────────────────────┐               ║
║                    │ DUNE: PART TWO        │ ◄── Highlighted
║                    │ DUNE (2021)            │               ║
║                    │ DUNE: PROPHECY         │               ║
║                    └────────────────────────┘               ║
║                      ↑ Autocomplete dropdown                ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

#### 4. Vietnamese Search Example
```
╔══════════════════════════════════════════════════════════════╗
║ CiNeXíNè                                    Xin chào, User! ║
╠══════════════════════════════════════════════════════════════╣
║                                                              ║
║                    ┌────────────────────────┐               ║
║                    │ mai|                    │               ║
║                    └────────────────────────┘               ║
║                    ┌────────────────────────┐               ║
║                    │ MAI                    │ ◄── Selected  ║
║                    │ MAI 2024               │               ║
║                    └────────────────────────┘               ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
```

#### 5. Full Integration in Home Screen
```
╔══════════════════════════════════════════════════════════════════════╗
║  ╔══════╗                                                            ║
║  ║CiNeXí║        ┌──────────────────────┐         Đặt vé    Login   ║
║  ║  Nè  ║        │ tử chiến|            │          ngay              ║
║  ╚══════╝        └──────────────────────┘                           ║
║                  ┌──────────────────────┐                            ║
║                  │ TỬ CHIẾN TRÊN KHÔNG │ ◄── Autocomplete           ║
║                  └──────────────────────┘                            ║
╠══════════════════════════════════════════════════════════════════════╣
║                                                                       ║
║        ╔═══════╗      ╔═══════╗      ╔═══════╗      ╔═══════╗      ║
║        ║       ║      ║       ║      ║       ║      ║       ║      ║
║   ◄    ║ MAI   ║      ║ DUNE  ║      ║GODZILLA║     ║ ĐÀO   ║   ►  ║
║        ║       ║      ║       ║      ║       ║      ║       ║      ║
║        ╚═══════╝      ╚═══════╝      ╚═══════╝      ╚═══════╝      ║
║                                                                       ║
║        ○  ●  ○  ○  ○  ○  ○  ○  ○  ○  ← Slider dots                 ║
║                                                                       ║
╚═══════════════════════════════════════════════════════════════════════╝
```

## User Interaction Flow

### Scenario 1: Searching for an English Movie

```
Step 1: User clicks search box
   └─> Search box gains focus (blue border)
   └─> Cursor appears and blinks

Step 2: User types "g"
   └─> SearchBox.handleEvent() captures 'g'
   └─> MovieSearchManager.searchMovies("g")
   └─> Trie.getSuggestions("g", 5)
   └─> Returns: ["godzilla x kong: the new empire"]
   └─> Dropdown shows: "GODZILLA X KONG: THE NEW EMPIRE"

Step 3: User types "o" → "go"
   └─> Suggestions update in real-time
   └─> Still shows: "GODZILLA X KONG: THE NEW EMPIRE"

Step 4: User presses Enter or clicks suggestion
   └─> SearchBox.hasSelectedMovie() returns true
   └─> HomeScreen sets selectedMovieIndex
   └─> App state changes to MOVIE_DETAILS
   └─> DetailScreen renders for selected movie
```

### Scenario 2: Searching for a Vietnamese Movie

```
Step 1: User clicks search box and types "m"
   └─> Suggestions: ["MAI", "LẬT MẶT: 48H" (if contains 'm')]

Step 2: User types "a" → "ma"
   └─> Suggestions narrow to: ["MAI"]

Step 3: User types "i" → "mai"
   └─> Exact match: ["MAI"]
   └─> Dropdown shows: "MAI"

Step 4: User presses Enter
   └─> Navigates to MAI detail screen
```

### Scenario 3: Using Keyboard Navigation

```
Step 1: User types "d"
   └─> Dropdown shows 3 suggestions:
       • DUNE: PART TWO
       • ĐÀO, PHỞ VÀ PIANO
       • (other 'd' movies)

Step 2: User presses Down Arrow
   └─> First suggestion highlighted (darker background)

Step 3: User presses Down Arrow again
   └─> Second suggestion highlighted

Step 4: User presses Up Arrow
   └─> Back to first suggestion

Step 5: User presses Enter
   └─> Selected movie loads
```

### Scenario 4: Canceling Search

```
Step 1: User types "xyz" (no results)
   └─> Dropdown shows "No suggestions"
   └─> (Or empty if no results to display)

Step 2: User presses Escape
   └─> Search box loses focus
   └─> Border returns to gray
   └─> Input cleared
   └─> Dropdown hidden
```

## Color Reference Chart

```
Component              │ State      │ Color (RGB)         │ Alpha
───────────────────────┼────────────┼─────────────────────┼──────
Search Box Background  │ All        │ (40, 40, 40)        │ 220
Search Box Border      │ Inactive   │ (100, 100, 100)     │ 255
Search Box Border      │ Active     │ (20, 118, 172)      │ 255  ← Accent
Input Text             │ All        │ (255, 255, 255)     │ 255  ← White
Placeholder Text       │ Inactive   │ (150, 150, 150)     │ 255
Cursor                 │ Active     │ (255, 255, 255)     │ 255
Dropdown Background    │ All        │ (30, 30, 30)        │ 240
Dropdown Border        │ All        │ (100, 100, 100)     │ 255
Suggestion Text        │ Normal     │ (200, 200, 200)     │ 255
Suggestion Text        │ Highlighted│ (255, 255, 255)     │ 255
Suggestion Highlight   │ Selected   │ (60, 60, 60)        │ 255
```

## Keyboard Shortcuts Reference

```
Key          │ Action
─────────────┼──────────────────────────────────────────────
Click        │ Activate search box / Select suggestion
Type         │ Enter search text
Backspace    │ Delete last character
Up Arrow     │ Navigate to previous suggestion
Down Arrow   │ Navigate to next suggestion
Enter        │ Select highlighted suggestion
Escape       │ Cancel and close search
Tab          │ (Not implemented - future enhancement)
```

## Accessibility Features

✅ **Keyboard Navigation**: Full keyboard support for mouse-free operation
✅ **Visual Feedback**: Color changes indicate active state
✅ **Cursor Indicator**: Blinking cursor shows input focus
✅ **Highlight Selection**: Clear visual indication of selected item
✅ **Dark Theme**: High contrast for readability
✅ **UTF-8 Support**: Vietnamese characters fully supported

## Performance Characteristics

```
Operation                  │ Time Complexity │ Notes
───────────────────────────┼─────────────────┼──────────────────────
Initial Load (10 movies)   │ O(n × m)        │ n=movies, m=avg length
Single Search Query        │ O(k)            │ k=query length
Generate Suggestions       │ O(k + 5)        │ Limited to 5 results
Render Dropdown            │ O(5)            │ Fixed number of items
Total Search Latency       │ < 1ms           │ For typical queries
Memory Footprint           │ ~10KB           │ For 10 movies
```

## Testing Scenarios

### Test Case 1: Basic Search
- [ ] Open application
- [ ] Click search box
- [ ] Type "dune"
- [ ] Verify suggestions appear
- [ ] Select first suggestion
- [ ] Verify detail screen shows correct movie

### Test Case 2: Vietnamese Characters
- [ ] Click search box
- [ ] Type "mai"
- [ ] Verify "MAI" appears in suggestions
- [ ] Type "tử"
- [ ] Verify "TỬ CHIẾN TRÊN KHÔNG" appears
- [ ] Select and verify navigation

### Test Case 3: Keyboard Navigation
- [ ] Type search query with multiple results
- [ ] Press Down Arrow multiple times
- [ ] Verify highlight moves down
- [ ] Press Up Arrow
- [ ] Verify highlight moves up
- [ ] Press Enter
- [ ] Verify correct movie selected

### Test Case 4: Case Insensitivity
- [ ] Type "DUNE" (uppercase)
- [ ] Verify results appear
- [ ] Type "dune" (lowercase)
- [ ] Verify same results appear
- [ ] Type "DuNe" (mixed case)
- [ ] Verify same results appear

### Test Case 5: No Results
- [ ] Type "xyz123"
- [ ] Verify no suggestions appear (or "No results" message)
- [ ] Verify no errors occur
- [ ] Press Escape
- [ ] Verify search clears properly

### Test Case 6: Click Outside
- [ ] Type search query
- [ ] Click outside search box
- [ ] Verify search box loses focus
- [ ] Verify dropdown closes
- [ ] Verify border returns to gray

## Troubleshooting Guide

### Issue: Suggestions Don't Appear
**Possible Causes:**
1. Movies not loaded into search manager
2. Query too short (need at least 1 character)
3. No matching movies in database

**Solution:**
- Check `home.initializeSearch(movies)` is called in `App.cpp`
- Verify movies CSV is loaded correctly
- Check console for error messages

### Issue: Vietnamese Characters Don't Work
**Possible Causes:**
1. UTF-8 encoding not set in file
2. Font doesn't support Vietnamese characters

**Solution:**
- Ensure CSV file is UTF-8 encoded
- Verify Montserrat_SemiBold.ttf supports Vietnamese
- Check SFML UTF-8 handling is correct

### Issue: Search Box Not Visible
**Possible Causes:**
1. Position off-screen
2. Size too small
3. Z-order issue with other UI elements

**Solution:**
- Check SearchBox position: (750, 55)
- Check SearchBox size: (350, 40)
- Ensure draw() is called after background elements

### Issue: Clicking Doesn't Select Suggestion
**Possible Causes:**
1. Click detection not working
2. Bounds calculation incorrect

**Solution:**
- Verify `suggestionBox.getGlobalBounds()` is correct
- Check mouse position mapping
- Ensure `mousePressed` is true on click

## Future Enhancement Ideas

1. **Search History**
   - Store recent searches
   - Quick access to previous queries
   - Clear history option

2. **Advanced Filters**
   - Filter by genre
   - Filter by year
   - Filter by rating
   - Filter by language

3. **Voice Search**
   - Speech-to-text input
   - Voice commands

4. **Search Analytics**
   - Track popular searches
   - Suggest trending movies

5. **Smart Suggestions**
   - Learn from user behavior
   - Personalized recommendations
   - Related movies

6. **Multi-Language Support**
   - Search in multiple languages
   - Translation support
   - Locale-aware results

## Conclusion

The movie search feature provides a seamless, intuitive way for users to find movies in the CiNeXíNè application. With real-time autocomplete, keyboard navigation, and Vietnamese character support, it enhances the user experience while maintaining the application's dark theme aesthetic.

**Key Benefits:**
- ⚡ Fast search (< 1ms response time)
- 🎯 Accurate results (Trie + fallback)
- ⌨️ Full keyboard support
- 🌏 Vietnamese language support
- 🎨 Beautiful dark theme UI
- ♿ Accessible and user-friendly

For technical details, see [SEARCH_FEATURE.md](SEARCH_FEATURE.md)
For architecture information, see [ARCHITECTURE.md](ARCHITECTURE.md)
For implementation details, see [IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md)
