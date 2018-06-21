//
// Created by Rowland on 2018/6/16.
//

#ifndef GTLIB_GTLIST_H
#define GTLIB_GTLIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"

typedef struct GtList GtList;
typedef struct GtListIter GtListIter;

GT_API GtList* gt_list_create(void);
GT_API unsigned int gt_list_size(GtList* gtList);
GT_API gt_status gt_list_insert(GtList* gtList, int index, GtValue val);
GT_API gt_status gt_list_append(GtList* gtList, GtValue val);
GT_API gt_status gt_list_get(GtList* gtList, int index, GtValue* val);
GT_API void gt_list_destroy(GtList** gtList);

GT_API GtListIter* gt_list_iterator_create(GtList *gtList);
GT_API GT_BOOL gt_list_iterator_has_next(GtListIter* iter);
GT_API gt_status gt_list_iterator_next(GtListIter* iter, GtValue* val);
GT_API gt_status gt_list_iterator_val(GtListIter* iter, GtValue* val);
GT_API gt_status gt_list_iterator_remove(GtListIter* iter);
GT_API void gt_list_iterator_destroy(GtListIter** iter);

#ifdef __cplusplus
}
#endif
#endif //GTLIB_GTLIST_H
