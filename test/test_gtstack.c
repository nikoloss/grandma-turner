//
// Created by rowland on 18-3-14.
//

#include <criterion/criterion.h>
#include "../include/gttypes.h"
#include "../include/gtstack.h"

Test(gtstack, test){
    GtStack* stack = gt_stack_create(10);
    cr_assert(stack!=NULL, "oops!!!");
    gt_stack_destroy(&stack);
    cr_assert(stack==NULL, "");
}