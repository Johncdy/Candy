//
//  Quaternion.cpp
//  Candy
//
//  Created by Dongyang.Cai on 18/11/2016.
//
//

#include "math/Quaternion.h"
#include "math/Mat4.h"

#include "assert.h"
#include <cmath>
#include <string.h>

NS_DY_BEGIN

NS_MATH_BEGIN

const Quaternion Quaternion::ZERO(0.0f, 0.0f, 0.0f, 0.0f);

Quaternion::Quaternion()
: _x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f)
{
}

Quaternion::Quaternion(float xx, float yy, float zz, float ww)
: _x(xx), _y(yy), _z(zz), _w(ww)
{
}

Quaternion::Quaternion(float* array)
{
    set(array);
}

Quaternion::Quaternion(const Mat4& m)
{
    set(m);
}

Quaternion::Quaternion(const Vec3& axis, float angle)
{
    set(axis, angle);
}

Quaternion::Quaternion(const Quaternion& copy)
{
    set(copy);
}

Quaternion::~Quaternion()
{
}

const Quaternion& Quaternion::identity()
{
    static Quaternion value(0.0f, 0.0f, 0.0f, 1.0f);
    return value;
}

const Quaternion& Quaternion::zero()
{
    static Quaternion value(0.0f, 0.0f, 0.0f, 0.0f);
    return value;
}

bool Quaternion::isIdentity() const
{
    return _x == 0.0f && _y == 0.0f && _z == 0.0f && _w == 1.0f;
}

bool Quaternion::isZero() const
{
    return _x == 0.0f && _y == 0.0f && _z == 0.0f && _w == 0.0f;
}

void Quaternion::createFromRotationMatrix(const Mat4& m, Quaternion* dst)
{
    m.getRotation(dst);
}

void Quaternion::createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst)
{
    assert(dst);
    
    float halfAngle = angle * 0.5f;
    float sinHalfAngle = sinf(halfAngle);
    
    Vec3 normal(axis);
    normal.normalize();
    dst->_x = normal._x * sinHalfAngle;
    dst->_y = normal._y * sinHalfAngle;
    dst->_z = normal._z * sinHalfAngle;
    dst->_w = cosf(halfAngle);
}

void Quaternion::conjugate()
{
    _x = -_x;
    _y = -_y;
    _z = -_z;
    //w =  w;
}

Quaternion Quaternion::getConjugated() const
{
    Quaternion q(*this);
    q.conjugate();
    return q;
}

bool Quaternion::inverse()
{
    float n = _x * _x + _y * _y + _z * _z + _w * _w;
    if (n == 1.0f)
    {
        _x = -_x;
        _y = -_y;
        _z = -_z;
        //w = w;
        
        return true;
    }
    
    // Too close to zero.
    if (n < 0.000001f)
        return false;
    
    n = 1.0f / n;
    _x = -_x * n;
    _y = -_y * n;
    _z = -_z * n;
    _w = _w * n;
    
    return true;
}

Quaternion Quaternion::getInversed() const
{
    Quaternion q(*this);
    q.inverse();
    return q;
}

void Quaternion::multiply(const Quaternion& q)
{
    multiply(*this, q, this);
}

void Quaternion::multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst)
{
    assert(dst);
    
    float _x = q1._w * q2._x + q1._x * q2._w + q1._y * q2._z - q1._z * q2._y;
    float _y = q1._w * q2._y - q1._x * q2._z + q1._y * q2._w + q1._z * q2._x;
    float _z = q1._w * q2._z + q1._x * q2._y - q1._y * q2._x + q1._z * q2._w;
    float _w = q1._w * q2._w - q1._x * q2._x - q1._y * q2._y - q1._z * q2._z;
    
    dst->_x = _x;
    dst->_y = _y;
    dst->_z = _z;
    dst->_w = _w;
}

void Quaternion::normalize()
{
    float n = _x * _x + _y * _y + _z * _z + _w * _w;
    
    // Already normalized.
    if (n == 1.0f)
        return;
    
    n = std::sqrt(n);
    // Too close to zero.
    if (n < 0.000001f)
        return;
    
    n = 1.0f / n;
    _x *= n;
    _y *= n;
    _z *= n;
    _w *= n;
}

