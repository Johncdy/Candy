//
//  Rect.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef Rect_h
#define Rect_h

#include "Size.h"
#include "Vec2.h"

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
    Rect(float x, float y, float width, float height);
    
public:
    // Low left point of rect.
    Vec2 origin;
    // Width and height of the rect.
    Size size;
};

NS_DY_END

#endif /* Rect_h */
