#include <iostream>

#include "trie.h"

int main() {
  Trie trie;
  std::cout << "Created trie\n";

  trie.insert("marek", 5);
  trie.insert("mareczek", 42);
  trie.insert("marekadamczyk", 1337);
  trie.insert("marik124", 10);

  std::cout << "Search 'marek': " << trie.search("marek") << std::endl;
  std::cout << "Search 'test': " << trie.search("test") << std::endl;

  auto results = trie.autocomplete("mar", 10);
  std::cout << "Autocomplete for 'mar':\n";
  for (const auto& result : results) {
    std::cout << "  " << result.first << " (" << result.second << ")\n";
  }
}
