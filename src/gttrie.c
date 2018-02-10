//
// Created by rowland on 18-2-8.
//
#include <stdlib.h>
#include <stdio.h>
#include "../include/gttrie.h"

typedef struct GtTrieNode GtTrieNode;

struct GtTrieNode{
    unsigned int ref; //引用计数器
    GtTrieValue data; //数据域
    GtTrieNode* nodes[GTMAXCHAR]; //子节点
};

struct GtTrie{
    unsigned long counts;
    GtTrieNode* root;
};

GtTrie* gt_trie_create(){
    GtTrie* out = (GtTrie*)malloc(sizeof(GtTrie));
    if(!out) exit(GT_ERROR_OUTMEM);

    out->counts=0; out->root = NULL;
    return out;
}

long gt_trie_counts(GtTrie* trie){
    return trie->counts;
}

/*
 * 节点查询
 */
static GtTrieNode* gt_trie_node_find(GtTrie* trie, char* key){
    char *p = key;
    unsigned int c;
    GtTrieNode* node = trie->root;
    for(;;){
        if(!node) return NULL;
        if(*p=='\0'){
            return node;
        }
        c = (unsigned int)*p;
        node = node->nodes[c];
        p++;
    }
}

/*
 * 思路是先查询节点，但是查询到的节点不一样有数据比如我有key值为abcd的节点
 * 第一层的节点是a，但是a这个节点并没有实际数值，包括a的子节点b，层层递进
 * 到d的时候才有数据
 */
int gt_trie_find(GtTrie* trie, char* key, GtTrieValue* value){
    GtTrieNode* node = gt_trie_node_find(trie, key);
    if(node&&node->data){
        *value = node->data;
        return GT_OK;
    }
    return GT_ERROR_EMPTY;
}

/*
 * 插入就是根据key字符层层递进下去直到key结尾，此时把value更新到节点的
 * 数据域
 */
int gt_trie_insert(GtTrie* trie, char* key, GtTrieValue value){
    if(!value) return GT_ERROR_EMPTY;

    char* p = key;
    unsigned int c;
    GtTrieNode** rover = &trie->root;
    //查查是否已经存在这个节点
    GtTrieNode* node = gt_trie_node_find(trie, key);
    if(node){
        //这么做主要是为了更新重复的节点又不增加引用计数器
        node->data = value;
        return GT_OK;
    }
    trie->counts++;

    for(;;){
        if(!(*rover)){
            node = (GtTrieNode*)malloc(sizeof(GtTrieNode));
            if(!node) exit(GT_ERROR_OUTMEM);
            node->ref = 0; node->data = NULL;
            *rover = node;
        }
        //增加引用计数器
        (*rover)->ref++;
        c = (unsigned int)*p;
        if(*p == '\0'){
            (*rover)->data = value;
            break;
        }
        rover = &(*rover)->nodes[c];
        p++;
    }
    return GT_OK;
}

/*
 * 删除不能单纯的find，free，比如“abcde”和“abcdf”
 * 删除其中abcde可不能把沿途的abcd节点全部删除，否则
 * 就不能访问abcdf了，free的逻辑类似insert，只不过在
 * 向下遍历的时候对每个节点进行引用计数器减一的操作，
 * 并把引用计数器为0的free掉。这里也显示出c/c++对内存
 * 外科手术刀式的精准操作，真是魅力无穷呀
 */
int gt_trie_remove(GtTrie* trie, char* key){
    char* p = key;
    unsigned int c;
    GtTrieNode** rover = &trie->root;
    GtTrieNode* node = gt_trie_node_find(trie, key);
    if(!node) return GT_ERROR_EMPTY;
    trie->counts--;
    for(;;){
        if(--(*rover)->ref==0){
            free(*rover);
            *rover = NULL;
        }
        c = (unsigned int)*p;
        if(*p=='\0') break;
        rover = &(*rover)->nodes[c];
        p++;
    }
    return GT_OK;
}

/*
 * 从某个节点开始遍历，depth为剩余遍历深度
 */
static void gt_trie_node_travel(GtTrieNode* node,
                                void(*traveller)(GtTrieValue),
                                unsigned int depth){
    if(!node) return;
    if(depth<=0) return;
    GtTrieNode** rover = node->nodes;
    if(node->data){
        //call back
        traveller(node->data);
    }

    depth--;
    for(int i=0;i<GTMAXCHAR;i++){
        //把这一层全部遍历一遍
        gt_trie_node_travel(rover[i], traveller, depth);
    }
}

/*
 * 先根据key找到节点，再从这个节点开始遍历
 */
void gt_trie_travel(GtTrie* trie,
                    char* key,
                    void(*traveller)(GtTrieValue),
                    unsigned int depth){
    char* p = key;
    unsigned int c;
    GtTrieNode* node = trie->root;
    if(!node) return;
    while(*p!='\0'){
        c = (unsigned int) *p;
        node = node->nodes[c];
        if(!node) return;
        depth--;
        p++;
    }
    gt_trie_node_travel(node, traveller, depth);
}

static void gt_trie_node_destroy(GtTrieNode *node){
    //把子节点保存下来，免得把父节点free掉了就访问不到了
    GtTrieNode** rover = node->nodes;
    //*rover = NULL;
    for(int i=0;i<GTMAXCHAR;i++){
        if(rover[i]){
            gt_trie_node_destroy(rover[i]);
        }
    }
    free(node);
}

void gt_trie_destroy(GtTrie** in){
    if(*in){
        GtTrie* trie = *in;
        if(trie->root){
            gt_trie_node_destroy(trie->root);
        }
        free(trie);
        *in = NULL;
    }
}
