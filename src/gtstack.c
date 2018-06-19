//
// Created by Rowland@Sjet on 2018/1/28.
//

#include <stdlib.h>
#include "../include/gtstack.h"
struct GtStack{
    int max;
    unsigned int index;
    GtValue* elems;
};

GtStack* gt_stack_create(int max){
    GtStack* out = (GtStack*)malloc(sizeof(GtStack));
    if(!out) exit(GT_STATUS_OUTMEN);

    if(max<=0) max = 16;
    out->elems = (void**)calloc((size_t)max, sizeof(void*));
    if(!out->elems) exit(GT_STATUS_OUTMEN);

    out->max = max; out->index = 0;
    return out;
}

int gt_stack_counts(GtStack* in){
    return in->index;
}

gt_status gt_stack_push(GtStack* in, GtValue data){
    if(!in) return GT_STATUS_NULL;
    if(in->index>=in->max) return GT_STATUS_FULL;

    in->elems[in->index++] = data;
    return GT_STATUS_OK;
}

gt_status gt_stack_pop(GtStack* in, GtValue* data){
    if(!in) return GT_STATUS_NULL;
    if(in->index<=0) return GT_STATUS_EMPTY;
    if(data) *data = in->elems[--in->index];
    return GT_STATUS_OK;
}

gt_status gt_stack_clear(GtStack* in){
    if(!in) return GT_STATUS_NULL;
    in->index = 0;
    return GT_STATUS_OK;
}

void gt_stack_destroy(GtStack** in){
    if(*in){
        GtStack* stack = *in;
        free(stack->elems);
        free(stack);
        *in = NULL;
    }
}
