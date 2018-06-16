//
// Created by 罗然 on 2018/6/16.
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
    GT_STATUS error;
    error = gt_list_get(gtList, 0, &val);
    cr_expect_eq(error, GT_STATUS_OK, "expected OK status bug got %d", error);
    cr_expect(!strcmp("apple", val), "shit happened here!");
    gt_list_remove(gtList, 0, &val); //banana orange pear lemon
    cr_expect(!strcmp("apple", val), "shit happened here!");
    gt_list_remove(gtList, 0, &val); //orange pear lemon
    cr_expect(!strcmp("banana", val), "shit happened here!");
    gt_list_remove(gtList, 2, &val); //orange pear
    cr_expect(!strcmp("lemon", val), "shit happened here!");
    gt_list_remove(gtList, 1, &val); //orange
    cr_expect(!strcmp("pear", val), "shit happened here!");
    gt_list_remove(gtList, 0, &val); //
    cr_expect(!strcmp("orange", val), "shit happened here!");
    size = gt_list_size(gtList);
    cr_expect_eq(size, 0, "expected list size 0 but got %d", size);
}
