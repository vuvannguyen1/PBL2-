#pragma once
#include <string>
#include <vector>
using namespace std;

class TrieNode  {
    public: 
        bool isEnd;
        TrieNode* children[26];
        TrieNode();
};

class Trie {
    private:
        TrieNode* root;
        void dfs(TrieNode*, string, vector<string>&, int);    
    public: 
        Trie();
        void insert(const string&);
        bool search(const string&);
        bool startsWith(const string&);
        vector<string> getSuggestions(const string&, int limit = 5);
};

