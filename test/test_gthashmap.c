//
// Created by rowland on 18-6-26.
//
#include <criterion/criterion.h>
#include "../include/gttypes.h"
#include "../include/gthashmap.h"

GtHashmap* gtHashmap = NULL;

void gthashmap_setup(void){
    gtHashmap = gt_hashmap_create(NULL);

}

void gthashmap_teardown(void){
    gt_hashmap_destroy(&gtHashmap);
}

TestSuite(GtHashmap, .init=gthashmap_setup, .fini=gthashmap_teardown);

Test(GtHashmap, storge){

    gt_hashmap_put(gtHashmap, "周一", "Mon");
    gt_hashmap_put(gtHashmap, "周二", "Tues");
    gt_hashmap_put(gtHashmap, "周三", "Wed");
    gt_hashmap_put(gtHashmap, "周四", "ThursDay");
    gt_hashmap_put(gtHashmap, "周五", "Fri");

    unsigned int size = gt_hashmap_counts(gtHashmap);
    cr_expect_eq(size, 5, "size 5 is expected but got %u", size);

    gt_status error;
    error = gt_hashmap_remove(gtHashmap, "周五");
    cr_expect_eq(error, GT_STATUS_OK, "remove failed");
    size = gt_hashmap_counts(gtHashmap);
    cr_expect_eq(size, 4, "size 4 is expected but got %u", size);

    GtValue value;
    gt_hashmap_get(gtHashmap, "周四", &value);
    cr_expect(!strcmp("ThursDay", value), "shit happened here!");

    gt_hashmap_put(gtHashmap, "周四", "Thurs");
    gt_hashmap_get(gtHashmap, "周四", &value);
    cr_expect(!strcmp("Thurs", value), "shit happened here!");
}

GT_BOOL hashmap_visit(char* key, GtValue gtValue){
    if(!strcmp(key, "周一")){
        cr_expect(!strcmp(gtValue, "Mon"), "shit happened here!");
    }else if(!strcmp(key, "周二")){
        cr_expect(!strcmp(gtValue, "Tues"), "shit happened here!");
    }else if(!strcmp(key, "周三")){
        cr_expect(!strcmp(gtValue, "Wed"), "shit happened here!");
    }else if(!strcmp(key, "周四")){
        cr_expect(!strcmp(gtValue, "Thurs"), "shit happened here!");
    }else if(!strcmp(key, "周五")){
        cr_expect(!strcmp(gtValue, "Fri"), "shit happened here!");
    }else if(!strcmp(key, "周六")){
        cr_expect(!strcmp(gtValue, "Sat"), "shit happened here!");
    }else if(!strcmp(key, "周日")){
        cr_expect(!strcmp(gtValue, "Sun"), "shit happened here!");
    }
    return GT_TRUE;
}

Test(GtHashmap, visit){
    char* data_set[] = {
            "周一", "Mon",
            "周二", "Tues",
            "周三", "Wed",
            "周四", "Thurs",
            "周五", "Fri",
            "周六", "Sat",
            "周日", "Sun"
    };
    for(int i=0;i<7;i++){
        gt_hashmap_put(gtHashmap, data_set[i*2], data_set[i*2+1]);
    }
    unsigned int size = gt_hashmap_counts(gtHashmap);
    cr_expect_eq(size, 7, "size 7 is expected but got %u", size);
    gt_hashmap_travel(gtHashmap, hashmap_visit);
}