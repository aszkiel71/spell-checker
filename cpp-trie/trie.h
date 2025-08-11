#ifndef TRIE_H
#define TRIE_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class TrieNode {
 private:
  std::unordered_map<char, std::unique_ptr<TrieNode>> children;
  bool isEndOfWord = false;
  std::string word;  // if isEndOfWord then whole word

  // informations
  int wordsPassingThrough = 0;
  int wordsEndingHere = 0;  // assume multiwords
  int frequency = 0;

  // ranking
  std::vector<std::pair<std::string, int>>
      topCompletions;  // top-k words (cache)

  friend class Trie;
};

class Trie {
 private:
  std::unique_ptr<TrieNode> root;

  // helpers
  TrieNode* findPrefixNode(const std::string& prefix) const;

  void collectWords(TrieNode* node,
                    std::vector<std::pair<std::string, int>>& results) const;

 public:
  Trie();
  void insert(const std::string& word, int frequency = 1);
  bool search(const std::string& word) const;
  std::vector<std::pair<std::string, int>> autocomplete(
      const std::string& prefix, int maxResults = 10) const;
};

#endif
