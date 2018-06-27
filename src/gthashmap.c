//
// Created by rowland on 18-6-26.
//
#include <stdlib.h>
#include <string.h>
#include "../include/gthashmap.h"
#include "../include/gtlist.h"

#define INIT_SIZE        (16)
#define MAX_DENSITY      (0.75)

typedef void* pv;

typedef struct GtElement{
    enum {UNUSED=0, USED} used; //逻辑删除
    enum {ORIGIN=0, LIST} listified; //冲突的时候退化为链表
    char* key;
    //如果是普通值就是GtValue否则就是链表
    union {
        GtValue value;
        GtList* list;
    };
}GtElement;

struct GtHashmap{
    unsigned int counts; //元素数量
    unsigned int size;   //容量
    unsigned int (*hashing)(char*); //hash函数
    GtElement* elems;
};

static unsigned int hashing(char *key)
{
    unsigned int result = 193;
    char* p = key;
    int c;

    while (*p != '\0') {
        c = (int)*p; //把char字符转int
        c += 128;    //中文可能涉及到负数，所以+128偏移量变成正数
        result = result*32 + result + c;
        p++;
    }

    return result;
}

static gt_status gt_hash_element_put(GtHashmap* gtHashmap, char* key, GtValue value){
    if(!gtHashmap) return GT_STATUS_NULL;
    unsigned int index = gtHashmap->hashing(key)%gtHashmap->size;
    GtElement* elems = gtHashmap->elems;
    GtElement* hover = elems+index;
    //冲突
    if(hover->used){
        GtElement* new_ele = malloc(sizeof(GtElement));
        if(!new_ele) return GT_STATUS_OUTMEN;
        new_ele->used =USED;
        new_ele->key = key;
        new_ele->listified = ORIGIN;
        new_ele->value = value;
        if(hover->listified){
            //如果是链表得先遍历链表确保元素
            GtList* list = hover->list;
            GtListIter* iter = gt_list_iterator_create(list);
            if(!iter) return GT_STATUS_OUTMEN;
            GtElement* elem;
            while(gt_list_iterator_has_next(iter)){
                gt_list_iterator_next(iter, (GtValue*)&elem);
                if(!strcmp(key, elem->key)){
                    //如果找到就删除
                    gt_list_iterator_remove(iter);
                    gtHashmap->counts--;
                    break;
                }
            }
            //插入到链表中
            gt_list_insert(list, 0, new_ele);
            gt_list_iterator_destroy(&iter);
        }else if(!hover->listified){
            //如果不是链表，转成链表
            GtElement* temp = malloc(sizeof(GtElement));
            if(!temp) return GT_STATUS_OUTMEN;
            temp->listified = ORIGIN;
            temp->used = USED;
            temp->key = hover->key;
            temp->value = hover->value;
            hover->key = NULL;
            GtList* list = gt_list_create();
            if(!list) return GT_STATUS_OUTMEN;
            gt_list_append(list, new_ele);
            gt_list_append(list, temp);
            hover->list = list;
            hover->listified = LIST;
        }
    }else{
        //没有冲突就简单了……
        hover->key = key;
        hover->value = value;
        hover->used = USED;
        hover->listified = ORIGIN;
    }
    gtHashmap->counts++;
    return GT_STATUS_OK;
}

static gt_status gt_rehash(GtHashmap *in){
    unsigned int old_size = in->size;
    unsigned int new_size = in->size * 2;
    GtElement* old_elems = in->elems;
    GtElement* new_elems = (GtElement*)calloc(new_size, sizeof(GtElement));
    if(!new_elems) return GT_STATUS_OUTMEN;

    GtElement* hover;
    gt_status error;
    in->size = new_size;
    in->elems = new_elems;
    for(int i=0;i<old_size;i++){
        GtElement old_ele = old_elems[i];
        if(!old_ele.used) continue;
        if(old_ele.listified){
            GtList* list = old_ele.list;
            GtListIter* iter = gt_list_iterator_create(list);
            while(gt_list_iterator_has_next(iter)){
                gt_list_iterator_next(iter, (GtValue*)&hover);
                error = gt_hash_element_put(in, hover->key, hover->value);
                free(hover);
            }
            gt_list_iterator_destroy(&iter);
            gt_list_destroy(&list);
        }else{
            error = gt_hash_element_put(in, old_ele.key, old_ele.value);
        }
    }
    free(old_elems);
    return error;
}

GtHashmap* gt_hashmap_create(unsigned int (*hash_func)(char* k)){
    GtHashmap* out = malloc(sizeof(GtHashmap));
    if(!out){
        exit(GT_STATUS_OUTMEN);
    }

    out->elems = calloc(INIT_SIZE, sizeof(GtElement));
    if(!out->elems){
        free(out);
        exit(GT_STATUS_OUTMEN);
    }

    if(hash_func) {
        out->hashing = hash_func;
    }else{
        out->hashing = hashing;
    }
    out->size = INIT_SIZE;
    out->counts = 0;
    return out;
}

unsigned int gt_hashmap_counts(GtHashmap *gtHashmap){
    int counts = 0;
    if(gtHashmap){
        counts = gtHashmap->size;
    }
    return counts;
}

gt_status gt_hashmap_put(GtHashmap* gtHashmap, char* key, GtValue value){
    if(!gtHashmap) return GT_STATUS_NULL;
    double density = (double)gtHashmap->counts/gtHashmap->size;
    gt_status error;
    if(density>MAX_DENSITY){
        error = gt_rehash(gtHashmap);
        if(error!=GT_STATUS_OK) return error;
    }

    return gt_hash_element_put(gtHashmap, key, value);
}

gt_status gt_hashmap_get(GtHashmap* gtHashmap, char* key, GtValue *value){
    if(!gtHashmap) return GT_STATUS_NULL;
    unsigned int index = gtHashmap->hashing(key)%gtHashmap->size;
    GtElement* elems = gtHashmap->elems;
    GtElement* hover = elems + index;
    if(!hover->used) return GT_STATUS_NULL;

    //如果是链表则需要遍历比较key
    if(hover->listified){
        GtList* list = hover->list;
        GtListIter* iter = gt_list_iterator_create(list);
        GtElement* temp;
        while(gt_list_iterator_has_next(iter)){
            gt_list_iterator_next(iter, (GtValue*)&temp);
            if(!strcmp(temp->key, key)){
                //hit!
                if(value) *value = temp->value;
                return GT_STATUS_OK;
            }
        }
        return GT_STATUS_NULL;
    }else{
        if(value) *value = hover->value;
        return GT_STATUS_OK;
    }
}

gt_status gt_hashmap_remove(GtHashmap* gtHashmap, char* key){
    if(!gtHashmap) return GT_STATUS_NULL;
    unsigned int index = gtHashmap->hashing(key)%gtHashmap->size;
    GtElement* elems = gtHashmap->elems;
    GtElement* hover = elems + index;
    if(!hover->used) return GT_STATUS_NULL;

    //如果是链表需要遍历比较key，找到了就删除
    if(hover->listified){

    }
}