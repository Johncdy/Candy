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
    inline Vec2(float x, float y);
    
    /**
     Setter of a Vec2.
     
     @param x   The x coordinate.
     @param y   The y coordinate.
     */
    inline void set(float x, float y);
    
    /**
     Operator equal.

     @param other Refrence from other vec2.

     @return Vec2.
     */
    inline const Vec2& operator= (const Vec2 &other);
    
    /**
     Operator plus.

     @param other Refrence from other vec2.

     @return Vec2.
     */
    inline const Vec2 operator+ (const Vec2 &other) const;
    
    /**
     Operator minus.

     @param other Refrence from other vec2.

     @return Vec2.
     */
    inline const Vec2 operator- (const Vec2 &other) const;
    
    /**
     Operator multipy.

     @param a Float number.

     @return Vec2.
     */
    inline const Vec2 operator* (float a) const;
    
    /**
     Operator division.

     @param a Float nubmer.

     @return Vec2.
     */
    inline const Vec2 operator/ (float a) const;
    
public:
    // The x coordinate.
    float _x;
    // The y coordinate.
    float _y;
};

NS_DY_END

#include "math/Vec2.inl"

#endif /* Vec2_h */
