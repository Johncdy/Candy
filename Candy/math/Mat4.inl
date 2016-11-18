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

inline const Mat4 Mat4::operator+(const Mat4& mat) const
{
    Mat4 result(*this);
    result.add(mat);
    return result;
}

inline Mat4& Mat4::operator+=(const Mat4& mat)
{
    add(mat);
    return *this;
}

inline const Mat4 Mat4::operator-(const Mat4& mat) const
{
    Mat4 result(*this);
    result.subtract(mat);
    return result;
}

inline Mat4& Mat4::operator-=(const Mat4& mat)
{
    subtract(mat);
    return *this;
}

inline const Mat4 Mat4::operator-() const
{
    Mat4 mat(*this);
    mat.negate();
    return mat;
}

inline const Mat4 Mat4::operator*(const Mat4& mat) const
{
    Mat4 result(*this);
    result.multiply(mat);
    return result;
}

inline Mat4& Mat4::operator*=(const Mat4& mat)
{
    multiply(mat);
    return *this;
}

inline Vec3& operator*=(Vec3& v, const Mat4& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vec3 operator*(const Mat4& m, const Vec3& v)
{
    Vec3 x;
    m.transformVector(v, &x);
    return x;
}

inline Vec4& operator*=(Vec4& v, const Mat4& m)
{
    m.transformVector(&v);
    return v;
}

inline const Vec4 operator*(const Mat4& m, const Vec4& v)
{
    Vec4 x;
    m.transformVector(v, &x);
    return x;
}

NS_MATH_END

NS_DY_END


#endif /* Mat4_inl */
