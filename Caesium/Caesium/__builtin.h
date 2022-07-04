#ifndef ___builtin_csgh_h_
#define ___builtin_csgh_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __CSG_STACK_SIZE    131072

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

#define _expectSemicolon    (void) 0x00
#define define              typedef struct
#define nil                 ((any) 0)
#define true                1
#define false               0

#define new(type, ...)      (type) { __VA_ARGS__ }
#define print(...)          printf(__VA_ARGS__)
#define panic(...)          do { fprintf(stderr, "Panic: " __VA_ARGS__); exit(-1); } while (0)
#define assert(c)           if (!(c)) panic("Assertion failed: %s\n", #c)
#define suppressUnused(c)   (void) c

any __stack[__CSG_STACK_SIZE];
u32 __stack_ptr = 0;

void push(any value) {
    if (__stack_ptr >= __CSG_STACK_SIZE)
        panic("Stack overflow\n");
    __stack[__stack_ptr++] = value;
}

void pushI8(i8 value) {
    push(&value);
}

void pushI16(i16 value) {
    push(&value);
}

void pushI32(i32 value) {
    push(&value);
}

void pushI64(i64 value) {
    push(&value);
}

void pushU8(u8 value) {
    push(&value);
}

void pushU16(u16 value) {
    push(&value);
}

void pushU32(u32 value) {
    push(&value);
}

void pushU64(u64 value) {
    push(&value);
}

void pushF32(f32 value) {
    push(&value);
}

void pushF64(f64 value) {
    push(&value);
}

void pushString(string value) {
    push((any) value);
}

any pop() {
    if (__stack_ptr <= 0) {
        panic("Stack underflow!\n");
    }
    return __stack[--__stack_ptr];
}

i8 popI8() {
    return *(i8*) pop();
}

i16 popI16() {
    return *(i16*) pop();
}

i32 popI32() {
    return *(i32*) pop();
}

i64 popI64() {
    return *(i64*) pop();
}

u8 popU8() {
    return *(u8*) pop();
}

u16 popU16() {
    return *(u16*) pop();
}

u32 popU32() {
    return *(u32*) pop();
}

u64 popU64() {
    return *(u64*) pop();
}

f32 popF32() {
    return *(f32*) pop();
}

f64 popF64() {
    return *(f64*) pop();
}

string popString() {
    return (string) pop();
}

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
