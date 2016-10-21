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

inline Size::Size(float w, float h)
: _width(w)
, _height(h)
{
}

inline void Size::set(float w, float h)
{
    this->_width = w;
    this->_height = h;
}

inline const Size& Size::operator=(const Size &other)
{
    this->_width = other._width;
    this->_height = other._height;
    return *this;
}

inline const Size Size::operator+(const candy::Size &other) const
{
    return Size(this->_width + other._width, this->_height + other._height);
}

inline const Size Size::operator-(const candy::Size &other) const
{
    return Size(this->_width - other._width, this->_height - other._height);
}

inline const Size Size::operator*(float a) const
{
    return Size(this->_width * a, this->_height * a);
}

inline const Size Size::operator/(float a) const
{
    return Size(this->_width / a, this->_height /a);
}

NS_DY_END

#endif
