//
// Created by 罗然 on 2018/6/16.
//
#include "../include/gtlist.h"
#include <stdlib.h>

typedef struct GtListEntry GtListEntry;

struct GtList {
    GtListEntry *entry;
};

struct GtListEntry {
    GtValue data;
    GtListEntry *prev;
    GtListEntry *next;
};

struct GtListIter{
    GtListEntry* head;
    GtListEntry* current;
};

GtList *gt_list_create() {
    GtList *out = (GtList *) malloc(sizeof(GtList));
    if (!out) exit(GT_STATUS_OUTMEN);

    out->entry = NULL;
    return out;
}

unsigned int gt_list_size(GtList *in) {
    unsigned int size = 0;
    if (in != NULL) {
        GtListEntry* entry = in->entry;
        while(entry){
            size++;
            entry=entry->next;
        }
    }
    return size;
}

//append newEntry after entries
static void gt_entry_append(GtListEntry** entryAddress, GtListEntry* newEntry){
    if(!entryAddress||!newEntry) return;
    if(!*entryAddress){
        //if list is empty, set list's head address to newEntry's address
        *entryAddress = newEntry;
    }else{
        GtListEntry* entry = *entryAddress;
        while(entry->next){
            entry=entry->next;
        }
        //here we arrive the last entry!
        entry->next = newEntry;
        newEntry->prev = entry;
    }
}

//add newEntry before entry
static void gt_entry_insert(GtListEntry** entryAddress, GtListEntry* newEntry){
    if(!entryAddress||!newEntry) return;
    if(!*entryAddress){
        //if list is empty, set list's head address to newEntry's address
        *entryAddress = newEntry;
    }else{
        GtListEntry* entry = *entryAddress;
        newEntry->next = entry;
        newEntry->prev = entry->prev;
        if(entry->prev){
            entry->prev->next = newEntry;
        }else{
            //newEntry is the first element
            *entryAddress = newEntry;
        }
        entry->prev = newEntry;
    }
}

//remove current entry
static void gt_entry_remove(GtListEntry** entryAddress){
    if(!entryAddress) return;
    GtListEntry* entry = *entryAddress;
    if(!entry->next&&!entry->prev){
        //check if this entry is the only one in the list
        *entryAddress = NULL;
    }else{
        if(entry->prev) {
            entry->prev->next = entry->next;
        }else{
            //delete first one
            *entryAddress = entry->next;
        }
        if(entry->next) entry->next->prev = entry->prev;
    }
    free(entry);
}

// Would use "append" instead if index is a negative value
gt_status gt_list_insert(GtList *in, int index, GtValue value) {
    if (!in||!value) return GT_STATUS_NULL;
    GtListEntry *newEntry = (GtListEntry *) malloc(sizeof(GtListEntry));
    if (!newEntry) return GT_STATUS_OUTMEN;
    newEntry->data = value;
    newEntry->prev = NULL;
    newEntry->next = NULL;

    GtListEntry** entry = &in->entry;
    if (index<0){
        //如果是负数，直接追加至末尾
        gt_entry_append(entry, newEntry);
        return GT_STATUS_OK;
    }
    //遍历步长
    while ((*entry)->next) {
        if(index==0) break;
        index--;
        entry = &(*entry)->next;
    }
    if(index>0) return GT_STATUS_OVER_INDEX;
    gt_entry_insert(entry, newEntry);
    return GT_STATUS_OK;
}

gt_status gt_list_append(GtList *in, GtValue value) {
    if (!in||!value) return GT_STATUS_NULL;
    GtListEntry *newEntry = (GtListEntry *) malloc(sizeof(GtListEntry));
    if (!newEntry) return GT_STATUS_OUTMEN;
    newEntry->data = value;
    newEntry->prev = NULL;
    newEntry->next = NULL;
    gt_entry_append(&in->entry, newEntry);
    return GT_STATUS_OK;
}

gt_status gt_list_get(GtList *in, int index, GtValue *value) {
    if (!in||!value) return GT_STATUS_NULL;
    if (!in->entry) return GT_STATUS_EMPTY;
    GtListEntry* entry = in->entry;
    while(entry){
        if(index==0) break;
        index--;
        entry = entry->next;
        if(!entry) return GT_STATUS_OVER_INDEX;
    }
    *value = entry->data;
    return GT_STATUS_OK;
}

void gt_list_destroy(GtList** in){
    if(*in){
        GtList* gtList = *in;
        GtListEntry* entry = gtList->entry;
        GtListEntry* next;
        while(entry){
            next = entry->next;
            free(entry);
            entry = next;
        }
        free(gtList);
        *in = NULL;
    }
}

GtListIter* gt_list_iterator_create(GtList *in){
    if(!in) return NULL;
    GtListIter* gtListIter = malloc(sizeof(GtListIter));
    gtListIter->head = (GtListEntry *) malloc(sizeof(GtListEntry));
    if (!gtListIter->head) exit(GT_STATUS_OUTMEN);
    gtListIter->head->data = NULL;
    gtListIter->head->prev = NULL;
    gtListIter->head->next = in->entry;
    gtListIter->current = gtListIter->head;
    return gtListIter;
}

GT_BOOL gt_list_iterator_has_next(GtListIter* in){
    if(!in) return 0;
    GtListIter* iter = in;
    return iter->current->next!=NULL;
}

gt_status gt_list_iterator_next(GtListIter* iter, GtValue* value){
    if(!iter) return GT_STATUS_NULL;
    if(iter->current){
        iter->current = iter->current->next;
    }
    if(value){
        *value = iter->current->data;
    }
    return GT_STATUS_OK;
}

gt_status gt_list_iterator_val(GtListIter* iter, GtValue* value){
    if(!iter) return GT_STATUS_NULL;
    if(value){
        *value = iter->current->data;
    }
    return GT_STATUS_OK;
}

gt_status gt_list_iterator_remove(GtListIter* iter){
    if(!iter||!iter->current) return GT_STATUS_NULL;
    gt_entry_remove(&iter->current);
    return GT_STATUS_OK;
}

void gt_list_iterator_destroy(GtListIter** in){
    if(*in){
        GtListIter* gtListIter = *in;
        free(gtListIter->head);
        free(gtListIter);
        *in = NULL;
    }
}