Quaternion Quaternion::getNormalized() const
{
    Quaternion q(*this);
    q.normalize();
    return q;
}

void Quaternion::set(float xx, float yy, float zz, float ww)
{
    _x = xx;
    _y = yy;
    _z = zz;
    _w = ww;
}

void Quaternion::set(float* array)
{
    assert(array);
    
    _x = array[0];
    _y = array[1];
    _z = array[2];
    _w = array[3];
}

void Quaternion::set(const Mat4& m)
{
    Quaternion::createFromRotationMatrix(m, this);
}

void Quaternion::set(const Vec3& axis, float angle)
{
    Quaternion::createFromAxisAngle(axis, angle, this);
}

void Quaternion::set(const Quaternion& q)
{
    _x = q._x;
    _y = q._y;
    _z = q._z;
    _w = q._w;
}

void Quaternion::setIdentity()
{
    _x = 0.0f;
    _y = 0.0f;
    _z = 0.0f;
    _w = 1.0f;
}

float Quaternion::toAxisAngle(Vec3* axis) const
{
    assert(axis);
    
    Quaternion q(_x, _y, _z, _w);
    q.normalize();
    axis->_x = q._x;
    axis->_y = q._y;
    axis->_z = q._z;
    axis->normalize();
    
    return (2.0f * std::acos(q._w));
}

void Quaternion::lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst)
{
    assert(dst);
    assert(!(t < 0.0f || t > 1.0f));
    
    if (t == 0.0f)
    {
        memcpy(dst, &q1, sizeof(float) * 4);
        return;
    }
    else if (t == 1.0f)
    {
        memcpy(dst, &q2, sizeof(float) * 4);
        return;
    }
    
    float t1 = 1.0f - t;
    
    dst->_x = t1 * q1._x + t * q2._x;
    dst->_y = t1 * q1._y + t * q2._y;
    dst->_z = t1 * q1._z + t * q2._z;
    dst->_w = t1 * q1._w + t * q2._w;
}

void Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst)
{
    assert(dst);
    slerp(q1._x, q1._y, q1._z, q1._w, q2._x, q2._y, q2._z, q2._w, t, &dst->_x, &dst->_y, &dst->_z, &dst->_w);
}

void Quaternion::squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst)
{
    assert(!(t < 0.0f || t > 1.0f));
    
    Quaternion dstQ(0.0f, 0.0f, 0.0f, 1.0f);
    Quaternion dstS(0.0f, 0.0f, 0.0f, 1.0f);
    
    slerpForSquad(q1, q2, t, &dstQ);
    slerpForSquad(s1, s2, t, &dstS);
    slerpForSquad(dstQ, dstS, 2.0f * t * (1.0f - t), dst);
}

