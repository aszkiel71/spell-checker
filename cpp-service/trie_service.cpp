#include <iostream>
#include <sstream>
#include <string>

#include "trie.h"


void show_help() {
    std::cout << "=== Polish Spell Checker - Trie Service ===\n";
    std::cout << "Multi-language spell checking system with C++/Python/Node.js\n\n";

    std::cout << "DAEMON MODE:\n";
    std::cout << "  ./trie_service --daemon\n";
    std::cout << "    Starts interactive daemon mode\n";
    std::cout << "    Commands available in daemon mode:\n";
    std::cout << "      help                    - Show this help\n";
    std::cout << "      search <word>           - Check if word exists (true/false)\n";
    std::cout << "      autocomplete <prefix>   - Get words starting with prefix\n";
    std::cout << "      exit                    - Shutdown daemon\n\n";

    std::cout << "SINGLE COMMAND MODE:\n";
    std::cout << "  ./trie_service search <word>\n";
    std::cout << "    Check if word exists in dictionary\n";
    std::cout << "    Example: ./trie_service search polska\n\n";

    std::cout << "  ./trie_service autocomplete <prefix>\n";
    std::cout << "    Get words starting with given prefix\n";
    std::cout << "    Example: ./trie_service autocomplete pol\n\n";


    std::cout << "EXAMPLES:\n";
    std::cout << "  # Interactive daemon mode:\n";
    std::cout << "  $ ./trie_service --daemon\n";
    std::cout << "  Trie loaded, ready for commands\n";
    std::cout << "  > search polska\n";
    std::cout << "  true\n";
    std::cout << "  > autocomplete pol\n";
    std::cout << "  polska,polski,polskie,polityka,...\n";
    std::cout << "  > exit\n\n";




    std::cout << "For more info, see README.md\n";
    std::cout.flush();
}

int main(int argc, char* argv[]) {
  if (argc > 1 && std::string(argv[1]) == "--daemon") {
    Trie dict;
    dict.loadFromFile("../cpp-service/words.txt");
    std::cerr << "Trie loaded, ready for commands" << "\n";
    std::string line;
    while (std::getline(std::cin, line)) {
      if (line.empty()) continue;

      std::istringstream iss(line);
      std::string cmd, word;
      iss >> cmd >> word;
      if (cmd == "help"){
        show_help();
      }
      else if (cmd == "search") {
        bool res = dict.search(word);
        std::cout << (res ? "true" : "false") << "\n";
        std::cout.flush();

      } else if (cmd == "autocomplete") {
        auto results = dict.autocomplete(word, 1337);
        for (size_t i = 0; i < results.size(); i++) {
          std::cout << results[i].first;
          if (i < results.size() - 1) std::cout << ",";
        }
        std::cout << "\n";
        std::cout.flush();

      } else if (cmd == "exit") {
        std::cerr << "Shutting down daemon..." << "\n";
        break;

      } else {
        std::cout << "unknown_command" << "\n";
        std::cout.flush();
      }
    }

    return 0;
  }

  if (argc < 2) return 1;
}
