#ifndef TRIE_H
#define TRIE_H
using namespace std;

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory> 
#include <string>

class TrieNode {
    private:
        unordered_map<char, unique_ptr<TrieNode>> children;
        bool isEndOfWord;
        string completedWord; //if isEndOfWord then whole word

        // informations
        int wordsPassingThrough;
        bool wordsEndingHere; // assume without multiwords
        int frequency;

        // ranking
        vector<pair<string, int>> topCompletions; // top-k words (cache)
        bool topCompletionsValid; // is cache actual
};

#endif
