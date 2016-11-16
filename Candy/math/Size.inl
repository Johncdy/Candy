//
//  Size.inl
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#ifndef Size_inl
#define Size_inl

#include "math/Size.h"

NS_DY_BEGIN

NS_MATH_BEGIN

inline Size::Size()
: _width(0.0f)
, _height(0.0f)
{
}

inline Size::Size(float w, float h)
: _width(w)
, _height(h)
{
}

inline Size::Size(const Size& copy)
: _width(copy._width)
, _height(copy._height)
{
}

inline void Size::set(float w, float h)
{
    _width = w;
    _height = h;
}

inline const Size& Size::operator=(const Size &other)
{
    _width = other._width;
    _height = other._height;
    return *this;
}

inline const Size Size::operator+(const Size &other) const
{
    return Size(_width + other._width, _height + other._height);
}

inline const Size Size::operator-(const Size &other) const
{
    return Size(_width - other._width, _height - other._height);
}

inline const Size Size::operator*(float a) const
{
    return Size(_width * a, _height * a);
}

inline const Size Size::operator/(float a) const
{
    return Size(_width / a, _height /a);
}

NS_MATH_END

NS_DY_END

#endif
