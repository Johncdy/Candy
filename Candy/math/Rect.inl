//
//  Rect.inl
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#ifndef Rect_inl
#define Rect_inl

#include "math/Rect.h"

NS_DY_BEGIN

NS_MATH_BEGIN

inline Rect::Rect()
: _origin(Vec2())
, _size(Size())
{
}

inline Rect::Rect(float x, float y, float width, float height)
: _origin(Vec2(x, y))
, _size(Size(width, height))
{
}

inline Rect::Rect(const Rect& copy)
: _origin(copy._origin)
, _size(copy._size)
{
}

inline const Rect& Rect::operator=(const Rect &other)
{
    _origin = other._origin;
    _size = other._size;
    return *this;
}

inline void Rect::set(float x, float y, float width, float height)
{
    _origin._x = x;
    _origin._y = y;
    _size._width = width;
    _size._height = height;
}

NS_MATH_END

NS_DY_END

#endif /* Rect_inl */
