//
// Created by Rowland@Sjet on 2018/1/28.
//

#ifndef GTLIB_GTSTACK_H
#define GTLIB_GTSTACK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"
typedef struct GtStack GtStack;

GT_API GtStack* gt_stack_create(int);
GT_API int gt_stack_counts(GtStack*);
GT_API gt_status gt_stack_push(GtStack*, GtValue);
GT_API gt_status gt_stack_pop(GtStack*, GtValue*);
GT_API gt_status gt_stack_clear(GtStack*);
GT_API void gt_stack_destroy(GtStack**);

#ifdef __cplusplus
}
#endif
#endif //
