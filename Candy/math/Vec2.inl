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

inline Vec2::Vec2(float x, float y)
: _x(x)
, _y(y)
{
}

inline const Vec2& Vec2::operator= (const Vec2 &other)
{
    this->_x = other._x;
    this->_y = other._y;
    return *this;
}

inline const Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(this->_x + other._x, this->_y + other._y);
}

inline const Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(this->_x - other._x, this->_y - other._y);
}

inline const Vec2 Vec2::operator*(float a) const
{
    return Vec2(this->_x * a, this->_y * a);
}

inline const Vec2 Vec2::operator/(float a) const
{
    return Vec2(this->_x / a, this->_y / a);
}

NS_DY_END

#endif
