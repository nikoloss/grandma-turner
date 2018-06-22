#### after installed gtlib
##### This is a dictionary function using trie data structure:
```bash
$/> cd app/trieapp
$/> clang dict.c `pkg-config --cflags --libs gtlib`
$/> ./a.out data.txt
LOOK FOR? /> di
Not found but I have 3 candidates
	dispensed
	discover
	directly
LOOK FOR? /> this
found it! this
LOOK FOR? /> ?esc
bye bye!
$/>
```