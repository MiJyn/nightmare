//
//  GLKMathTypes.h
//  GLKit
//
//  Copyright (c) 2011, Apple Inc. All rights reserved.
//

#ifndef __GLK_MATH_TYPES_H
#define __GLK_MATH_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

union _GLKMatrix2
{
    struct
    {
        float m00, m01;
        float m10, m11;
    };
    float m2[2][2];
    float m[4];
};
typedef union _GLKMatrix2 GLKMatrix2;

union _GLKMatrix3
{
    struct
    {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
};
typedef union _GLKMatrix3 GLKMatrix3;

/*
 m30, m31, and m32 correspond to the translation values tx, ty, and tz, respectively.
 m[12], m[13], and m[14] correspond to the translation values tx, ty, and tz, respectively.
 */
union _GLKMatrix4
{
    struct
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
} __attribute__((aligned(16)));
typedef union _GLKMatrix4 GLKMatrix4;

union _GLKVector2
{
    struct { float x, y; };
    struct { float s, t; };
    float v[2];
};
typedef union _GLKVector2 GLKVector2;

union _GLKVector3
{
    struct { float x, y, z; };
    struct { float r, g, b; };
    struct { float s, t, p; };
    float v[3];
};
typedef union _GLKVector3 GLKVector3;

union _GLKVector4
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { float s, t, p, q; };
    float v[4];
} __attribute__((aligned(16)));
typedef union _GLKVector4 GLKVector4;

/*
 x, y, and z represent the imaginary values.
 Vector v represents the imaginary values.
 q[0], q[1], and q[2] represent the imaginary values.
 */
union _GLKQuaternion
{
    struct { GLKVector3 v; float s; };
    struct { float x, y, z, w; };
    float q[4];
} __attribute__((aligned(16)));
typedef union _GLKQuaternion GLKQuaternion;

#ifdef __cplusplus
}
#endif

#endif /* __GLK_MATH_TYPES_H */