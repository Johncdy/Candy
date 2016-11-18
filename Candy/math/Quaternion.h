//
//  Quaternion.h
//  Candy
//
//  Created by Dongyang.Cai on 18/11/2016.
//
//

#ifndef Quaternion_h
#define Quaternion_h

#include "math/Vec3.h"

NS_DY_BEGIN

NS_MATH_BEGIN

class Mat4;

class Quaternion
{
public:
    /**
     * The x-value of the quaternion's vector component.
     */
    float _x;
    /**
     * The y-value of the quaternion's vector component.
     */
    float _y;
    /**
     * The z-value of the quaternion's vector component.
     */
    float _z;
    /**
     * The scalar component of the quaternion.
     */
    float _w;
    
    /**
     * Constructs a quaternion initialized to (0, 0, 0, 1).
     */
    Quaternion();
    
    /**
     * Constructs a quaternion initialized to (0, 0, 0, 1).
     *
     * @param xx The x component of the quaternion.
     * @param yy The y component of the quaternion.
     * @param zz The z component of the quaternion.
     * @param ww The w component of the quaternion.
     */
    Quaternion(float xx, float yy, float zz, float ww);
    
    /**
     * Constructs a new quaternion from the values in the specified array.
     *
     * @param array The values for the new quaternion.
     */
    Quaternion(float* array);
    
    /**
     * Constructs a quaternion equal to the rotational part of the specified matrix.
     *
     * @param m The matrix.
     */
    Quaternion(const Mat4& m);
    
    /**
     * Constructs a quaternion equal to the rotation from the specified axis and angle.
     *
     * @param axis A vector describing the axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    Quaternion(const Vec3& axis, float angle);
    
    /**
     * Constructs a new quaternion that is a copy of the specified one.
     *
     * @param copy The quaternion to copy.
     */
    Quaternion(const Quaternion& copy);
    
    /**
     * Destructor.
     */
    ~Quaternion();
    
    /**
     * Returns the identity quaternion.
     *
     * @return The identity quaternion.
     */
    static const Quaternion& identity();
    
    /**
     * Returns the quaternion with all zeros.
     *
     * @return The quaternion.
     */
    static const Quaternion& zero();
    
    /**
     * Determines if this quaternion is equal to the identity quaternion.
     *
     * @return true if it is the identity quaternion, false otherwise.
     */
    bool isIdentity() const;
    
    /**
     * Determines if this quaternion is all zeros.
     *
     * @return true if this quaternion is all zeros, false otherwise.
     */
    bool isZero() const;
    
    /**
     * Creates a quaternion equal to the rotational part of the specified matrix
     * and stores the result in dst.
     *
     * @param m The matrix.
     * @param dst A quaternion to store the conjugate in.
     */
    static void createFromRotationMatrix(const Mat4& m, Quaternion* dst);
    
    /**
     * Creates this quaternion equal to the rotation from the specified axis and angle
     * and stores the result in dst.
     *
     * @param axis A vector describing the axis of rotation.
     * @param angle The angle of rotation (in radians).
     * @param dst A quaternion to store the conjugate in.
     */
    static void createFromAxisAngle(const Vec3& axis, float angle, Quaternion* dst);
    
    /**
     * Sets this quaternion to the conjugate of itself.
     */
    void conjugate();
    
    /**
     * Gets the conjugate of this quaternion.
     *
     */
    Quaternion getConjugated() const;
    
    /**
     * Sets this quaternion to the inverse of itself.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     *
     * @return true if the inverse can be computed, false otherwise.
     */
    bool inverse();
    
    /**
     * Gets the inverse of this quaternion.
     *
     * Note that the inverse of a quaternion is equal to its conjugate
     * when the quaternion is unit-length. For this reason, it is more
     * efficient to use the conjugate method directly when you know your
     * quaternion is already unit-length.
     */
    Quaternion getInversed() const;
    
    /**
     * Multiplies this quaternion by the specified one and stores the result in this quaternion.
     *
     * @param q The quaternion to multiply.
     */
    void multiply(const Quaternion& q);
    
    /**
     * Multiplies the specified quaternions and stores the result in dst.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param dst A quaternion to store the result in.
     */
    static void multiply(const Quaternion& q1, const Quaternion& q2, Quaternion* dst);
    
    /**
     * Normalizes this quaternion to have unit length.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method does nothing.
     */
    void normalize();
    
    /**
     * Get the normalized quaternion.
     *
     * If the quaternion already has unit length or if the length
     * of the quaternion is zero, this method simply copies
     * this vector.
     */
    Quaternion getNormalized() const;
    
