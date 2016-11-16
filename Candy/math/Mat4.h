//
//  Mat4.h
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#ifndef Mat4_h
#define Mat4_h

#include "include/Candy.h"

#include "math/Vec3.h"

NS_DY_BEGIN

NS_MATH_BEGIN

//class Plane;

/**
 * Defines a 4 x 4 floating point matrix representing a 3D transformation.
 *
 * Vectors are treated as columns, resulting in a matrix that is represented as follows,
 * where x, y and z are the translation components of the matrix:
 *
 *     1  0  0  x
 *     0  1  0  y
 *     0  0  1  z
 *     0  0  0  1
 *
 * This matrix class is directly compatible with OpenGL since its elements are
 * laid out in memory exactly as they are expected by OpenGL.
 * The matrix uses column-major format such that array indices increase down column first.
 * Since matrix multiplication is not commutative, multiplication must be done in the
 * correct order when combining transformations. Suppose we have a translation
 * matrix T and a rotation matrix R. To first rotate an object around the origin
 * and then translate it, you would multiply the two matrices as TR.
 *
 * Likewise, to first translate the object and then rotate it, you would do RT.
 * So generally, matrices must be multiplied in the reverse order in which you
 * want the transformations to take place (this also applies to
 * the scale, rotate, and translate methods below; these methods are convenience
 * methods for post-multiplying by a matrix representing a scale, rotation, or translation).
 *
 * In the case of repeated local transformations (i.e. rotate around the Z-axis by 0.76 radians,
 * then translate by 2.1 along the X-axis, then ...), it is better to use the Transform class
 * (which is optimized for that kind of usage).
 *
 * @see Transform
 */
class Mat4 {
public:
    /**
     * Default constructor.
     * Constructs a matrix initialized to the identity matrix:
     *
     *     1  0  0  0
     *     0  1  0  0
     *     0  0  1  0
     *     0  0  0  1
     */
    inline Mat4();
    
    /**
     * Constructs a matrix initialized to the specified value.
     *
     * @param m11 The first element of the first row.
     * @param m12 The second element of the first row.
     * @param m13 The third element of the first row.
     * @param m14 The fourth element of the first row.
     * @param m21 The first element of the second row.
     * @param m22 The second element of the second row.
     * @param m23 The third element of the second row.
     * @param m24 The fourth element of the second row.
     * @param m31 The first element of the third row.
     * @param m32 The second element of the third row.
     * @param m33 The third element of the third row.
     * @param m34 The fourth element of the third row.
     * @param m41 The first element of the fourth row.
     * @param m42 The second element of the fourth row.
     * @param m43 The third element of the fourth row.
     * @param m44 The fourth element of the fourth row.
     */
    inline Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
         float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
    
    /**
     * Creates a matrix initialized to the specified column-major array.
     *
     * The passed-in array is in column-major order, so the memory layout of the array is as follows:
     *
     *     0   4   8   12
     *     1   5   9   13
     *     2   6   10  14
     *     3   7   11  15
     *
     * @param mat An array containing 16 elements in column-major order.
     */
    inline Mat4(const float* mat);
    
    /**
     * Constructs a new matrix by copying the values from the specified matrix.
     *
     * @param copy The matrix to copy.
     */
    inline Mat4(const Mat4& copy);
    
