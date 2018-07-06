// test_gtstack.c
// Created by rowland on 18-3-14.
//

#include <criterion/criterion.h>
#include "../include/gttypes.h"
#include "../include/gtstack.h"

GtStack* gtStack = NULL;

void gtstack_setup(void){
    gtStack = gt_stack_create(3);
}

void gtstack_teardown(void){
    gt_stack_destroy(&gtStack);
}

TestSuite(GtStack, .init=gtstack_setup, .fini=gtstack_teardown);

Test(GtStack, initialized){
    cr_assert(gtStack, "initialized failed");
}

Test(GtStack, counts){
    cr_assert_eq(gt_stack_counts(gtStack), 0, "counts");
    gt_stack_push(gtStack, "托尔斯泰");
    cr_assert_eq(gt_stack_counts(gtStack), 1, "counts");
    gt_stack_push(gtStack, "甘地");
    cr_assert_eq(gt_stack_counts(gtStack), 2, "counts");
    gt_stack_push(gtStack, "泰勒");
    cr_assert_eq(gt_stack_counts(gtStack), 3, "counts");
}

Test(GtStack, overflow){
    cr_assert_eq(gt_stack_counts(gtStack), 0, "counts");
    gt_status err;
    char* vars[] = {"today","is","a"};
    for(int i=0;i<3;i++){
        gt_stack_push(gtStack, vars[i]);
        cr_assert_eq(gt_stack_counts(gtStack), i+1, "unexpected counts %d", i+1);
    }
    err = gt_stack_push(gtStack, "overflow");
    cr_assert_eq(err, GT_STATUS_FULL, "overflow");
}

Test(GtStack, empty){
    cr_assert_eq(gt_stack_counts(gtStack), 0, "counts");
    gt_status err;
    cr_expect_eq(gt_stack_counts(gtStack), 0, "0 is expected");
    GtValue var;
    err = gt_stack_pop(gtStack, &var);
    cr_assert_eq(err, GT_STATUS_EMPTY, "empty");
}

Test(GtStack, store){
    cr_assert_eq(gt_stack_counts(gtStack), 0, "counts");
    gt_status err;
    GtValue var;
    char* vars[] = {"today", "is", "sunny"};
    for(int i=0;i<3;i++){
        gt_stack_push(gtStack, vars[i]);
    }
    err = gt_stack_pop(gtStack, &var);
    cr_expect_eq(err, GT_STATUS_OK, "%d is expected while inserting but got %d", GT_STATUS_OK, err);
    cr_assert(!strcmp((char*)var, "sunny"), "\"sunny\" is expected but got \"%s\"", (char*)var);
    err = gt_stack_clear(gtStack);
    cr_expect_eq(err, GT_STATUS_OK, "%d is expected while inserting but got %d", GT_STATUS_OK, err);
    cr_expect_eq(gt_stack_counts(gtStack), 0, "expect 0 counts after clear");
}

