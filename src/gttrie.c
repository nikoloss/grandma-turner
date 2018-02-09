//
// Created by rowland on 18-2-8.
//
#include <stdlib.h>
#include <stdio.h>
#include "../include/gttrie.h"

typedef struct GtTrieNode GtTrieNode;

struct GtTrieNode{
    unsigned int ref;
    GtTrieValue data;
    GtTrieNode* nodes[GTMAXCHAR];
};

struct GtTrie{
    long counts;
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

int gt_trie_find(GtTrie* trie, char* key, GtTrieValue* value){
    GtTrieNode* node = gt_trie_node_find(trie, key);
    if(node&&node->data){
        *value = node->data;
        return GT_OK;
    }
    return GT_ERROR_EMPTY;
}

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

    for(;;){
        if(!(*rover)){
            *rover = (GtTrieNode*)malloc(sizeof(GtTrieNode));
            (*rover)->ref = 0; (*rover)->data = NULL;
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

/**
 * 删除不能单纯的find，free，比如“abcde”和“abcdf”
 * 删除其中abcde可不能把沿途的abcd节点全部删除，否则
 * 就不能访问abcdf了，free的逻辑类似insert，只不过在
 * 向下遍历的时候对每个节点进行引用计数器减一的操作，
 * 并把引用计数器为0的free掉。
 */
int gt_trie_remove(GtTrie* trie, char* key){
    char* p = key;
    unsigned int c;
    GtTrieNode** rover = &trie->root;
    GtTrieNode* node = gt_trie_node_find(trie, key);
    if(!node) return GT_ERROR_EMPTY;

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

static void gt_trie_node_travel(GtTrieNode* node, void(*traveller)(GtTrieValue), unsigned int depth){
    if(!node) return;
    if(depth<=0) return;
    if(node->data){
        traveller(node->data);
    }
    GtTrieNode** rover = node->nodes;
    depth--;
    for(int i=0;i<GTMAXCHAR;i++){
        gt_trie_node_travel(rover[i], traveller, depth);
    }
}

void gt_trie_travel(GtTrie* trie, char* key, void(*traveller)(GtTrieValue), unsigned int depth){
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
    if(!node) return;
    GtTrieNode** rover = node->nodes;
    free(node);

    for(int i=0;i<GTMAXCHAR;i++){
        gt_trie_node_destroy(rover[i]);
    }
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
