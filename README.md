### Spell Checker

#### About this project:
This project can be helpful if you want to fix spelling mistakes.
It shows how it's possible to connect 3 differents technologies.
**Note:** This approach prioritizes showcasing integration skills over optimal Python usage. Treat it as a demonstration of multi-technology orchestration.

Provided words.txt is a Polish dictionary.
You can use your own but make sure the format is readible.

#### Used structures, algorithms etc
**Trie** - contain words
**Dfs** - searching words with given prefix
**Daemon** - background process
**Levenhstein** - searching best match
**OOP** rules, paradigms


#### How to use?
Assume we are in main directory.
To compile CPP:
``g++ ./cpp-service/trie_service.cpp ./cpp-service/trie.cpp -o ./cpp-service/trie_service``
Then we go to node-orchestratr:
``cd node-orchestrator``
To translate sentences from Command Line:
``node sc.js "polskaa konstytucye policjak"``
To redirect to file:
``node sc.js "polskaa konstytucye policjak" > output.txt``
To translate file:
``node sc.js input.txt``
To redicrect to file:
``node sc.js input.txt > output.txt``

#### Other functionality:
``cd cpp-service``
``./trie-service --daemon``
Then you can use:
``help`` -> show commands
``search word`` -> to search if word exist
``autocomplete prefix`` -> get words starting with prefix
``exit`` -> shutdown daemon


#### How it works?
User provide word.
SC.js ask trie_service.cpp about words:
if it exist in dictionary, we don't have anything to fix.
If does not exist -> we find all words with prefix.
Prefix length depends on length od word.
Then SC.js ask spell_corrector.py for best matched word from provided words and return it.
We can translate whole sentences.
We do not initialize dictionary for each word - we do it at the start using Daemon.
We translate sentece word by word.


#### Worktime:

Approximately:

**C++** :
    ##### 6h -> implementing Trie, debugging, testing
    ##### 3.5h -> learning about CLI, daemon process, implementing

**Python** :
    ##### 0.5h -> implementing Levenshtein distance, testing

**Node** :
    ##### 8h -> learning node.js, implementing, debugging process, connecting

##### Total: 18h

#### Author:
[Wojtek Aszkielowicz](https://github.com/aszkiel71)

#### License:
project is based on MIT license

#### Tech stack:
python, cpp, nodejs
