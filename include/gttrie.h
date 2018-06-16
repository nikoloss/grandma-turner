//
// Created by rowland on 18-2-8.
//

#ifndef GTLIB_GTTRIE_H
#define GTLIB_GTTRIE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gttypes.h"

typedef struct GtTrie GtTrie;


GT_API GtTrie* gt_trie_create(void);
GT_API long gt_trie_counts(GtTrie* trie);
GT_API GT_STATUS gt_trie_find(GtTrie* trie, char* key, GtValue* value);
GT_API GT_STATUS gt_trie_insert(GtTrie* trie, char* key, GtValue value);
GT_API GT_STATUS gt_trie_remove(GtTrie* trie, char* key);
GT_API void gt_trie_travel(GtTrie* trie, char* key, void(*traveller)(GtValue), unsigned int depth);
GT_API void gt_trie_destroy(GtTrie** trie);

#ifdef __cplusplus
}
#endif
#endif //GTLIB_GTTRIE_H
