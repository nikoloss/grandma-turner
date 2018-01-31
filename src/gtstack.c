//
// Created by Rowland@Sjet on 2018/1/28.
//

#include <stdlib.h>
#include "../include/gtstack.h"
struct gt_stack{
    int max;
    int index;
    void** elems;
};

gt_stack* gt_stack_create(int max){
    gt_stack* out = (gt_stack*)malloc(sizeof(gt_stack));
    if(!out) exit(GT_ERROR_OUTMEM);

    out->elems = (void**)calloc(max, sizeof(void*));
    if(!out->elems) exit(GT_ERROR_OUTMEM);

    if(max<=0) max = 16;
    out->max = max; out->index = 0;
    return out;
}

int gt_stack_push(gt_stack* in, void* data){
    if(in->index>=in->max) return GT_ERROR_FULL;

    in->elems[in->index++] = data;
    return GT_OK;
}

int gt_stack_pop(gt_stack* in, void** data){
    if(in->index<=0) return GT_ERROR_EMPTY;

    *data = in->elems[--in->index];
    return GT_OK;
}

void gt_stack_destroy(gt_stack** in){
    if(*in){
        gt_stack* stack = *in;
        free(stack->elems);
        free(stack);
        *in = NULL;
    }
}
