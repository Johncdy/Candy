//
//  Vec2.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef Vec2_h
#define Vec2_h

#include "platform/PlatformMacros.h"

NS_DY_BEGIN

class Vec2 {
public:
    
    /**
     Constructs a new vector initialized to the specified values.

     @param x   The x coordinate.
     @param y   The y coordinate.
     */
    Vec2(float x, float y);
    
public:
    // The x coordinate.
    float x;
    // The y coordinate.
    float y;
};

NS_DY_END

#endif /* Vec2_h */
