#include "trie.h"

#include <algorithm>
#include <iostream>

Trie::Trie() { root = std::make_unique<TrieNode>(); }

void Trie::insert(const std::string& word, int frequency) {
  TrieNode* current = root.get();
  // std::cout << "Inserting word: " << word << std::endl;

  for (char c : word) {
    // std::cout << "Processing char: " << c << std::endl;

    if (current->children.find(c) == current->children.end()) {
      // std::cout << "  Creating new node for: " << c << std::endl;
      current->children[c] = std::make_unique<TrieNode>();
    } else {
      // std::cout << "  Node for " << c << " already exists" << std::endl;
    }

    current = current->children[c].get();
    current->wordsPassingThrough++;
    // std::cout << "  Words passing through this node: " <<
    // current->wordsPassingThrough << std::endl;
  }

  // std::cout << "Marking end of word" << std::endl;
  current->isEndOfWord = true;
  current->word = word;
  current->frequency = frequency;
  current->wordsEndingHere++;
  // std::cout << "Insert completed for: " << word << std::endl << std::endl;
}

bool Trie::search(const std::string& word) const {
  TrieNode* current = root.get();

  for (int i = 0; i < word.size(); i++) {
    if (current->children.count(word[i]) == 0) {
      return false;
    }
    current = current->children[word[i]].get();
  }
  return current->isEndOfWord;
}

TrieNode* Trie::findPrefixNode(const std::string& prefix) const {
  TrieNode* current = root.get();

  for (char c : prefix) {
    auto it = current->children.find(c);
    if (it == current->children.end()) {
      return nullptr;
    }
    current = it->second.get();
  }

  return current;
}

void Trie::collectWords(
    TrieNode* node, std::vector<std::pair<std::string, int>>& results) const {
  if (node->isEndOfWord) {
    results.push_back({node->word, node->frequency});
  }

  for (const auto& child : node->children) {
    collectWords(child.second.get(), results);
  }
}

std::vector<std::pair<std::string, int>> Trie::autocomplete(
    const std::string& prefix, int maxResults) const {
  TrieNode* prefixNode = findPrefixNode(prefix);
  if (prefixNode == nullptr) {
    return {};
  }

  std::vector<std::pair<std::string, int>> results;
  collectWords(prefixNode, results);

  std::sort(results.begin(), results.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

  if (results.size() > maxResults) {
    results.resize(maxResults);
  }

  return results;
}
