//
// Created by rowland on 18-2-8.
//

#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <string.h>
#include <ctype.h>
#include <gt/gtstack.h>
#include <gt/gttrie.h>

GtStack* stack = NULL;

void travel(GtTrieValue value){
    gt_stack_push(stack, value);
}

void fetch_candidate_words(GtTrie* trie, GtStack* stack, char* word){
    char *p = (char*)calloc(64, sizeof(char));
    strncpy(p, word, strlen(word));
    int depth;
    for(;;) {
        int len = strlen(p);
        if(len==0) break;
        depth = len + 8; //多向下遍历几层
        gt_trie_travel(trie, p, travel, depth);
        if(gt_stack_counts(stack)) break;
        //not match any
        p[--len] = '\0';
    }
    free(p);
}

void words_training(GtTrie* trie, FILE* fp){
    int c = fgetc(fp);
    if(c==EOF) return;
    while(!isalpha(c)){
        c = fgetc(fp);
        if(c==EOF) return;
    }
    //剩下来的都是合法字符
    char* word = (char*)calloc(64, sizeof(char));
    char* p = word;
    while(isalpha(c)) {
        c = tolower(c);//统一小写
        *p++ = c;
        c = fgetc(fp);
    }
    //单词结尾
//    printf("training:%s\n", word);
    gt_trie_insert(trie, word, word);
    words_training(trie, fp);
}

int main(int argc, char* argv[]){
    mtrace();

    stack = gt_stack_create(10);
    GtTrie* trie = gt_trie_create();
    char** tmp = argv;
    if(argc < 2){
        printf("usage:%s {file}\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    words_training(trie, fp);

    char in[64]; char* p;
    int err;
    int esc = 0;
    while(!esc) {
        printf("LOOK FOR? /> ");
        scanf("%s", in);
        if(!strcmp(in, "?esc")){
            esc = 1;
            continue;
        }
        if ((err = gt_trie_find(trie, in, (void **) &p)) == GT_OK) {
            printf("found it! %s\n", p);
        } else {
            fetch_candidate_words(trie, stack, in);
            int counts = gt_stack_counts(stack);
            printf("Not found but I have %d candidates\n", counts);
            while ((err = gt_stack_pop(stack, (void **) &p)) == GT_OK) {
                printf("\t%s\n", p);
            }
        }
    }
    printf("bye bye!\n");
    gt_trie_destroy(&trie);
    gt_stack_destroy(&stack);
    return EXIT_SUCCESS;
}