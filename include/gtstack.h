//
// Created by Rowland@Sjet on 2018/1/28.
//

#ifndef GRANDMATRUNER_GTSTACK_H
#define GRANDMATRUNER_GTSTACK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"
typedef struct gt_stack gt_stack;

GT_API gt_stack* gt_stack_create(int);
GT_API int gt_stack_push(gt_stack*, void*);
GT_API int gt_stack_pop(gt_stack*, void**);
GT_API void gt_stack_destroy(gt_stack**);

#ifdef __cplusplus
}
#endif
#endif //
