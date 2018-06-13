// test_gttrie.c
// Created by rowland on 18-3-14.
//
#include <criterion/criterion.h>
#include "../include/gttypes.h"
#include "../include/gttrie.h"

GtTrie* gtTrie = NULL;
char* dict[] = {
        "Doe", "a deer, a female deer",
        "Ray", "a drop of golden sun",
        "Me", "a name I call myself",
        "Far", "a long, long way to run",
};
void gttrie_setup(void){
    gtTrie = gt_trie_create();
}

void gttrie_teardown(void){
    gt_trie_destroy(&gtTrie);
}

TestSuite(GtTrie, .init=gttrie_setup, .fini=gttrie_teardown);

Test(GtTrie, insert_search){
    cr_expect_eq(gt_trie_counts(gtTrie), 0, "0 is expected");
    int err;
    for(int i=0;i<8;i=i+2){
        err = gt_trie_insert(gtTrie, dict[i], dict[i+1]);
        cr_expect_eq(err, GT_OK, "%d is expected while inserting but got %d", GT_OK, err);
    }

    GtValue var;
    err = gt_trie_find(gtTrie, "Far", &var);
    cr_expect_eq(err, GT_OK, "%d is expected while inserting but got %d", GT_OK, err);
    cr_assert(!strcmp("a long, long way to run", (char*)var),
              "\"a long, long way to run\" is expected but got \"%s\"", (char*)var);
}