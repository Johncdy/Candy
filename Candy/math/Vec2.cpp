//
//  Vec2.cpp
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#include "math/Vec2.h"
#include "math/MathMacros.h"

#include <cmath>

NS_DY_BEGIN

NS_MATH_BEGIN

const Vec2 Vec2::ZERO(0.0f, 0.0f);
const Vec2 Vec2::ONE(1.0f, 1.0f);
const Vec2 Vec2::UNIT_X(1.0f, 0.0f);
const Vec2 Vec2::UNIT_Y(0.0f, 1.0f);
const Vec2 Vec2::ANCHOR_MIDDLE(0.5f, 0.5f);
const Vec2 Vec2::ANCHOR_BOTTOM_LEFT(0.0f, 0.0f);
const Vec2 Vec2::ANCHOR_TOP_LEFT(0.0f, 1.0f);
const Vec2 Vec2::ANCHOR_BOTTOM_RIGHT(1.0f, 0.0f);
const Vec2 Vec2::ANCHOR_TOP_RIGHT(1.0f, 1.0f);
const Vec2 Vec2::ANCHOR_MIDDLE_RIGHT(1.0f, 0.5f);
const Vec2 Vec2::ANCHOR_MIDDLE_LEFT(0.0f, 0.5f);
const Vec2 Vec2::ANCHOR_MIDDLE_TOP(0.5f, 1.0f);
const Vec2 Vec2::ANCHOR_MIDDLE_BOTTOM(0.5f, 0.0f);

bool Vec2::equals(const candy::math::Vec2 &target) const
{
    return (std::abs(target._x - _x) < FLT_EPSILON)
        && (std::abs(target._y - _y) < FLT_EPSILON);
}

NS_MATH_END

NS_DY_END
