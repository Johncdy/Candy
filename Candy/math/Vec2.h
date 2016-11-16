//
//  Vec2.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef Vec2_h
#define Vec2_h

#include "include/CandyMacros.h"

NS_DY_BEGIN

NS_MATH_BEGIN

class Vec2 {
public:
    
    /**
     * Constructs a new vector initialized to all zeros.
     */
    inline Vec2();
    
    /**
     Constructs a new vector initialized to the specified values.

     @param x   The x coordinate.
     @param y   The y coordinate.
     */
    inline Vec2(float x, float y);
    
    /**
     * Constructs a new vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y.
     */
    inline Vec2(const float* array);
    
    /**
     * Constructs a new vector that is a copy of the specified vector.
     *
     * @param copy The vector to copy.
     */
    inline Vec2(const Vec2& copy);
    
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
    inline const Vec2 operator+ (const Vec2& other) const;
    
    /**
     Operator minus.

     @param other Refrence from other vec2.

     @return Vec2.
     */
    inline const Vec2 operator- (const Vec2& other) const;
    
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
    // The x-coordinate.
    float _x;
    // The y-coordinate.
    float _y;
};

NS_MATH_END

NS_DY_END

#include "math/Vec2.inl"

#endif /* Vec2_h */