    /**
     * Sets the values of this matrix.
     *
     * @param m11 The first element of the first row.
     * @param m12 The second element of the first row.
     * @param m13 The third element of the first row.
     * @param m14 The fourth element of the first row.
     * @param m21 The first element of the second row.
     * @param m22 The second element of the second row.
     * @param m23 The third element of the second row.
     * @param m24 The fourth element of the second row.
     * @param m31 The first element of the third row.
     * @param m32 The second element of the third row.
     * @param m33 The third element of the third row.
     * @param m34 The fourth element of the third row.
     * @param m41 The first element of the fourth row.
     * @param m42 The second element of the fourth row.
     * @param m43 The third element of the fourth row.
     * @param m44 The fourth element of the fourth row.
     */
    inline void set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);
    
    /**
     Operator equal.
     
     @param other Refrence from other mat4.
     
     @return Mat4.
     */
    inline const Mat4& operator= (const Mat4& other);
    
    /**
     * Calculates the sum of this mat4 with the given mat4.
     *
     * Note: this does not modify this mat4.
     *
     * @param other The mat4 to add.
     * @return The mat4 sum.
     */
    inline const Mat4 operator+ (const Mat4& other) const;
    
    /**
     * Calculates the difference of this mat4 with the given mat4.
     *
     * Note: this does not modify this mat4.
     *
     * @param other The mat4 to subtract.
     * @return The mat4 difference.
     */
    inline const Mat4 operator- (const Mat4& other) const;
    
    /**
     * Calculates the scalar product of this mat4 with the given value.
     *
     * Note: this does not modify this mat4.
     *
     * @param a The value to scale by.
     * @return The scaled mat4.
     */
    inline const Mat4 operator* (float a) const;
    
    /**
     * Returns the components of this mat4 divided by the given constant
     *
     * Note: this does not modify this mat4.
     *
     * @param a the constant to divide this mat4 with
     * @return a smaller mat4
     */
    inline const Mat4 operator/ (float a) const;
    
    /**
     * Adds the specified matrix to this matrix.
     *
     * @param mat The matrix to add.
     */
    void add(const Mat4& mat);
    
    /**
     * Creates a view matrix based on the specified input parameters.
     *
     * @param eyePosition The eye position.
     * @param targetPosition The target's center position.
     * @param up The up vector.
     * @param dst A matrix to store the result in.
     */
    static void createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4* dst);
    
    /**
     * Creates a view matrix based on the specified input parameters.
     *
     * @param eyePositionX The eye x-coordinate position.
     * @param eyePositionY The eye y-coordinate position.
     * @param eyePositionZ The eye z-coordinate position.
     * @param targetCenterX The target's center x-coordinate position.
     * @param targetCenterY The target's center y-coordinate position.
     * @param targetCenterZ The target's center z-coordinate position.
     * @param upX The up vector x-coordinate value.
     * @param upY The up vector y-coordinate value.
     * @param upZ The up vector z-coordinate value.
     * @param dst A matrix to store the result in.
     */
    static void createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                             float targetCenterX, float targetCenterY, float targetCenterZ,
                             float upX, float upY, float upZ, Mat4* dst);
    
    /**
     * Builds a perspective projection matrix based on a field of view and returns by value.
     *
     * Projection space refers to the space after applying projection transformation from view space.
     * After the projection transformation, visible content has x- and y-coordinates ranging from -1 to 1,
     * and a z-coordinate ranging from 0 to 1. To obtain the viewable area (in world space) of a scene,
     * create a BoundingFrustum and pass the combined view and projection matrix to the constructor.
     *
     * @param fieldOfView The field of view in the y direction (in degrees).
     * @param aspectRatio The aspect ratio, defined as view space width divided by height.
     * @param zNearPlane The distance to the near view plane.
     * @param zFarPlane The distance to the far view plane.
     * @param dst A matrix to store the result in.
     */
    static void createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane, Mat4* dst);
    
    /**
     * Creates an orthographic projection matrix.
     *
     * @param width The width of the view.
     * @param height The height of the view.
     * @param zNearPlane The minimum z-value of the view volume.
     * @param zFarPlane The maximum z-value of the view volume.
     * @param dst A matrix to store the result in.
     */
    static void createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4* dst);
    
    /**
     * Creates an orthographic projection matrix.
     *
     * Projection space refers to the space after applying
     * projection transformation from view space. After the
     * projection transformation, visible content has
     * x and y coordinates ranging from -1 to 1, and z coordinates
     * ranging from 0 to 1.
     *
     * Unlike perspective projection, in orthographic projection
     * there is no perspective foreshortening.
     *
     * The viewable area of this orthographic projection extends
     * from left to right on the x-axis, bottom to top on the y-axis,
     * and zNearPlane to zFarPlane on the z-axis. These values are
     * relative to the position and x, y, and z-axes of the view.
     * To obtain the viewable area (in world space) of a scene,
     * create a BoundingFrustum and pass the combined view and
     * projection matrix to the constructor.
     *
     * @param left The minimum x-value of the view volume.
     * @param right The maximum x-value of the view volume.
     * @param bottom The minimum y-value of the view volume.
     * @param top The maximum y-value of the view volume.
     * @param zNearPlane The minimum z-value of the view volume.
     * @param zFarPlane The maximum z-value of the view volume.
     * @param dst A matrix to store the result in.
     */
    static void createOrthographicOffCenter(float left, float right, float bottom, float top,
                                            float zNearPlane, float zFarPlane, Mat4* dst);
    
    /** equals to a matrix full of zeros */
    static const Mat4 ZERO;
    /** equals to the identity matrix */
    static const Mat4 IDENTITY;
    
public:
    float _m[16];
};

NS_MATH_END

NS_DY_END

#include "math/Mat4.inl"

#endif /* Mat4_h */
