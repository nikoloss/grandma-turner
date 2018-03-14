//
// Created by rowland on 18-3-14.
//
#include <criterion/criterion.h>
#include <string.h>

Test(sample, test) {
    cr_assert(strlen("")==0, "");
}