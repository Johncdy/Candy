//
//  Vec3.cpp
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#include "math/Vec3.h"
#include "math/MathMacros.h"
#include "math/MathUtil.h"

#include <cmath>

NS_DY_BEGIN

NS_MATH_BEGIN

Vec3::Vec3()
: _x(0.0f), _y(0.0f), _z(0.0f)
{
}

Vec3::Vec3(float xx, float yy, float zz)
: _x(xx), _y(yy), _z(zz)
{
}

Vec3::Vec3(const float* array)
{
    set(array);
}

Vec3::Vec3(const Vec3& p1, const Vec3& p2)
{
    set(p1, p2);
}

Vec3::Vec3(const Vec3& copy)
{
    set(copy);
}

Vec3 Vec3::fromColor(unsigned int color)
{
    float components[3];
    int componentIndex = 0;
    for (int i = 2; i >= 0; --i)
    {
        int component = (color >> i*8) & 0x0000ff;
        
        components[componentIndex++] = static_cast<float>(component) / 255.0f;
    }
    
    Vec3 value(components);
    return value;
}

Vec3::~Vec3()
{
}

float Vec3::angle(const Vec3& v1, const Vec3& v2)
{
    float dx = v1._y * v2._z - v1._z * v2._y;
    float dy = v1._z * v2._x - v1._x * v2._z;
    float dz = v1._x * v2._y - v1._y * v2._x;
    
    return std::atan2(std::sqrt(dx * dx + dy * dy + dz * dz) + MATH_FLOAT_SMALL, dot(v1, v2));
}

void Vec3::add(const Vec3& v1, const Vec3& v2, Vec3* dst)
{
    assert(dst);
    
    dst->_x = v1._x + v2._x;
    dst->_y = v1._y + v2._y;
    dst->_z = v1._z + v2._z;
}

void Vec3::clamp(const Vec3& min, const Vec3& max)
{
    assert(!(min._x > max._x || min._y > max._y || min._z > max._z));
    
    // Clamp the x value.
    if (_x < min._x)
        _x = min._x;
    if (_x > max._x)
        _x = max._x;
    
    // Clamp the y value.
    if (_y < min._y)
        _y = min._y;
    if (_y > max._y)
        _y = max._y;
    
    // Clamp the z value.
    if (_z < min._z)
        _z = min._z;
    if (_z > max._z)
        _z = max._z;
}

void Vec3::clamp(const Vec3& v, const Vec3& min, const Vec3& max, Vec3* dst)
{
    assert(dst);
    assert(!(min._x > max._x || min._y > max._y || min._z > max._z));
    
    // Clamp the x value.
    dst->_x = v._x;
    if (dst->_x < min._x)
        dst->_x = min._x;
    if (dst->_x > max._x)
        dst->_x = max._x;
    
    // Clamp the y value.
    dst->_y = v._y;
    if (dst->_y < min._y)
        dst->_y = min._y;
    if (dst->_y > max._y)
        dst->_y = max._y;
    
    // Clamp the z value.
    dst->_z = v._z;
    if (dst->_z < min._z)
        dst->_z = min._z;
    if (dst->_z > max._z)
        dst->_z = max._z;
}

void Vec3::cross(const Vec3& v)
{
    cross(*this, v, this);
}

void Vec3::cross(const Vec3& v1, const Vec3& v2, Vec3* dst)
{
    assert(dst);
    
    // NOTE: This code assumes Vec3 struct members are contiguous floats in memory.
    // We might want to revisit this (and other areas of code that make this assumption)
    // later to guarantee 100% safety/compatibility.
    MathUtil::crossVec3(&v1._x, &v2._x, &dst->_x);
}

float Vec3::distance(const Vec3& v) const
{
    float dx = v._x - _x;
    float dy = v._y - _y;
    float dz = v._z - _z;
    
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

float Vec3::distanceSquared(const Vec3& v) const
{
    float dx = v._x - _x;
    float dy = v._y - _y;
    float dz = v._z - _z;
    
    return (dx * dx + dy * dy + dz * dz);
}

float Vec3::dot(const Vec3& v) const
{
    return (_x * v._x + _y * v._y + _z * v._z);
}

float Vec3::dot(const Vec3& v1, const Vec3& v2)
{
    return (v1._x * v2._x + v1._y * v2._y + v1._z * v2._z);
}

void Vec3::normalize()
{
    float n = _x * _x + _y * _y + _z * _z;
    // Already normalized.
    if (n == 1.0f)
        return;
    
    n = std::sqrt(n);
    // Too close to zero.
    if (n < MATH_TOLERANCE)
        return;
    
    n = 1.0f / n;
    _x *= n;
    _y *= n;
    _z *= n;
}

Vec3 Vec3::getNormalized() const
{
    Vec3 v(*this);
    v.normalize();
    return v;
}

void Vec3::subtract(const Vec3& v1, const Vec3& v2, Vec3* dst)
{
    assert(dst);
    
    dst->_x = v1._x - v2._x;
    dst->_y = v1._y - v2._y;
    dst->_z = v1._z - v2._z;
}

void Vec3::smooth(const Vec3& target, float elapsedTime, float responseTime)
{
    if (elapsedTime > 0)
    {
        *this += (target - *this) * (elapsedTime / (elapsedTime + responseTime));
    }
}

const Vec3 Vec3::ZERO(0.0f, 0.0f, 0.0f);
const Vec3 Vec3::ONE(1.0f, 1.0f, 1.0f);
const Vec3 Vec3::UNIT_X(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::UNIT_Y(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::UNIT_Z(0.0f, 0.0f, 1.0f);

NS_MATH_END

NS_DY_END
