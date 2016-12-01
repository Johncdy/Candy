//
//  Size.cpp
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#include "math/Size.h"
#include "math/MathMacros.h"

#include <cmath>

NS_DY_BEGIN

NS_MATH_BEGIN

const Size Size::ZERO = Size(0, 0);

bool Size::equals(const candy::math::Size &target) const
{
    return (std::abs(target._width - this->_width) < FLT_EPSILON)
        && (std::abs(target._height - this->_height) < FLT_EPSILON);
}

NS_MATH_END

NS_DY_END
