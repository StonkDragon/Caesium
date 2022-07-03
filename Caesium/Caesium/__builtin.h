#ifndef ___builtin_csgh_h_
#define ___builtin_csgh_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _expectSemicolon    (void) 0x00
#define define              typedef struct
#define nil                 NULL
#define true                1
#define false               0

typedef char*               string;
typedef void*               any;

typedef long long           i64;
typedef unsigned long long  u64;
typedef int                 i32;
typedef unsigned int        u32;
typedef short               i16;
typedef unsigned short      u16;
typedef char                i8;
typedef unsigned char       u8;
typedef float               f32;
typedef double              f64;
typedef unsigned char       bool;

#define new(type, ...)      (type) { __VA_ARGS__ }
#define print(...)          printf(__VA_ARGS__)
#define panic(...)          do { fprintf(stderr, __VA_ARGS__); exit(-1); } while (0)
#define assert(c)           if (!(c)) panic("Assertion failed: %s\n", #c)
#define suppressUnused(c)   (void) c

define {
    f32 x, y;
} vec2;

define {
    f32 x, y, z;
} vec3;

define {
    f32 x, y, z, w;
} vec4;

define {
    i32 x, y;
} int2;

define {
    i32 x, y, z;
} int3;

define {
    i32 x, y, z, w;
} int4;

#ifdef __cplusplus
}
#endif

#endif