void Quaternion::slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw)
{
    // Fast slerp implementation by kwhatmough:
    // It contains no division operations, no trig, no inverse trig
    // and no sqrt. Not only does this code tolerate small constraint
    // errors in the input quaternions, it actually corrects for them.
    assert(dstx && dsty && dstz && dstw);
    assert(!(t < 0.0f || t > 1.0f));
    
    if (t == 0.0f)
    {
        *dstx = q1x;
        *dsty = q1y;
        *dstz = q1z;
        *dstw = q1w;
        return;
    }
    else if (t == 1.0f)
    {
        *dstx = q2x;
        *dsty = q2y;
        *dstz = q2z;
        *dstw = q2w;
        return;
    }
    
    if (q1x == q2x && q1y == q2y && q1z == q2z && q1w == q2w)
    {
        *dstx = q1x;
        *dsty = q1y;
        *dstz = q1z;
        *dstw = q1w;
        return;
    }
    
    float halfY, alpha, beta;
    float u, f1, f2a, f2b;
    float ratio1, ratio2;
    float halfSecHalfTheta, versHalfTheta;
    float sqNotU, sqU;
    
    float cosTheta = q1w * q2w + q1x * q2x + q1y * q2y + q1z * q2z;
    
    // As usual in all slerp implementations, we fold theta.
    alpha = cosTheta >= 0 ? 1.0f : -1.0f;
    halfY = 1.0f + alpha * cosTheta;
    
    // Here we bisect the interval, so we need to fold t as well.
    f2b = t - 0.5f;
    u = f2b >= 0 ? f2b : -f2b;
    f2a = u - f2b;
    f2b += u;
    u += u;
    f1 = 1.0f - u;
    
    // One iteration of Newton to get 1-cos(theta / 2) to good accuracy.
    halfSecHalfTheta = 1.09f - (0.476537f - 0.0903321f * halfY) * halfY;
    halfSecHalfTheta *= 1.5f - halfY * halfSecHalfTheta * halfSecHalfTheta;
    versHalfTheta = 1.0f - halfY * halfSecHalfTheta;
    
    // Evaluate series expansions of the coefficients.
    sqNotU = f1 * f1;
    ratio2 = 0.0000440917108f * versHalfTheta;
    ratio1 = -0.00158730159f + (sqNotU - 16.0f) * ratio2;
    ratio1 = 0.0333333333f + ratio1 * (sqNotU - 9.0f) * versHalfTheta;
    ratio1 = -0.333333333f + ratio1 * (sqNotU - 4.0f) * versHalfTheta;
    ratio1 = 1.0f + ratio1 * (sqNotU - 1.0f) * versHalfTheta;
    
    sqU = u * u;
    ratio2 = -0.00158730159f + (sqU - 16.0f) * ratio2;
    ratio2 = 0.0333333333f + ratio2 * (sqU - 9.0f) * versHalfTheta;
    ratio2 = -0.333333333f + ratio2 * (sqU - 4.0f) * versHalfTheta;
    ratio2 = 1.0f + ratio2 * (sqU - 1.0f) * versHalfTheta;
    
    // Perform the bisection and resolve the folding done earlier.
    f1 *= ratio1 * halfSecHalfTheta;
    f2a *= ratio2;
    f2b *= ratio2;
    alpha *= f1 + f2a;
    beta = f1 + f2b;
    
    // Apply final coefficients to a and b as usual.
    float w = alpha * q1w + beta * q2w;
    float x = alpha * q1x + beta * q2x;
    float y = alpha * q1y + beta * q2y;
    float z = alpha * q1z + beta * q2z;
    
    // This final adjustment to the quaternion's length corrects for
    // any small constraint error in the inputs q1 and q2 But as you
    // can see, it comes at the cost of 9 additional multiplication
    // operations. If this error-correcting feature is not required,
    // the following code may be removed.
    f1 = 1.5f - 0.5f * (w * w + x * x + y * y + z * z);
    *dstw = w * f1;
    *dstx = x * f1;
    *dsty = y * f1;
    *dstz = z * f1;
}

void Quaternion::slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst)
{
    assert(dst);
    
    // cos(omega) = q1 * q2;
    // slerp(q1, q2, t) = (q1*sin((1-t)*omega) + q2*sin(t*omega))/sin(omega);
    // q1 = +- q2, slerp(q1,q2,t) = q1.
    // This is a straight-forward implementation of the formula of slerp. It does not do any sign switching.
    float c = q1._x * q2._x + q1._y * q2._y + q1._z * q2._z + q1._w * q2._w;
    
    if (std::abs(c) >= 1.0f)
    {
        dst->_x = q1._x;
        dst->_y = q1._y;
        dst->_z = q1._z;
        dst->_w = q1._w;
        return;
    }
    
    float omega = std::acos(c);
    float s = std::sqrt(1.0f - c * c);
    if (std::abs(s) <= 0.00001f)
    {
        dst->_x = q1._x;
        dst->_y = q1._y;
        dst->_z = q1._z;
        dst->_w = q1._w;
        return;
    }
    
    float r1 = std::sin((1 - t) * omega) / s;
    float r2 = std::sin(t * omega) / s;
    dst->_x = (q1._x * r1 + q2._x * r2);
    dst->_y = (q1._y * r1 + q2._y * r2);
    dst->_z = (q1._z * r1 + q2._z * r2);
    dst->_w = (q1._w * r1 + q2._w * r2);
}

NS_MATH_END

NS_DY_END
