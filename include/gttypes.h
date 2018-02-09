//
// Created by Rowland@Sjet on 2018/1/28.
//

#ifndef GTLIB_GTTYPES_H
#define GTLIB_GTTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#define GT_API            extern
#define GT_OK             (0)
#define GT_ERROR_OUTMEM   (-1)
#define GT_ERROR_FULL     (-2)
#define GT_ERROR_EMPTY    (-3)

#define GTMAXCHAR         (2<<7)

#ifdef __cplusplus
}
#endif

#endif
