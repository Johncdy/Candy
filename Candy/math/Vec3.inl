//
//  Vec3.inl
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#ifndef Vec3_inl
#define Vec3_inl

#include "math/Vec3.h"

NS_DY_BEGIN

NS_MATH_BEGIN

inline Vec3::Vec3()
: _x(0.0f)
, _y(0.0f)
, _z(0.0f)
{
}

inline Vec3::Vec3(float x, float y, float z)
: _x(x)
, _y(y)
, _z(z)
{
}

inline Vec3::Vec3(const float* array)
: _x(array[0])
, _y(array[1])
, _z(array[2])
{
}

inline Vec3::Vec3(const Vec3& copy)
: _x(copy._x)
, _y(copy._y)
, _z(copy._z)
{
}

inline void Vec3::set(float x, float y, float z)
{
    _x = x;
    _y = y;
    _z = z;
}

inline const Vec3& Vec3::operator=(const candy::math::Vec3 &other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

inline const Vec3 Vec3::operator+(const candy::math::Vec3 &other) const
{
    return Vec3(_x + other._x, _y + other._y, _z + other._z);
}

inline const Vec3 Vec3::operator-(const candy::math::Vec3 &other) const
{
    return Vec3(_x - other._x, _y - other._y, _z - other._z);
}

inline const Vec3 Vec3::operator*(float a) const
{
    return Vec3(_x * a, _y * a, _z * a);
}

inline const Vec3 Vec3::operator/(float a) const
{
    return Vec3(_x / a, _y / a, _z / a);
}

NS_MATH_END

NS_DY_END

#endif /* Vec3_inl */
