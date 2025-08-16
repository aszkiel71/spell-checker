# Spell Checker

## About this project
This project can be helpful if you want to fix spelling mistakes.
It shows how it's possible to connect 3 different technologies.

**Note:** This approach prioritizes showcasing integration skills over optimal Python usage. Treat it as a demonstration of multi-technology orchestration.

Provided words.txt is a Polish dictionary.
You can use your own but make sure the format is readable.

## Used structures, algorithms etc
- **Trie** - contain words
- **DFS** - searching words with given prefix
- **Daemon** - background process
- **Levenshtein** - searching best match
- **OOP** rules, paradigms

## How to use?
Assume we are in main directory.

### To compile CPP:
```bash
g++ ./cpp-service/trie_service.cpp ./cpp-service/trie.cpp -o ./cpp-service/trie_service
```

### Then we go to node-orchestrator:
```bash
cd node-orchestrator
```

### To fix sentences from Command Line:
```bash
node sc.js "polskaa konstytucje policjak"
```

### To redirect to file:
```bash
node sc.js "polskaa konstytucje policjak" > output.txt
```

### To fix file:
```bash
node sc.js input.txt
```

### To redirect to file:
```bash
node sc.js input.txt > output.txt
```

## Other functionality:
```bash
cd cpp-service
./trie-service --daemon
```

Then you can use:
- `help` → show commands
- `search word` → to search if word exists
- `autocomplete prefix` → get words starting with prefix
- `exit` → shutdown daemon

## How it works?
1. User provides word.
2. SC.js asks trie_service.cpp about words:
   - If it exists in dictionary, we don't have anything to fix.
   - If does not exist → we find all words with prefix.
3. Prefix length depends on length of word.
4. Then SC.js asks spell_corrector.py for best matched word from provided words and returns it.
5. We can fix whole sentences.
6. We do not initialize dictionary for each word - we do it at the start using Daemon.
7. We fix sentence word by word.

## Worktime:
Approximately:

### C++
- **6h** → implementing Trie, debugging, testing
- **3.5h** → learning about CLI, daemon process, implementing

### Python
- **0.5h** → implementing Levenshtein distance, testing

### Node
- **8h** → learning node.js, implementing, debugging process, connecting

**Total: 18h**

## Author
[Wojtek Aszkielowicz](https://github.com/aszkiel71)

## License
Project is based on MIT license

## Tech Stack
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Node.js](https://img.shields.io/badge/Node.js-43853D?style=for-the-badge&logo=node.js&logoColor=white)
