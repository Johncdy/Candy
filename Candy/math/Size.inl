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
: width(w)
, height(h)
{
}

inline const Size& Size::operator=(const Size &other)
{
    this->width = other.width;
    this->height = other.height;
    return *this;
}

inline const Size Size::operator+(const candy::Size &other) const
{
    return Size(this->width + other.width, this->height + other.height);
}

inline const Size Size::operator-(const candy::Size &other) const
{
    return Size(this->width - other.width, this->height - other.height);
}

inline const Size Size::operator*(float a) const
{
    return Size(this->width * a, this->height * a);
}

inline const Size Size::operator/(float a) const
{
    return Size(this->width / a, this->height /a);
}

NS_DY_END

#endif
