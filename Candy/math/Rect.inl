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

inline Rect::Rect(float x, float y, float width, float height)
: _origin(Vec2(x, y))
, _size(Size(width, height))
{
}

inline const Rect& Rect::operator=(const Rect &other)
{
    this->_origin = other._origin;
    this->_size = other._size;
    return *this;
}

inline void Rect::set(float x, float y, float width, float height)
{
    this->_origin._x = x;
    this->_origin._y = y;
    this->_size._width = width;
    this->_size._height = height;
}

NS_DY_END

#endif /* Rect_inl */
