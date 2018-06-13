// test_gttrie.c
// Created by rowland on 18-3-14.
//
#include <criterion/criterion.h>
#include <stdio.h>
#include "../include/gttypes.h"
#include "../include/gttrie.h"

GtTrie* gtTrie = NULL;
char* dict[] = {
        "哆", "a deer, a female deer",
        "唻", "a drop of golden sun",
        "咪", "a name I call myself",
        "发", "a long, long way to run",
};

char *to_ascii(const char *inputstring) {
    // allocate the maximum needed to store the ascii represention:
    char *output = malloc(sizeof(char) * (strlen(inputstring) * 4 + 1));
    char *output_end = output;
    if (!output) // allocation failed! omg!
        exit(EXIT_FAILURE);
    *output_end = '\0';
    for (; *inputstring; ++inputstring) {
        output_end += sprintf(output_end, "%u ", *inputstring);
        //assert(output_end == '\0');
    }
    return output;
}

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
    err = gt_trie_find(gtTrie, "咪", &var);
    cr_expect_eq(err, GT_OK, "%d is expected while inserting but got %d", GT_OK, err);
    cr_assert(!strcmp("a long, long way to run", (char*)var),
              "\"a long, long way to run\" is expected but got \"%s\"", (char*)var);
}