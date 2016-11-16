//
//  Vec3.h
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#ifndef Vec3_h
#define Vec3_h

#include "include/Candy.h"

NS_DY_BEGIN

NS_MATH_BEGIN

/**
 * Defines a 3-element floating point vector.
 *
 * When using a vector to represent a surface normal,
 * the vector should typically be normalized.
 * Other uses of directional vectors may wish to leave
 * the magnitude of the vector intact. When used as a point,
 * the elements of the vector represent a position in 3D space.
 */
class Vec3 {
public:
    
    /**
     * Constructs a new vector initialized to all zeros.
     */
    inline Vec3();
    
    /**
     * Constructs a new vector initialized to the specified values.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param z The z coordinate.
     */
    inline Vec3(float x, float y, float z);
    
    /**
     * Constructs a new vector from the values in the specified array.
     *
     * @param array An array containing the elements of the vector in the order x, y, z.
     */
    inline Vec3(const float* array);
    
    /**
     * Constructs a new vector that is a copy of the specified vector.
     *
     * @param copy The vector to copy.
     */
    inline Vec3(const Vec3& copy);
    
    /**
     * Sets the elements of this vector to the specified values.
     *
     * @param x The new x coordinate.
     * @param y The new y coordinate.
     * @param z The new z coordinate.
     */
    inline void set(float x, float y, float z);
    
    /**
     Operator equal.
     
     @param other Refrence from other vec3.
     
     @return Vec3.
     */
    inline const Vec3& operator= (const Vec3& other);
    
    /**
     * Calculates the sum of this vector with the given vector.
     *
     * Note: this does not modify this vector.
     *
     * @param other The vector to add.
     * @return The vector sum.
     */
    inline const Vec3 operator+ (const Vec3& other) const;
    
    /**
     * Calculates the difference of this vector with the given vector.
     *
     * Note: this does not modify this vector.
     *
     * @param other The vector to subtract.
     * @return The vector difference.
     */
    inline const Vec3 operator- (const Vec3& other) const;
    
    /**
     * Calculates the scalar product of this vector with the given value.
     *
     * Note: this does not modify this vector.
     *
     * @param a The value to scale by.
     * @return The scaled vector.
     */
    inline const Vec3 operator* (float a) const;
    
    /**
     * Returns the components of this vector divided by the given constant
     *
     * Note: this does not modify this vector.
     *
     * @param a the constant to divide this vector with
     * @return a smaller vector
     */
    inline const Vec3 operator/ (float a) const;
    
public:
    // The x-coordinate.
    float _x;
    // The y-coordinate.
    float _y;
    // The z-coordinate.
    float _z;
};

NS_MATH_END

NS_DY_END

#include "math/Vec3.inl"

#endif /* Vec3_h */
