// test_gttrie.c
// Created by rowland on 18-3-14.
//
#include <criterion/criterion.h>
#include "../include/gttypes.h"
#include "../include/gttrie.h"


Test(gttrie, test_create_destroy){
    GtTrie* trie = gt_trie_create();
    cr_assert(trie, "");
    gt_trie_destroy(&trie);
    cr_assert(!trie, "");
}
