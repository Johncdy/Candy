//
//  Vec2.inl
//  Candy
//
//  Created by Dongyang.Cai on 29/09/2016.
//
//

#ifndef Vec2_inl
#define Vec2_inl

#include "math/Vec2.h"

NS_DY_BEGIN

NS_MATH_BEGIN

inline Vec2::Vec2()
: _x(0.0f)
, _y(0.0f)
{
}

inline Vec2::Vec2(float x, float y)
: _x(x)
, _y(y)
{
}

inline Vec2::Vec2(const float* array)
: _x(array[0])
, _y(array[1])
{
}

inline Vec2::Vec2(const Vec2& copy)
: _x(copy._x)
, _y(copy._y)
{
}

inline void Vec2::set(float x, float y)
{
    _x = x;
    _y = y;
}

inline const Vec2& Vec2::operator= (const Vec2 &other)
{
    _x = other._x;
    _y = other._y;
    return *this;
}

inline const Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(_x + other._x, _y + other._y);
}

inline const Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(_x - other._x, _y - other._y);
}

inline const Vec2 Vec2::operator*(float a) const
{
    return Vec2(_x * a, _y * a);
}

inline const Vec2 Vec2::operator/(float a) const
{
    return Vec2(_x / a, _y / a);
}

inline bool Vec2::isZero() const
{
    return _x == 0.0f && _y == 0.0f;
}

inline bool Vec2::isOne() const
{
    return _x == 1.0f && _y == 1.0f;
}

NS_MATH_END

NS_DY_END

#endif
