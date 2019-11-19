# Your Grandma's Turner
if on St. Swithin's day, it doth rain, something something, something remain


### How to use
#### Install in Linux & Mac:
```bash
$/> mkdir build
$/> cd build
$/> cmake ..
$/> make
$/> make test
$/> sudo make install
```
then you will have gtlib in your system
#### Getting start
```c
#include <stdio.h>
#include <stdlib.h>
#include <gt/gtstack.h>

int main(){
    GtStack* stack = gt_stack_create(10);
    gt_stack_push(stack, "顺丰");
    gt_stack_push(stack, "韵达");
    gt_stack_push(stack, "申通");
    gt_stack_push(stack, "圆通");
    GtValue p;
    int err;
    while((err=gt_stack_pop(stack, &p))==GT_STATUS_OK){
        printf("pop:%s\n", (char*)p);
    }
    gt_stack_destroy(&stack);
    return EXIT_SUCCESS;
}
```
#### compile
```bash
$ />clang main.c `pkg-config --cflags --libs gtlib`
```


### Demo app
[Dictionary](demos/trieapp/readme.md)
