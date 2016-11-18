//
//  Quaternion.inl
//  Candy
//
//  Created by Dongyang.Cai on 18/11/2016.
//
//

#ifndef Quaternion_inl
#define Quaternion_inl

#include "math/Quaternion.h"

NS_DY_BEGIN

NS_MATH_BEGIN

inline const Quaternion Quaternion::operator*(const Quaternion& q) const
{
    Quaternion result(*this);
    result.multiply(q);
    return result;
}

inline Quaternion& Quaternion::operator*=(const Quaternion& q)
{
    multiply(q);
    return *this;
}

inline Vec3 Quaternion::operator*(const Vec3& v) const
{
    Vec3 uv, uuv;
    Vec3 qvec(x, y, z);
    Vec3::cross(qvec, v, &uv);
    Vec3::cross(qvec, uv, &uuv);
    
    uv *= (2.0f * w);
    uuv *= 2.0f;
    
    return v + uv + uuv;
}

NS_MATH_END

NS_DY_END

#endif /* Quaternion_inl */
