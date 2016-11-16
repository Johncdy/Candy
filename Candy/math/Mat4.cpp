//
//  Mat4.cpp
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#include "math/Mat4.h"

NS_DY_BEGIN

NS_MATH_BEGIN

const Mat4 Mat4::ZERO = Mat4(
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0);

const Mat4 Mat4::IDENTITY = Mat4(
                             1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f);

void Mat4::add(const candy::math::Mat4 &mat)
{
    
}

NS_MATH_END

NS_DY_END
