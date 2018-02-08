//
// Created by Rowland@Sjet on 2018/1/28.
//

#ifndef GRANDMATRUNER_GTSTACK_H
#define GRANDMATRUNER_GTSTACK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"
typedef struct GtStack GtStack;

GT_API GtStack* gt_stack_create(size_t);
GT_API int gt_stack_push(GtStack*, void*);
GT_API int gt_stack_pop(GtStack*, void**);
GT_API void gt_stack_destroy(GtStack**);

#ifdef __cplusplus
}
#endif
#endif //
