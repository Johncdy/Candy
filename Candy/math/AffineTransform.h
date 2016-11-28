//
//  AffineTransform.h
//  Candy
//
//  Created by Dongyang.Cai on 28/11/2016.
//
//

#ifndef AffineTransform_h
#define AffineTransform_h

#include "include/CandyMacros.h"
#include "math/math.h"
#include "math/Size.h"
#include "math/Rect.h"

NS_DY_BEGIN

NS_MATH_BEGIN

/**@{
 Affine transform
 a   b    0
 c   d    0
 tx  ty   1
 
 Identity
 1   0    0
 0   1    0
 0   0    1
 */

struct AffineTransform {
    float _a, _b, _c, _d;
    float _tx, _ty;
    
    static const AffineTransform IDENTITY;
};

/**Make affine transform.*/
AffineTransform AffineTransformMake(float a, float b, float c, float d, float tx, float ty);

/**Multiply point (x,y,1) by a  affine transform.*/
Vec2 PointApplyAffineTransform(const Vec2& point, const AffineTransform& t);

/**Multiply size (width,height,0) by a  affine transform.*/
Size SizeApplyAffineTransform(const Size& size, const AffineTransform& t);

/**Transform Rect, which will transform the four vertices of the point.*/
Rect RectApplyAffineTransform(const Rect& rect, const AffineTransform& t);

/**@{
 Transform vec2 and Rect by Mat4.
 */
Rect RectApplyTransform(const Rect& rect, const Mat4& t);
Vec2 PointApplyTransform(const Vec2& point, const Mat4& t);

/**
 Translation, equals
 1  0  1
 0  1  0   * affine transform
 tx ty 1
 */
AffineTransform AffineTransformTranslate(const AffineTransform& t, float tx, float ty);

/**
 Rotation, equals
 cos(angle)   sin(angle)   0
 -sin(angle)  cos(angle)   0  * AffineTransform
 0            0            1
 */
AffineTransform AffineTransformRotate(const AffineTransform& t, float angle);

/**
 Scale, equals
 sx   0   0
 0    sy  0  * affineTransform
 0    0   1
 */
AffineTransform AffineTransformScale(const AffineTransform& t, float sx, float sy);

/**Concat two affine transform, t1 * t2*/
AffineTransform AffineTransformConcat(const AffineTransform& t1, const AffineTransform& t2);

/**Compare affine transform.*/
bool AffineTransformEqualToTransform(const AffineTransform& t1, const AffineTransform& t2);

/**Get the inverse of affine transform.*/
AffineTransform AffineTransformInvert(const AffineTransform& t);

/**Concat Mat4, return t1 * t2.*/
Mat4 TransformConcat(const Mat4& t1, const Mat4& t2);

extern const AffineTransform AffineTransformIdentity;

NS_MATH_END

NS_DY_END

#endif /* AffineTransform_h */
