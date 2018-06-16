//
// Created by 罗然 on 2018/6/16.
//
#include "../include/gtlist.h"
#include <stdlib.h>

typedef struct GtListEntry GtListEntry;

struct GtList {
    unsigned int size;
    GtListEntry *entry;
};

struct GtListEntry {
    GtValue data;
    GtListEntry *prev;
    GtListEntry *next;
};

GtList *gt_list_create() {
    GtList *out = (GtList *) malloc(sizeof(GtList));
    if (!out) exit(GT_STATUS_OUTMEN);

    out->size = 0;
    out->entry = NULL;
    return out;
}

unsigned int gt_list_size(GtList *in) {
    unsigned int size = 0;
    if (in != NULL) {
        size = in->size;
    }
    return size;
}

GT_STATUS gt_list_insert(GtList *in, unsigned int index, GtValue value) {
    if (!in) return GT_STATUS_NULL;
    GtListEntry *newEntry = (GtListEntry *) malloc(sizeof(GtListEntry));
    if (!newEntry) return GT_STATUS_OUTMEN;
    newEntry->data = value;
    newEntry->prev = NULL;
    newEntry->next = NULL;

    unsigned int position = index;
    if(in->size==0){
        position = 0;
    }else{
        position = in->size-1;
    }
    GtListEntry* entry = in->entry;

    if (!entry) {
        in->entry = newEntry;
    } else {

        while (entry && position) {
            position--;
            entry = entry->next;
        }

        newEntry->prev = entry;
        entry->next = newEntry;
        if (entry->next) {
            newEntry->next = entry->next;
            entry->next->prev = newEntry;
        }
    }
    in->size++;
    return GT_STATUS_OK;
}

GT_STATUS gt_list_append(GtList *in, GtValue value) {
    return gt_list_insert(in, in->size, value);
}

GT_STATUS gt_list_get(GtList *in, unsigned int index, GtValue *value) {
    if (!in) return GT_STATUS_NULL;
    if (index>in->size) return GT_STATUS_OVER_INDEX;
    GtListEntry* entry = in->entry;
    while(index){
        index--;
        entry = entry->next;
    }
    *value = entry->data;
    return GT_STATUS_OK;
}

GT_STATUS gt_list_remove(GtList *in, unsigned int index, GtValue *value){
    if(!in) return GT_STATUS_NULL;
    if(index>in->size) return GT_STATUS_OVER_INDEX;
    GtListEntry* entry = in->entry;
    while(index){
        index--;
        entry = entry->next;
    }
    *value = entry->data;
    if(entry->prev){
        entry->prev->next = entry->next;
    }else{
        in->entry = entry->next;
    }
    if(entry->next){
        entry->next->prev = entry->prev;
    }
    free(entry);
    in->size--;
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