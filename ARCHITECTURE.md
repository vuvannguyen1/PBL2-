# Movie Search Feature - Architecture Diagram

## Component Hierarchy

```
┌─────────────────────────────────────────────────────────────────┐
│                          App (Main)                              │
│  • Manages application lifecycle                                 │
│  • Loads movie data from CSV                                     │
│  • Coordinates screen transitions                                │
└───────────────────────────┬─────────────────────────────────────┘
                            │
                            │ initializes
                            │
┌───────────────────────────▼─────────────────────────────────────┐
│                        HomeScreen                                │
│  • Main UI container                                             │
│  • Manages search components                                     │
│  • Handles user interactions                                     │
└────────────┬────────────────────────────────┬───────────────────┘
             │                                 │
             │ owns                            │ owns
             │                                 │
┌────────────▼─────────────┐     ┌───────────▼──────────────────┐
│      SearchBox           │     │   MovieSearchManager         │
│  • UI Component          │     │   • Business Logic           │
│  • Input field           │────▶│   • Movie indexing           │
│  • Autocomplete dropdown │uses │   • Search operations        │
│  • Event handling        │     │   • Result mapping           │
└──────────────────────────┘     └──────────┬───────────────────┘
                                             │
                                             │ uses
                                             │
                                  ┌──────────▼───────────┐
                                  │        Trie          │
                                  │  • Core algorithm    │
                                  │  • Prefix search     │
                                  │  • Autocomplete      │
                                  └──────────────────────┘
```

## Data Flow Diagram

```
┌──────────┐
│  User    │
└────┬─────┘
     │ types search query
     │
     ▼
┌────────────────┐         ┌──────────────────────┐
│   SearchBox    │───1──▶  │ handleEvent()        │
│   (UI Layer)   │         │  • Capture input     │
└────────────────┘         │  • Normalize text    │
     │                     └──────────┬───────────┘
     │                                │
     │                                │ 2. search
     │                                ▼
     │                     ┌──────────────────────┐
     │                     │ MovieSearchManager   │
     │                     │  • Normalize query   │
     │                     └──────────┬───────────┘
     │                                │
     │                                │ 3. getSuggestions
     │                                ▼
     │                     ┌──────────────────────┐
     │                     │       Trie           │
     │                     │  • Prefix search     │
     │                     │  • DFS traversal     │
     │                     └──────────┬───────────┘
     │                                │
     │                                │ 4. return matches
     │                                ▼
     │                     ┌──────────────────────┐
     │                     │ MovieSearchManager   │
     │                     │  • Map to indices    │
     │                     │  • Fallback search   │
     │                     └──────────┬───────────┘
     │                                │
     │                                │ 5. return results
     │                                ▼
     │                     ┌──────────────────────┐
     │◀────────────6───────│   SearchBox          │
     │  display             │  • Format results    │
     │  suggestions         │  • Render dropdown   │
     │                     └──────────────────────┘
     │
     │ 7. user selects
     │
     ▼
┌────────────────┐         ┌──────────────────────┐
│  HomeScreen    │───8──▶  │   DetailScreen       │
│                │ navigate│  • Show movie info   │
└────────────────┘         └──────────────────────┘
```

## State Diagram

```
                    ┌─────────────┐
                    │   Initial   │
                    │   (Idle)    │
                    └──────┬──────┘
                           │
                  user clicks search box
                           │
                    ┌──────▼──────┐
              ┌────▶│   Active    │◀────┐
              │     │ (Accepting  │     │
              │     │   Input)    │     │
              │     └──────┬──────┘     │
              │            │            │
              │   user types character  │
              │            │            │
              │     ┌──────▼──────┐    │
              │     │  Searching  │    │
              │     │ (Query Trie)│    │
              │     └──────┬──────┘    │
              │            │            │
              │   suggestions found     │
              │            │            │
              │     ┌──────▼──────┐    │
        no    │     │  Dropdown   │    │ continues
    matches   │     │  Visible    │    │ typing
              │     └──────┬──────┘    │
              │            │            │
              │   user navigates with   │
              │   arrows / hovers       │
              │            │            │
              └────────────┼────────────┘
                           │
                  user selects (Enter/Click)
                           │
                    ┌──────▼──────┐
                    │  Selected   │
                    │  (Navigate) │
                    └──────┬──────┘
                           │
                    ┌──────▼──────┐
                    │ DetailScreen│
                    │   (Movie)   │
                    └─────────────┘
                           │
                   back to home (Escape)
                           │
                    ┌──────▼──────┐
                    │   Initial   │
                    │   (Idle)    │
                    └─────────────┘
```

## Class Diagram

