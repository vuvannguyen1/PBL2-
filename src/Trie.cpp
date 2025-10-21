#include "Trie.h"
#include <algorithm>
#include <locale>
#include <codecvt>

// Helper function to normalize Vietnamese characters and convert to lowercase
string normalizeString(const string& str) {
    string result = str;
    // Convert to lowercase
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Helper function to get index for a character (supports more than just a-z)
int getCharIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return -1; // For non-alphabetic characters, we'll handle them specially
}

TrieNode::TrieNode() : isEnd(false) {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const string& word) {
    if (word.empty()) return;
    
    string normalized = normalizeString(word);
    TrieNode* current = root;
    
    for (char c : normalized) {
        int index = getCharIndex(c);
        if (index == -1) continue; // Skip non-alphabetic characters
        
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    current->isEnd = true;
}

bool Trie::search(const string& word) {
    if (word.empty()) return false;
    
    string normalized = normalizeString(word);
    TrieNode* current = root;
    
    for (char c : normalized) {
        int index = getCharIndex(c);
        if (index == -1) continue;
        
        if (current->children[index] == nullptr) {
            return false;
        }
        current = current->children[index];
    }
    return current != nullptr && current->isEnd;
}

bool Trie::startsWith(const string& prefix) {
    if (prefix.empty()) return true;
    
    string normalized = normalizeString(prefix);
    TrieNode* current = root;
    
    for (char c : normalized) {
        int index = getCharIndex(c);
        if (index == -1) continue;
        
        if (current->children[index] == nullptr) {
            return false;
        }
        current = current->children[index];
    }
    return current != nullptr;
}

void Trie::dfs(TrieNode* node, string current, vector<string>& results, int limit) {
    if (results.size() >= (size_t)limit) return;
    
    if (node->isEnd) {
        results.push_back(current);
    }
    
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            char c = 'a' + i;
            dfs(node->children[i], current + c, results, limit);
        }
    }
}

vector<string> Trie::getSuggestions(const string& prefix, int limit) {
    vector<string> results;
    if (prefix.empty()) return results;
    
    string normalized = normalizeString(prefix);
    TrieNode* current = root;
    
    // Navigate to the prefix node
    for (char c : normalized) {
        int index = getCharIndex(c);
        if (index == -1) continue;
        
        if (current->children[index] == nullptr) {
            return results; // Prefix not found
        }
        current = current->children[index];
    }
    
    // DFS to find all words with this prefix
    dfs(current, normalized, results, limit);
    return results;
}
