#include "MovieSearchManager.h"
#include <algorithm>
#include <cctype>
#include <locale>
#include <codecvt>

// Helper function to normalize Vietnamese characters and convert to lowercase
string MovieSearchManager::normalizeString(const string& str) {
    string result;
    
    // Process UTF-8 string and convert to lowercase
    for (size_t i = 0; i < str.length(); i++) {
        unsigned char c = str[i];
        
        // Handle ASCII characters
        if (c < 128) {
            result += tolower(c);
        } else {
            // For Vietnamese UTF-8 characters, keep them as-is for now
            // A more sophisticated approach would map Vietnamese chars to their base forms
            result += c;
            // Handle multi-byte UTF-8 characters
            if ((c & 0xE0) == 0xC0) {  // 2-byte character
                if (i + 1 < str.length()) {
                    result += str[++i];
                }
            } else if ((c & 0xF0) == 0xE0) {  // 3-byte character
                if (i + 2 < str.length()) {
                    result += str[++i];
                    result += str[++i];
                }
            } else if ((c & 0xF8) == 0xF0) {  // 4-byte character
                if (i + 3 < str.length()) {
                    result += str[++i];
                    result += str[++i];
                    result += str[++i];
                }
            }
        }
    }
    
    return result;
}

MovieSearchManager::MovieSearchManager() {}

void MovieSearchManager::loadMovies(const vector<Movie>& movieList) {
    movies = movieList;
    titleToIndexMap.clear();
    
    // Build the Trie and index map
    for (size_t i = 0; i < movies.size(); i++) {
        string title = movies[i].title;
        string normalized = normalizeString(title);
        
        // Insert into Trie
        trie.insert(normalized);
        
        // Map normalized title to movie index
        titleToIndexMap[normalized].push_back(i);
    }
}

vector<SearchResult> MovieSearchManager::searchMovies(const string& query, int limit) {
    vector<SearchResult> results;
    
    if (query.empty()) {
        return results;
    }
    
    string normalizedQuery = normalizeString(query);
    
    // Get suggestions from Trie
    vector<string> suggestions = trie.getSuggestions(normalizedQuery, limit);
    
    // Convert suggestions to SearchResult with movie indices
    for (const string& suggestion : suggestions) {
        if (titleToIndexMap.find(suggestion) != titleToIndexMap.end()) {
            const vector<int>& indices = titleToIndexMap[suggestion];
            for (int idx : indices) {
                if (results.size() >= (size_t)limit) break;
                SearchResult result;
                result.title = movies[idx].title;
                result.movieIndex = idx;
                results.push_back(result);
            }
        }
    }
    
    // If no results from Trie, try substring matching
    if (results.empty()) {
        for (size_t i = 0; i < movies.size() && results.size() < (size_t)limit; i++) {
            string normalized = normalizeString(movies[i].title);
            if (normalized.find(normalizedQuery) != string::npos) {
                SearchResult result;
                result.title = movies[i].title;
                result.movieIndex = i;
                results.push_back(result);
            }
        }
    }
    
    return results;
}
