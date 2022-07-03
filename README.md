# The Caesium Programming Language

Examples can be found in the [examples](examples/) directory.

## Keywords

| Keyword | Description |
| ------- | ----------- |
| return | Return from a function |
| const | Declare a constant |
| define | Define a complex type |
| typedef | Declare a type alias |
| fn | Declare a function |
| void | Declare a void type |
| i32 | Declare an integer |
| i64 | Declare a 64-bit integer |
| i16 | Declare a 16-bit integer |
| i8 | Declare a 8-bit integer |
| u32 | Declare an unsigned integer |
| u64 | Declare a 64-bit unsigned integer |
| u16 | Declare a 16-bit unsigned integer |
| u8 | Declare a 8-bit unsigned integer |
| f64 | Declare a 64-bit floating point number |
| f32 | Declare a 32-bit floating point number |
| bool | Declare a boolean |
| int2 | Declare a 2-Dimensional integer vector |
| int3 | Declare a 3-Dimensional integer vector |
| int4 | Declare a 4-Dimensional integer vector |
| vec2 | Declare a 2-Dimensional floating point vector |
| vec3 | Declare a 3-Dimensional floating point vector |
| vec4 | Declare a 4-Dimensional floating point vector |
| string | Declare a string |
| struct | Declare a struct |
| true | Boolean literal true |
| false | Boolean literal false |
| nil | Null literal |
| if | Conditional if statement |
| else | Conditional else statement |
| while | while-Loop statement |
| do | do-while-Loop statement |
| for | for-Loop statement |
| any | Declare a type that can be any type |

## Preprocessor Directives

The compiler translates these into C-like preprocessor directives.

| Directive | Description |
| --------- | ----------- |
| @Include | Include a (C) file (`#include` in C) |
| @Ifdef | Conditional if statement (`#ifdef` in C) |
| @Define | Define a constant (`#define` in C) |
| @Endif | Conditional else statement (`#endif` in C) |
| @Ifndef | Conditional if statement (`#ifndef` in C) |
| @If | Conditional if statement (`#if` in C) |
| @Undef | Undefine a constant (`#undef` in C) |
| @Else | Conditional else statement (`#else` in C) |
| @Error | Error message (`#error` in C) |
| @Require | Require a Caesium file (no C equivalent) |

## How to use

- Copy the [Caesium](Caesium/) directory to your home directory.
- Open a terminal and navigate to your project directory.
- Run `csgc <your file>` to compile your file.
- Profit!