```
┌──────────────────────────────────┐
│          TrieNode                │
├──────────────────────────────────┤
│ + isEnd: bool                    │
│ + children: TrieNode*[26]        │
├──────────────────────────────────┤
│ + TrieNode()                     │
└──────────────────────────────────┘
                ▲
                │
                │ uses
                │
┌───────────────┴──────────────────┐
│            Trie                  │
├──────────────────────────────────┤
│ - root: TrieNode*                │
├──────────────────────────────────┤
│ + Trie()                         │
│ + insert(string): void           │
│ + search(string): bool           │
│ + startsWith(string): bool       │
│ + getSuggestions(string, int):  │
│   vector<string>                 │
│ - dfs(TrieNode*, string,        │
│   vector<string>&, int): void    │
└──────────────────────────────────┘
                ▲
                │
                │ uses
                │
┌───────────────┴──────────────────┐
│     MovieSearchManager           │
├──────────────────────────────────┤
│ - trie: Trie                     │
│ - movies: vector<Movie>          │
│ - titleToIndexMap:               │
│   map<string, vector<int>>       │
├──────────────────────────────────┤
│ + MovieSearchManager()           │
│ + loadMovies(vector<Movie>):    │
│   void                           │
│ + searchMovies(string, int):    │
│   vector<SearchResult>           │
│ - normalizeString(string):       │
│   string                         │
└──────────────────────────────────┘
                ▲
                │
                │ uses
                │
┌───────────────┴──────────────────┐
│          SearchBox               │
├──────────────────────────────────┤
│ - inputBox: RectangleShape       │
│ - suggestionBox: RectangleShape  │
│ - inputText: Text                │
│ - suggestions:                   │
│   vector<SearchResult>           │
│ - searchManager:                 │
│   MovieSearchManager*            │
│ - isActive: bool                 │
│ - showSuggestions: bool          │
├──────────────────────────────────┤
│ + SearchBox(Font&, Vector2f,    │
│   Vector2f)                      │
│ + setSearchManager(              │
│   MovieSearchManager*): void     │
│ + handleEvent(Event&): void      │
│ + update(Vector2f, bool): void   │
│ + draw(RenderWindow&): void      │
│ + hasSelectedMovie(int&): bool   │
│ + clear(): void                  │
└──────────────────────────────────┘
                ▲
                │
                │ owns
                │
┌───────────────┴──────────────────┐
│         HomeScreen               │
├──────────────────────────────────┤
│ - searchBox: SearchBox*          │
│ - searchManager:                 │
│   MovieSearchManager*            │
│ - selectedMovieIndex: int        │
├──────────────────────────────────┤
│ + HomeScreen(Font&)              │
│ + ~HomeScreen()                  │
│ + initializeSearch(              │
│   vector<Movie>&): void          │
│ + update(Vector2f, bool,         │
│   AppState&, Event*): void       │
│ + draw(RenderWindow&): void      │
│ + getSelectedMovieIndex(): int   │
│ + clearSelectedMovieIndex():     │
│   void                           │
└──────────────────────────────────┘
```

## Memory Layout

```
App
 └─> HomeScreen
      ├─> SearchBox (heap allocated)
      │    ├─> RectangleShape (input box)
      │    ├─> RectangleShape (suggestion box)
      │    ├─> Text (input, placeholder, suggestions)
      │    └─> vector<SearchResult> (suggestions)
      │
      └─> MovieSearchManager (heap allocated)
           ├─> Trie
           │    └─> TrieNode* (root)
           │         └─> TrieNode*[26] (children) [recursive]
           │
           ├─> vector<Movie> (copy of movies)
           └─> map<string, vector<int>> (title to index)
```

## Execution Flow Timeline

```
Time  │ Action                              │ Component
──────┼─────────────────────────────────────┼────────────────────
T0    │ App starts                          │ App
T1    │ Load movies from CSV                │ App
T2    │ Create HomeScreen                   │ App
T3    │ Initialize SearchBox                │ HomeScreen
T4    │ Create MovieSearchManager           │ HomeScreen
T5    │ Load movies into Trie               │ MovieSearchManager
T6    │ Render home screen                  │ HomeScreen
...   │ ...                                 │ ...
Tn    │ User clicks search box              │ SearchBox
Tn+1  │ SearchBox becomes active            │ SearchBox
Tn+2  │ User types 'D'                      │ SearchBox
Tn+3  │ Query MovieSearchManager            │ SearchBox
Tn+4  │ Trie.getSuggestions('d')           │ Trie
Tn+5  │ Return ["dune", "dao"]             │ Trie
Tn+6  │ Map to movie indices                │ MovieSearchManager
Tn+7  │ Display suggestions                 │ SearchBox
Tn+8  │ User types 'U' → 'DU'              │ SearchBox
Tn+9  │ Update suggestions → ["dune"]      │ SearchBox
Tn+10 │ User presses Enter                  │ SearchBox
Tn+11 │ hasSelectedMovie() returns true     │ SearchBox
Tn+12 │ Set selectedMovieIndex              │ HomeScreen
Tn+13 │ State → MOVIE_DETAILS              │ App
Tn+14 │ Render DetailScreen                 │ DetailScreen
```

## Key Design Decisions

1. **Trie for Efficiency**: O(k) search time where k is query length
2. **Fallback Search**: Substring matching when Trie has no results
3. **Pointer Ownership**: HomeScreen owns SearchBox and MovieSearchManager
4. **Event-Driven**: SearchBox processes SFML events for text input
5. **Lazy Initialization**: Search components created but movies loaded on demand
6. **Index-Based Navigation**: Store movie index for efficient DetailScreen lookup
7. **Dark Theme**: Colors match existing UI (RGB(40,40,40) backgrounds)
8. **Keyboard Support**: Arrow keys, Enter, Escape for accessibility
9. **Mouse Support**: Click to focus, click suggestions to select
10. **Real-Time Updates**: Suggestions update as user types
