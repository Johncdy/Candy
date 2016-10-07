//
//  Rect.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef Rect_h
#define Rect_h

#include "math/Size.h"
#include "math/Vec2.h"

NS_DY_BEGIN

class Rect {
public:
    
    /**
     Constructor a rect.

     @param x      The x coordinate.
     @param y      The y coordinate.
     @param width  The width of rect.
     @param height The height of rect.
     */
    inline Rect(float x, float y, float width, float height);
    
    /**
     Operator equal.

     @param other Refrence from other rect.

     @return Rect.
     */
    inline const Rect& operator= (const Rect& other);
    
public:
    // Low left point of rect.
    Vec2 origin;
    // Width and height of the rect.
    Size size;
};

NS_DY_END

#include "math/Rect.inl"

#endif /* Rect_h */
