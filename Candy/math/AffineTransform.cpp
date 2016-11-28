//
//  AffineTransform.cpp
//  Candy
//
//  Created by Dongyang.Cai on 28/11/2016.
//
//

#include "math/AffineTransform.h"

#include <math.h>

using namespace std;

NS_DY_BEGIN

NS_MATH_BEGIN

AffineTransform AffineTransformMakeIdentity()
{
    return AffineTransformMake(1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

extern const AffineTransform AffineTransformIdentity = AffineTransformMakeIdentity();
const AffineTransform AffineTransform::IDENTITY = AffineTransformMakeIdentity();

AffineTransform AffineTransformMake(float a, float b, float c, float d, float tx, float ty)
{
    AffineTransform t;
    t._a = a;
    t._b = b;
    t._c = c;
    t._d = d;
    t._tx = tx;
    t._ty = ty;
    
    return t;
}

Vec2 PointApplyAffineTransform(const Vec2& point, const AffineTransform& t)
{
    Vec2 p;
    p._x = t._a * point._x + (double)t._c * point._y + t._tx;
    p._y = t._b * point._y + (double)t._d * point._y + t._ty;
    
    return p;
}

Size SizeApplyAffineTransform(const Size& size, const AffineTransform& t)
{
    Size s;
    s._width = t._a * s._width + t._c * s._height;
    s._height = t._b * s._width + t._d * s._height;
    
    return s;
}

Rect RectApplyAffineTransform(const Rect& rect, const AffineTransform& t)
{
    float left = rect._origin._x;
    float right = rect._origin._x + rect._size._width;
    float top = rect._origin._y;
    float bottom = rect._origin._y + rect._size._height;
    
    Vec2 topLeft = PointApplyAffineTransform(Vec2(left, top), t);
    Vec2 topRight = PointApplyAffineTransform(Vec2(right, top), t);
    Vec2 bottomLeft = PointApplyAffineTransform(Vec2(left, bottom), t);
    Vec2 bottomRight = PointApplyAffineTransform(Vec2(right, bottom), t);
    
    float minX = min(min(topLeft._x, topRight._x), min(bottomLeft._x, bottomRight._x));
    float maxX = max(max(topLeft._x, topRight._x), max(bottomLeft._x, bottomRight._x));
    float minY = min(min(topLeft._y, topRight._y), min(bottomLeft._y, bottomRight._y));
    float maxY = max(max(topLeft._y, topRight._y), max(bottomLeft._y, bottomRight._y));
    
    return Rect(minX, minY, (maxX - minX), (maxY - minY));
}

Rect RectApplyAffineTransform(const Rect& rect, const Mat4& t)
{
    float left = rect._origin._x;
    float right = rect._origin._x + rect._size._width;
    float top = rect._origin._y;
    float bottom = rect._origin._y + rect._size._height;
    
    Vec3 topLeft(left, top, 0);
    Vec3 topRight(right, top, 0);
    Vec3 bottomLeft(left, bottom, 0);
    Vec3 bottomRight(right, bottom, 0);
    t.transformPoint(&topLeft);
    t.transformPoint(&topRight);
    t.transformPoint(&bottomLeft);
    t.transformPoint(&bottomRight);
    
    float minX = min(min(topLeft._x, topRight._x), min(bottomLeft._x, bottomRight._x));
    float maxX = max(max(topLeft._x, topRight._x), max(bottomLeft._x, bottomRight._x));
    float minY = min(min(topLeft._y, topRight._y), min(bottomLeft._y, bottomRight._y));
    float maxY = max(max(topLeft._y, topRight._y), max(bottomLeft._y, bottomRight._y));
    
    return Rect(minX, minY, (maxX - minX), (maxY - minY));
}

Vec2 PointApplyTransform(const Vec2& point, const Mat4& t)
{
    Vec3 vec(point._x, point._y, 0);
    t.transformPoint(&vec);
    return Vec2(vec._x, vec._y);
}

AffineTransform AffineTransformTranslate(const AffineTransform& t, float tx, float ty)
{
    return AffineTransformMake(t._a, t._b, t._c, t._d, t._tx + t._a * tx + t._c * ty, t._ty + t._b * tx + t._d * ty);
}

AffineTransform AffineTransformRotate(const AffineTransform& t, float angle)
{
    float sine = sinf(angle);
    float cosine = cosf(angle);
    
    return AffineTransformMake(t._a * cosine + t._c * sine,
                               t._b * cosine + t._d * sine,
                               t._c * cosine - t._a * sine,
                               t._d * cosine - t._b * sine,
                               t._tx,
                               t._ty);
}

AffineTransform AffineTransformScale(const AffineTransform& t, float sx, float sy)
{
    return AffineTransformMake(t._a * sx, t._b * sx, t._c * sy, t._d * sy, t._tx, t._ty);
}

AffineTransform AffineTransformConcat(const AffineTransform& t1, const AffineTransform& t2)
{
    return AffineTransformMake(t1._a * t2._a + t1._b * t2._c, t1._a * t2._b + t1._b * t2._d, t1._c * t2._a + t1._d * t2._c, t1._c * t2._b + t1._d * t2._d, t1._tx * t2._a + t1._ty * t2._c + t2._tx, t1._tx * t2._b + t1._ty * t2._d + t2._ty);
}

bool AffineTransformEqualToTransform(const AffineTransform& t1, const AffineTransform& t2)
{
    return (t1._a == t2._a && t1._b == t2._b && t1._c == t2._c && t1._d == t2._d && t1._tx == t2._tx && t1._ty == t2._ty);
}

AffineTransform AffineTransformInvert(const AffineTransform& t)
{
    float determinant = 1 / (t._a * t._d - t._b * t._c);
    
    return AffineTransformMake(determinant * t._d, -determinant * t._b, -determinant * t._c, determinant * t._a, determinant * (t._c * t._ty - t._d * t._tx), determinant * (t._b * t._tx - t._a * t._ty) );
}

Mat4 TransformConcat(const Mat4& t1, const Mat4& t2)
{
    return t1 * t2;
}

NS_MATH_END

NS_DY_END
