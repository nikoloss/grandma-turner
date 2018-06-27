//
// Created by rowland on 18-6-26.
//

#ifndef GTLIB_GTHASHMAP_H
#define GTLIB_GTHASHMAP_H
#ifdef __cplusplus
extern "C" {
#endif
#include "gttypes.h"
typedef struct GtHashmap GtHashmap;
GT_API GtHashmap* gt_hashmap_create(unsigned int(*)(char* key));
GT_API unsigned int gt_hashmap_counts(GtHashmap *gtHashmap);
GT_API gt_status gt_hashmap_put(GtHashmap* gtHashmap, char* key, GtValue value);
GT_API gt_status gt_hashmap_get(GtHashmap* gtHashmap, char* key, GtValue *value);
GT_API gt_status gt_hashmap_remove(GtHashmap* gtHashmap, char* key);
GT_API void gt_hashmap_travel(GtHashmap* gtHashmap, GT_BOOL(*traveller)(char* key, GtValue value));
GT_API void gt_hashmap_destroy(GtHashmap** gtHashmap);

#ifdef __cplusplus
}
#endif
#endif //GTLIB_GTHASHMAP_H
