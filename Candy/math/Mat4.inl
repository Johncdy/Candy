//
//  Mat4.inl
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#ifndef Mat4_inl
#define Mat4_inl

#include "math/Mat4.h"

NS_DY_BEGIN

NS_MATH_BEGIN

inline Mat4::Mat4()
{
    *this = IDENTITY;
}

inline Mat4::Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
                  float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

inline Mat4::Mat4(const float* mat)
{
    memcpy(_m, mat, sizeof(float) * 16);
}

inline Mat4::Mat4(const Mat4& copy)
{
    memcpy(_m, copy._m, sizeof(float) * 16);
}

inline void Mat4::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    _m[0]  = m11;
    _m[1]  = m21;
    _m[2]  = m31;
    _m[3]  = m41;
    _m[4]  = m12;
    _m[5]  = m22;
    _m[6]  = m32;
    _m[7]  = m42;
    _m[8]  = m13;
    _m[9]  = m23;
    _m[10] = m33;
    _m[11] = m43;
    _m[12] = m14;
    _m[13] = m24;
    _m[14] = m34;
    _m[15] = m44;
}

inline const Mat4& Mat4::operator=(const candy::math::Mat4& other)
{
    _m[0] = other._m[0];
    _m[1] = other._m[1];
    _m[2] = other._m[2];
    _m[3] = other._m[3];
    _m[4] = other._m[4];
    _m[5] = other._m[5];
    _m[6] = other._m[6];
    _m[7] = other._m[7];
    _m[8] = other._m[8];
    _m[9] = other._m[9];
    _m[10] = other._m[10];
    _m[11] = other._m[11];
    _m[12] = other._m[12];
    _m[13] = other._m[13];
    _m[14] = other._m[14];
    _m[15] = other._m[15];
    return *this;
}

inline const Mat4 Mat4::operator+(const candy::math::Mat4 &other)
{
    
}

NS_MATH_END

NS_DY_END


#endif /* Mat4_inl */
