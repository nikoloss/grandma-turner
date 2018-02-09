//
// Created by rowland on 18-2-8.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gt/gtstack.h>
#include <gt/gttrie.h>

GtStack* stack = NULL;  //栈，全局变量

/*
 * 回调函数，将找到的值压栈
 */
void travel(GtTrieValue value){
    gt_stack_push(stack, value);
}
/*
 * 抓取候选词的思路是这样：
 * 首先让我们假设word为“hella”
 * 首先我们按照h->e->l->l->a的层级遍历查找节点，如果找到了（栈不为空）则返回栈
 * 如果没有找到则把最后一个字符干掉重新来过，h->e->l->l。倒过来做是为了找相似度
 * 比较高的单词。
 */
void fetch_candidate_words(GtTrie* trie, GtStack* stack, char* word){
    char *p = (char*)calloc(64, sizeof(char));
    strncpy(p, word, strlen(word));
    int depth;
    for(;;) {
        int len = strlen(p);
        if(len==0) break;
        depth = len + 8; //多向下遍历8层
        gt_trie_travel(trie, p, travel, depth);
        if(gt_stack_counts(stack)) break;
        //not match any
        p[--len] = '\0';
    }
    free(p);
}
/*
 * 通过一片文章来构建trie树的节点是最方便的嘛
 * 每次从文件中向后读取一个字符，如果是字母就认为是单词开头
 * 于是把字符写入字符串word直到非字母字符发生，认为单词结尾
 * 再把单词插入trie树以完成通过文件自动构建trie树的目的
 */
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
        *p++ = c;
        c = fgetc(fp);
    }
    //单词结尾！
//    printf("training:%s\n", word);
    gt_trie_insert(trie, word, word); //插入
    words_training(trie, fp); //继续整个过程直到fp被耗尽
}

int main(int argc, char* argv[]){
    stack = gt_stack_create(10);
    GtTrie* trie = gt_trie_create();
    char** tmp = argv;
    if(argc < 2){
        printf("usage:%s {file}\n", argv[0]);
        return EXIT_FAILURE;
    }
    char* filename = argv[1];
    FILE* fp = fopen(filename, "r");
    words_training(trie, fp); //训练trie树之后就可以拿来做功能了

    char in[64]; char* p;
    int err;
    int esc = 0;
    while(!esc) {
        printf("LOOK FOR? /> ");
        scanf("%s", in); //读入输入的字符串
        if(!strcmp(in, "?esc")){ //如果用户输入了“?ecs”则退出该程序
            esc = 1;
            continue;
        }
        if ((err = gt_trie_find(trie, in, (void **) &p)) == GT_OK) {
            //如果找到这个节点且节点数据域就是单词本身
            printf("found it! %s\n", p);
        } else {
            //如果没有找到节点值，说明没有这个单词，启动遍历相似单词的程序
            fetch_candidate_words(trie, stack, in);
            int counts = gt_stack_counts(stack);
            printf("Not found but I have %d candidates\n", counts);
            while ((err = gt_stack_pop(stack, (void **) &p)) == GT_OK) {
                printf("\t%s\n", p);
            }
        }
    }
    printf("bye bye!\n");
    //擦屁股，remember always 擦屁股
    gt_trie_destroy(&trie);
    gt_stack_destroy(&stack);
    return EXIT_SUCCESS;
}