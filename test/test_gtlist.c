//
// Created by Rowland on 2018/6/16.
//
#include <criterion/criterion.h>
#include "../include/gttypes.h"
#include "../include/gtlist.h"

GtList* gtList = NULL;

void gtlist_setup(void){
    gtList = gt_list_create();
}

void gtlist_teardown(void){
    gt_list_destroy(&gtList);
}

TestSuite(GtList, .init=gtlist_setup, .fini=gtlist_teardown);

Test(GtList, counts){
    cr_assert(gtList!=NULL, "list initialized failed!");
    unsigned int size = gt_list_size(gtList);
    cr_expect_eq(size, 0, "expected list size 0");
    gt_list_append(gtList, "apple");
    size = gt_list_size(gtList);
    cr_expect_eq(size, 1, "expected list size 1");
}

Test(GtList, storge){
    unsigned int size = gt_list_size(gtList);
    cr_expect_eq(size, 0, "expected list size 0");
    gt_list_append(gtList, "apple");
    gt_list_append(gtList, "banana");
    gt_list_append(gtList, "orange");
    gt_list_append(gtList, "pear");
    gt_list_append(gtList, "lemon");

    GtValue val;
    gt_status error;
    error = gt_list_get(gtList, 0, &val);
    cr_expect_eq(error, GT_STATUS_OK, "expected OK status bug got %d", error);
    cr_expect(!strcmp("apple", val), "shit happened here!");
    gt_list_get(gtList, 2, &val);
    cr_expect(!strcmp("orange", val), "shit happened here!");
    size = gt_list_size(gtList);
    cr_expect_eq(size, 5, "expected list size 0 but got %d", size);
    gt_list_insert(gtList, 0, "cherry");
    // cherry, apple, banana, orange, pear, lemon
    gt_list_insert(gtList, 4, "mango");
    // cherry, apple, banana, orange, mango, pear, lemon
    char* data_set[] = {
            "cherry", "apple", "banana", "orange", "mango", "pear", "lemon"
    };
    for(int i=0;i<7;i++){
        gt_list_get(gtList, i, &val);
//        cr_log(CR_LOG_WARNING, "%s", (char*)val);
        cr_expect(!strcmp(data_set[i], val), "shit happened here!");
    }
}

Test(GtList, visit){
    char* data_set[] = {
            "apple",
            "banana",
            "orange",
            "pear",
            "lemon"
    };
    for(int i=0;i<5;i++){
        gt_list_append(gtList, data_set[i]);
    }
    unsigned int size = gt_list_size(gtList);
    cr_expect_eq(size, 5, "expected list size 5 but got %d", size);

    GtValue val;
    GtListIter *gtListIter = gt_list_iterator_create(gtList);
    cr_assert(gtListIter, "list iterator initialized failed");
    for(int i=0;gt_list_iterator_has_next(gtListIter);i++){
        gt_list_iterator_next(gtListIter, &val);
        cr_assert(!strcmp(data_set[i], val), "not equal at %d rounds", i+1);
        if(i==3){
            gt_list_iterator_remove(gtListIter); //删除pear
        }
    }
    gt_list_get(gtList, 3, &val);
    cr_assert(!strcmp("lemon", val), "list iterator failed to remove 3rd item");
    size = gt_list_size(gtList);
    cr_expect_eq(size, 4, "expected list size 4 but got %d", size);
    gt_list_iterator_val(gtListIter, &val);
    cr_expect(!strcmp("lemon", val), "shit happened here!");
    gt_list_iterator_destroy(&gtListIter);
}
