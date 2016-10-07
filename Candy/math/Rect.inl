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
: origin(Vec2(x, y))
, size(Size(width, height))
{
}

inline const Rect& Rect::operator=(const Rect &other)
{
    this->origin = other.origin;
    this->size = other.size;
    return *this;
}

NS_DY_END

#endif /* Rect_inl */