    /**
     * Sets the elements of the quaternion to the specified values.
     *
     * @param xx The new x-value.
     * @param yy The new y-value.
     * @param zz The new z-value.
     * @param ww The new w-value.
     */
    void set(float xx, float yy, float zz, float ww);
    
    /**
     * Sets the elements of the quaternion from the values in the specified array.
     *
     * @param array An array containing the elements of the quaternion in the order x, y, z, w.
     */
    void set(float* array);
    
    /**
     * Sets the quaternion equal to the rotational part of the specified matrix.
     *
     * @param m The matrix.
     */
    void set(const Mat4& m);
    
    /**
     * Sets the quaternion equal to the rotation from the specified axis and angle.
     *
     * @param axis The axis of rotation.
     * @param angle The angle of rotation (in radians).
     */
    void set(const Vec3& axis, float angle);
    
    /**
     * Sets the elements of this quaternion to a copy of the specified quaternion.
     *
     * @param q The quaternion to copy.
     */
    void set(const Quaternion& q);
    
    /**
     * Sets this quaternion to be equal to the identity quaternion.
     */
    void setIdentity();
    
    /**
     * Converts this Quaternion4f to axis-angle notation. The axis is normalized.
     *
     * @param e The Vec3f which stores the axis.
     *
     * @return The angle (in radians).
     */
    float toAxisAngle(Vec3* e) const;
    
    /**
     * Interpolates between two quaternions using linear interpolation.
     *
     * The interpolation curve for linear interpolation between
     * quaternions gives a straight line in quaternion space.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void lerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * Interpolates between two quaternions using spherical linear interpolation.
     *
     * Spherical linear interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be at (or close to) unit length.
     * This method does not automatically normalize the input quaternions, so it is up to the
     * caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void slerp(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
    
    /**
     * Interpolates over a series of quaternions using spherical spline interpolation.
     *
     * Spherical spline interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be unit.
     * This method does not automatically normalize the input quaternions,
     * so it is up to the caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1 The first quaternion.
     * @param q2 The second quaternion.
     * @param s1 The first control point.
     * @param s2 The second control point.
     * @param t The interpolation coefficient.
     * @param dst A quaternion to store the result in.
     */
    static void squad(const Quaternion& q1, const Quaternion& q2, const Quaternion& s1, const Quaternion& s2, float t, Quaternion* dst);
    
    /**
     * Calculates the quaternion product of this quaternion with the given quaternion.
     *
     * Note: this does not modify this quaternion.
     *
     * @param q The quaternion to multiply.
     * @return The quaternion product.
     */
    inline const Quaternion operator*(const Quaternion& q) const;
    
    /**
     * Calculates the quaternion product of this quaternion with the given vec3.
     * @param v The vec3 to multiply.
     * @return The vec3 product.
     */
    inline Vec3 operator*(const Vec3& v) const;
    
    /**
     * Multiplies this quaternion with the given quaternion.
     *
     * @param q The quaternion to multiply.
     * @return This quaternion, after the multiplication occurs.
     */
    inline Quaternion& operator*=(const Quaternion& q);
    
    /** equals to Quaternion(0,0,0, 0) */
    static const Quaternion ZERO;
    
private:
    
    /**
     * Interpolates between two quaternions using spherical linear interpolation.
     *
     * Spherical linear interpolation provides smooth transitions between different
     * orientations and is often useful for animating models or cameras in 3D.
     *
     * Note: For accurate interpolation, the input quaternions must be at (or close to) unit length.
     * This method does not automatically normalize the input quaternions, so it is up to the
     * caller to ensure they call normalize beforehand, if necessary.
     *
     * @param q1x The x component of the first quaternion.
     * @param q1y The y component of the first quaternion.
     * @param q1z The z component of the first quaternion.
     * @param q1w The w component of the first quaternion.
     * @param q2x The x component of the second quaternion.
     * @param q2y The y component of the second quaternion.
     * @param q2z The z component of the second quaternion.
     * @param q2w The w component of the second quaternion.
     * @param t The interpolation coefficient.
     * @param dstx A pointer to store the x component of the slerp in.
     * @param dsty A pointer to store the y component of the slerp in.
     * @param dstz A pointer to store the z component of the slerp in.
     * @param dstw A pointer to store the w component of the slerp in.
     */
    static void slerp(float q1x, float q1y, float q1z, float q1w, float q2x, float q2y, float q2z, float q2w, float t, float* dstx, float* dsty, float* dstz, float* dstw);
    
    static void slerpForSquad(const Quaternion& q1, const Quaternion& q2, float t, Quaternion* dst);
};

NS_MATH_END

NS_DY_END

#endif /* Quaternion_h */
