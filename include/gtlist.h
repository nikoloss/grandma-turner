//
// Created by 罗然 on 2018/6/16.
//

#ifndef GTLIB_GTLIST_H
#define GTLIB_GTLIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"

typedef struct GtList GtList;

GT_API GtList* gt_list_create(void);
GT_API unsigned int gt_list_size(GtList* gtList);
GT_API GT_STATUS gt_list_insert(GtList* gtList, unsigned int index, GtValue val);
GT_API GT_STATUS gt_list_append(GtList* gtList, GtValue val);
GT_API GT_STATUS gt_list_get(GtList* gtList, unsigned int index, GtValue* val);
GT_API GT_STATUS gt_list_remove(GtList* gtList, unsigned int index, GtValue* val);
GT_API void gt_list_destroy(GtList** in);

#ifdef __cplusplus
}
#endif
#endif //GTLIB_GTLIST_H
