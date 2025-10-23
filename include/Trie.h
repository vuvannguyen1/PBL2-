#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

class TrieNode  {
    public: 
        bool isEnd;
        map<unsigned char, TrieNode*> children; // Dùng map thay vì array để hỗ trợ UTF-8
        TrieNode();
        ~TrieNode();
};

class Trie {
    private:
        TrieNode* root;
        void dfs(TrieNode*, string, vector<string>&, int);    
    public: 
        Trie();
        ~Trie();
        void insert(const string&);
        bool search(const string&);
        bool startsWith(const string&);
        vector<string> getSuggestions(const string&, int limit = 5);
};

