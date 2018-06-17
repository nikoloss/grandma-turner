//
// Created by Rowland@Sjet on 2018/1/28.
//

#ifndef GTLIB_GTTYPES_H
#define GTLIB_GTTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#define GT_API         extern
#define GTMAXCHAR      (2<<7)
#define GT_TRUE        (1)
#define GT_FALSE       (0)

typedef int GT_BOOL;

typedef enum {
    GT_STATUS_OK,
    GT_STATUS_OUTMEN,
    GT_STATUS_FULL,
    GT_STATUS_EMPTY,
    GT_STATUS_NULL,
    GT_STATUS_OVER_INDEX,
} gt_status;


typedef void* GtValue;

#ifdef __cplusplus
}
#endif

#endif
