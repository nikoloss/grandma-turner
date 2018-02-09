# Your Grandma's Turner
If it rains today, something something remain


### How to use
####Linux:
```bash
$/> mkdir build
$/> cd build
$/> cmake ..
$/> make
$/> sudo make install
```
then you will have gtlib in your system
### Demo app
#### after installed gtlib
##### trieapp:
```bash
$/> cd app/trieapp
$/> gcc main.c `pkg-config --cflags --libs gtlib`
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