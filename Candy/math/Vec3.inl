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

#include <cmath>

NS_DY_BEGIN

NS_MATH_BEGIN

inline bool Vec3::isZero() const
{
    return _x == 0.0f && _y == 0.0f && _z == 0.0f;
}

inline bool Vec3::isOne() const
{
    return _x == 1.0f && _y == 1.0f && _z == 1.0f;
}

inline void Vec3::add(const Vec3& v)
{
    _x += v._x;
    _y += v._y;
    _z += v._z;
}

inline void Vec3::add(float xx, float yy, float zz)
{
    _x += xx;
    _y += yy;
    _z += zz;
}

inline float Vec3::length() const
{
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

inline float Vec3::lengthSquared() const
{
    return (_x * _x + _y * _y + _z * _z);
}

inline void Vec3::negate()
{
    _x = -_x;
    _y = -_y;
    _z = -_z;
}

inline void Vec3::scale(float scalar)
{
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
}

inline Vec3 Vec3::lerp(const Vec3 &target, float alpha) const
{
    return *this * (1.f - alpha) + target * alpha;
}

inline void Vec3::set(float xx, float yy, float zz)
{
    _x = xx;
    _y = yy;
    _z = zz;
}

inline void Vec3::set(const float* array)
{
    assert(array);
    
    _x = array[0];
    _y = array[1];
    _z = array[2];
}

inline void Vec3::set(const Vec3& v)
{
    _x = v._x;
    _y = v._y;
    _z = v._z;
}

inline void Vec3::set(const Vec3& p1, const Vec3& p2)
{
    _x = p2._x - p1._x;
    _y = p2._y - p1._y;
    _z = p2._z - p1._z;
}

inline void Vec3::setZero()
{
    _x = _y = _z = 0.0f;
}

inline void Vec3::subtract(const Vec3& v)
{
    _x -= v._x;
    _y -= v._y;
    _z -= v._z;
}

inline const Vec3 Vec3::operator+(const Vec3& v) const
{
    Vec3 result(*this);
    result.add(v);
    return result;
}

inline Vec3& Vec3::operator+=(const Vec3& v)
{
    add(v);
    return *this;
}

inline const Vec3 Vec3::operator-(const Vec3& v) const
{
    Vec3 result(*this);
    result.subtract(v);
    return result;
}

inline Vec3& Vec3::operator-=(const Vec3& v)
{
    subtract(v);
    return *this;
}

inline const Vec3 Vec3::operator-() const
{
    Vec3 result(*this);
    result.negate();
    return result;
}

inline const Vec3 Vec3::operator*(float s) const
{
    Vec3 result(*this);
    result.scale(s);
    return result;
}

inline Vec3& Vec3::operator*=(float s)
{
    scale(s);
    return *this;
}

inline const Vec3 Vec3::operator/(const float s) const
{
    return Vec3(_x / s, _y / s, _z / s);
}

inline bool Vec3::operator==(const Vec3& v) const
{
    return _x==v._x && _y==v._y && _z==v._z;
}

inline bool Vec3::operator!=(const Vec3& v) const
{
    return _x!=v._x || _y!=v._y || _z!=v._z;
}

inline const Vec3 operator*(float x, const Vec3& v)
{
    Vec3 result(v);
    result.scale(x);
    return result;
}

NS_MATH_END

NS_DY_END

#endif /* Vec3_inl */
