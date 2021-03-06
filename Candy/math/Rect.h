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

NS_MATH_BEGIN

class Rect {
public:
    /**
     Constructor an empty Rect.
     */
    inline Rect();
    
    /**
     Constructor a rect.

     @param x      The x coordinate.
     @param y      The y coordinate.
     @param width  The width of rect.
     @param height The height of rect.
     */
    inline Rect(float x, float y, float width, float height);
    
    /**
     Copy constructor.
     */
    inline Rect(const Rect& copy);
    
    /**
     Operator equal.

     @param other Refrence from other rect.

     @return Rect.
     */
    inline const Rect& operator= (const Rect& other);
    
    /**
     Setter of a rect.
     
     @param x      The x coordinate.
     @param y      The y coordinate.
     @param width  The width of rect.
     @param height The height of rect.
     */
    inline void set(float x, float y, float width, float height);
    
public:
    // Low left point of rect.
    Vec2 _origin;
    // Width and height of the rect.
    Size _size;
};

NS_MATH_END

NS_DY_END

#include "math/Rect.inl"

#endif /* Rect_h */
