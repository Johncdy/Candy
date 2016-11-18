//
//  Mat4.cpp
//  Candy
//
//  Created by Dongyang.Cai on 16/11/2016.
//
//

#include "math/MathMacros.h"
#include "math/Mat4.h"
#include "math/MathUtil.h"

NS_DY_BEGIN

NS_MATH_BEGIN

const Mat4 Mat4::ZERO = Mat4(
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0);

const Mat4 Mat4::IDENTITY = Mat4(
                             1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f);

Mat4::Mat4()
{
    *this = IDENTITY;
}

Mat4::Mat4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    set(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

Mat4::Mat4(const float* mat)
{
    set(mat);
}

Mat4::Mat4(const Mat4& copy)
{
    memcpy(m, copy.m, MATRIX_SIZE);
}

Mat4::~Mat4()
{
}

void Mat4::createLookAt(const Vec3& eyePosition, const Vec3& targetPosition, const Vec3& up, Mat4* dst)
{
    createLookAt(eyePosition._x, eyePosition._y, eyePosition._z, targetPosition._x, targetPosition._y, targetPosition._z,
                 up._x, up._y, up._z, dst);
}

void Mat4::createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                        float targetPositionX, float targetPositionY, float targetPositionZ,
                        float upX, float upY, float upZ, Mat4* dst)
{
    assert(dst);
    
    Vec3 eye(eyePositionX, eyePositionY, eyePositionZ);
    Vec3 target(targetPositionX, targetPositionY, targetPositionZ);
    Vec3 up(upX, upY, upZ);
    up.normalize();
    
    Vec3 zaxis;
    Vec3::subtract(eye, target, &zaxis);
    zaxis.normalize();
    
    Vec3 xaxis;
    Vec3::cross(up, zaxis, &xaxis);
    xaxis.normalize();
    
    Vec3 yaxis;
    Vec3::cross(zaxis, xaxis, &yaxis);
    yaxis.normalize();
    
    dst->m[0] = xaxis._x;
    dst->m[1] = yaxis._x;
    dst->m[2] = zaxis._x;
    dst->m[3] = 0.0f;
    
    dst->m[4] = xaxis._y;
    dst->m[5] = yaxis._y;
    dst->m[6] = zaxis._y;
    dst->m[7] = 0.0f;
    
    dst->m[8] = xaxis._z;
    dst->m[9] = yaxis._z;
    dst->m[10] = zaxis._z;
    dst->m[11] = 0.0f;
    
    dst->m[12] = -Vec3::dot(xaxis, eye);
    dst->m[13] = -Vec3::dot(yaxis, eye);
    dst->m[14] = -Vec3::dot(zaxis, eye);
    dst->m[15] = 1.0f;
}

void Mat4::createPerspective(float fieldOfView, float aspectRatio,
                             float zNearPlane, float zFarPlane, Mat4* dst)
{
    assert(dst);
    assert(zFarPlane != zNearPlane);
    
    float f_n = 1.0f / (zFarPlane - zNearPlane);
    float theta = MATH_DEG_TO_RAD(fieldOfView) * 0.5f;
    if (std::abs(std::fmod(theta, MATH_PIOVER2)) < MATH_EPSILON)
    {
        printf("Invalid field of view value (%f) causes attempted calculation tan(%f), which is undefined.", fieldOfView, theta);
        return;
    }
    float divisor = std::tan(theta);
    assert(divisor);
    float factor = 1.0f / divisor;
    
    memset(dst, 0, MATRIX_SIZE);
    
    assert(aspectRatio);
    dst->m[0] = (1.0f / aspectRatio) * factor;
    dst->m[5] = factor;
    dst->m[10] = (-(zFarPlane + zNearPlane)) * f_n;
    dst->m[11] = -1.0f;
    dst->m[14] = -2.0f * zFarPlane * zNearPlane * f_n;
}

void Mat4::createOrthographic(float width, float height, float zNearPlane, float zFarPlane, Mat4* dst)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    createOrthographicOffCenter(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane, dst);
}

void Mat4::createOrthographicOffCenter(float left, float right, float bottom, float top,
                                       float zNearPlane, float zFarPlane, Mat4* dst)
{
    assert(dst);
    assert(right != left);
    assert(top != bottom);
    assert(zFarPlane != zNearPlane);
    
    memset(dst, 0, MATRIX_SIZE);
    dst->m[0] = 2 / (right - left);
    dst->m[5] = 2 / (top - bottom);
    dst->m[10] = 2 / (zNearPlane - zFarPlane);
    
    dst->m[12] = (left + right) / (left - right);
    dst->m[13] = (top + bottom) / (bottom - top);
    dst->m[14] = (zNearPlane + zFarPlane) / (zNearPlane - zFarPlane);
    dst->m[15] = 1;
}

void Mat4::createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                           const Vec3& cameraUpVector, Mat4* dst)
{
    createBillboardHelper(objectPosition, cameraPosition, cameraUpVector, nullptr, dst);
}

void Mat4::createBillboard(const Vec3& objectPosition, const Vec3& cameraPosition,
                           const Vec3& cameraUpVector, const Vec3& cameraForwardVector,
                           Mat4* dst)
{
    createBillboardHelper(objectPosition, cameraPosition, cameraUpVector, &cameraForwardVector, dst);
}

void Mat4::createBillboardHelper(const Vec3& objectPosition, const Vec3& cameraPosition,
                                 const Vec3& cameraUpVector, const Vec3* cameraForwardVector,
                                 Mat4* dst)
{
    Vec3 delta(objectPosition, cameraPosition);
    bool isSufficientDelta = delta.lengthSquared() > MATH_EPSILON;
    
    dst->setIdentity();
    dst->m[3] = objectPosition._x;
    dst->m[7] = objectPosition._y;
    dst->m[11] = objectPosition._z;
    
    // As per the contracts for the 2 variants of createBillboard, we need
    // either a safe default or a sufficient distance between object and camera.
    if (cameraForwardVector || isSufficientDelta)
    {
        Vec3 target = isSufficientDelta ? cameraPosition : (objectPosition - *cameraForwardVector);
        
        // A billboard is the inverse of a lookAt rotation
        Mat4 lookAt;
        createLookAt(objectPosition, target, cameraUpVector, &lookAt);
        dst->m[0] = lookAt.m[0];
        dst->m[1] = lookAt.m[4];
        dst->m[2] = lookAt.m[8];
        dst->m[4] = lookAt.m[1];
        dst->m[5] = lookAt.m[5];
        dst->m[6] = lookAt.m[9];
        dst->m[8] = lookAt.m[2];
        dst->m[9] = lookAt.m[6];
        dst->m[10] = lookAt.m[10];
    }
}

// void Mat4::createReflection(const Plane& plane, Mat4* dst)
// {
//     Vec3 normal(plane.getNormal());
//     float k = -2.0f * plane.getDistance();

//     dst->setIdentity();

//     dst->m[0] -= 2.0f * normal.x * normal.x;
//     dst->m[5] -= 2.0f * normal.y * normal.y;
//     dst->m[10] -= 2.0f * normal.z * normal.z;
//     dst->m[1] = dst->m[4] = -2.0f * normal.x * normal.y;
//     dst->m[2] = dst->m[8] = -2.0f * normal.x * normal.z;
//     dst->m[6] = dst->m[9] = -2.0f * normal.y * normal.z;

//     dst->m[3] = k * normal.x;
//     dst->m[7] = k * normal.y;
//     dst->m[11] = k * normal.z;
// }

void Mat4::createScale(const Vec3& scale, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    dst->m[0] = scale._x;
    dst->m[5] = scale._y;
    dst->m[10] = scale._z;
}

void Mat4::createScale(float xScale, float yScale, float zScale, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    dst->m[0] = xScale;
    dst->m[5] = yScale;
    dst->m[10] = zScale;
}


void Mat4::createRotation(const Quaternion& q, Mat4* dst)
{
    assert(dst);
    
    float x2 = q._x + q._x;
    float y2 = q._y + q._y;
    float z2 = q._z + q._z;
    
    float xx2 = q._x * x2;
    float yy2 = q._y * y2;
    float zz2 = q._z * z2;
    float xy2 = q._x * y2;
    float xz2 = q._x * z2;
    float yz2 = q._y * z2;
    float wx2 = q._w * x2;
    float wy2 = q._w * y2;
    float wz2 = q._w * z2;
    
    dst->m[0] = 1.0f - yy2 - zz2;
    dst->m[1] = xy2 + wz2;
    dst->m[2] = xz2 - wy2;
    dst->m[3] = 0.0f;
    
    dst->m[4] = xy2 - wz2;
    dst->m[5] = 1.0f - xx2 - zz2;
    dst->m[6] = yz2 + wx2;
    dst->m[7] = 0.0f;
    
    dst->m[8] = xz2 + wy2;
    dst->m[9] = yz2 - wx2;
    dst->m[10] = 1.0f - xx2 - yy2;
    dst->m[11] = 0.0f;
    
    dst->m[12] = 0.0f;
    dst->m[13] = 0.0f;
    dst->m[14] = 0.0f;
    dst->m[15] = 1.0f;
}

void Mat4::createRotation(const Vec3& axis, float angle, Mat4* dst)
{
    assert(dst);
    
    float x = axis._x;
    float y = axis._y;
    float z = axis._z;
    
    // Make sure the input axis is normalized.
    float n = x*x + y*y + z*z;
    if (n != 1.0f)
    {
        // Not normalized.
        n = std::sqrt(n);
        // Prevent divide too close to zero.
        if (n > 0.000001f)
        {
            n = 1.0f / n;
            x *= n;
            y *= n;
            z *= n;
        }
    }
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    float t = 1.0f - c;
    float tx = t * x;
    float ty = t * y;
    float tz = t * z;
    float txy = tx * y;
    float txz = tx * z;
    float tyz = ty * z;
    float sx = s * x;
    float sy = s * y;
    float sz = s * z;
    
    dst->m[0] = c + tx*x;
    dst->m[1] = txy + sz;
    dst->m[2] = txz - sy;
    dst->m[3] = 0.0f;
    
    dst->m[4] = txy - sz;
    dst->m[5] = c + ty*y;
    dst->m[6] = tyz + sx;
    dst->m[7] = 0.0f;
    
    dst->m[8] = txz + sy;
    dst->m[9] = tyz - sx;
    dst->m[10] = c + tz*z;
    dst->m[11] = 0.0f;
    
    dst->m[12] = 0.0f;
    dst->m[13] = 0.0f;
    dst->m[14] = 0.0f;
    dst->m[15] = 1.0f;
}

void Mat4::createRotationX(float angle, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    dst->m[5]  = c;
    dst->m[6]  = s;
    dst->m[9]  = -s;
    dst->m[10] = c;
}

void Mat4::createRotationY(float angle, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    dst->m[0]  = c;
    dst->m[2]  = -s;
    dst->m[8]  = s;
    dst->m[10] = c;
}

void Mat4::createRotationZ(float angle, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    float c = std::cos(angle);
    float s = std::sin(angle);
    
    dst->m[0] = c;
    dst->m[1] = s;
    dst->m[4] = -s;
    dst->m[5] = c;
}

void Mat4::createTranslation(const Vec3& translation, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    dst->m[12] = translation._x;
    dst->m[13] = translation._y;
    dst->m[14] = translation._z;
}

void Mat4::createTranslation(float xTranslation, float yTranslation, float zTranslation, Mat4* dst)
{
    assert(dst);
    
    memcpy(dst, &IDENTITY, MATRIX_SIZE);
    
    dst->m[12] = xTranslation;
    dst->m[13] = yTranslation;
    dst->m[14] = zTranslation;
}

void Mat4::add(float scalar)
{
    add(scalar, this);
}

void Mat4::add(float scalar, Mat4* dst)
{
    assert(dst);
#ifdef __SSE__
    MathUtil::addMatrix(col, scalar, dst->col);
#else
    MathUtil::addMatrix(m, scalar, dst->m);
#endif
}

void Mat4::add(const Mat4& mat)
{
    add(*this, mat, this);
}

void Mat4::add(const Mat4& m1, const Mat4& m2, Mat4* dst)
{
    assert(dst);
#ifdef __SSE__
    MathUtil::addMatrix(m1.col, m2.col, dst->col);
#else
    MathUtil::addMatrix(m1.m, m2.m, dst->m);
#endif
}

bool Mat4::decompose(Vec3* scale, Quaternion* rotation, Vec3* translation) const
{
    if (translation)
    {
        // Extract the translation.
        translation->_x = m[12];
        translation->_y = m[13];
        translation->_z = m[14];
    }
    
    // Nothing left to do.
    if (scale == nullptr && rotation == nullptr)
        return true;
    
    // Extract the scale.
    // This is simply the length of each axis (row/column) in the matrix.
    Vec3 xaxis(m[0], m[1], m[2]);
    float scaleX = xaxis.length();
    
    Vec3 yaxis(m[4], m[5], m[6]);
    float scaleY = yaxis.length();
    
    Vec3 zaxis(m[8], m[9], m[10]);
    float scaleZ = zaxis.length();
    
    // Determine if we have a negative scale (true if determinant is less than zero).
    // In this case, we simply negate a single axis of the scale.
    float det = determinant();
    if (det < 0)
        scaleZ = -scaleZ;
    
    if (scale)
    {
        scale->_x = scaleX;
        scale->_y = scaleY;
        scale->_z = scaleZ;
    }
    
    // Nothing left to do.
    if (rotation == nullptr)
        return true;
    
    // Scale too close to zero, can't decompose rotation.
    if (scaleX < MATH_TOLERANCE || scaleY < MATH_TOLERANCE || std::abs(scaleZ) < MATH_TOLERANCE)
        return false;
    
    float rn;
    
    // Factor the scale out of the matrix axes.
    rn = 1.0f / scaleX;
    xaxis._x *= rn;
    xaxis._y *= rn;
    xaxis._z *= rn;
    
    rn = 1.0f / scaleY;
    yaxis._x *= rn;
    yaxis._y *= rn;
    yaxis._z *= rn;
    
    rn = 1.0f / scaleZ;
    zaxis._x *= rn;
    zaxis._y *= rn;
    zaxis._z *= rn;
    
    // Now calculate the rotation from the resulting matrix (axes).
    float trace = xaxis._x + yaxis._y + zaxis._z + 1.0f;
    
    if (trace > MATH_EPSILON)
    {
        float s = 0.5f / std::sqrt(trace);
        rotation->_w = 0.25f / s;
        rotation->_x = (yaxis._z - zaxis._y) * s;
        rotation->_y = (zaxis._x - xaxis._z) * s;
        rotation->_z = (xaxis._y - yaxis._x) * s;
    }
    else
    {
        // Note: since xaxis, yaxis, and zaxis are normalized,
        // we will never divide by zero in the code below.
        if (xaxis._x > yaxis._y && xaxis._x > zaxis._z)
        {
            float s = 0.5f / std::sqrt(1.0f + xaxis._x - yaxis._y - zaxis._z);
            rotation->_w = (yaxis._z - zaxis._y) * s;
            rotation->_x = 0.25f / s;
            rotation->_y = (yaxis._x + xaxis._y) * s;
            rotation->_z = (zaxis._x + xaxis._z) * s;
        }
        else if (yaxis._y > zaxis._z)
        {
            float s = 0.5f / std::sqrt(1.0f + yaxis._y - xaxis._x - zaxis._z);
            rotation->_w = (zaxis._x - xaxis._z) * s;
            rotation->_x = (yaxis._x + xaxis._y) * s;
            rotation->_y = 0.25f / s;
            rotation->_z = (zaxis._y + yaxis._z) * s;
        }
        else
        {
            float s = 0.5f / std::sqrt(1.0f + zaxis._z - xaxis._x - yaxis._y);
            rotation->_w = (xaxis._y - yaxis._x ) * s;
            rotation->_x = (zaxis._x + xaxis._z ) * s;
            rotation->_y = (zaxis._y + yaxis._z ) * s;
            rotation->_z = 0.25f / s;
        }
    }
    
    return true;
}

float Mat4::determinant() const
{
    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];
    
    // Calculate the determinant.
    return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
}

void Mat4::getScale(Vec3* scale) const
{
    decompose(scale, nullptr, nullptr);
}

bool Mat4::getRotation(Quaternion* rotation) const
{
    return decompose(nullptr, rotation, nullptr);
}

void Mat4::getTranslation(Vec3* translation) const
{
    decompose(nullptr, nullptr, translation);
}

void Mat4::getUpVector(Vec3* dst) const
{
    assert(dst);
    
    dst->_x = m[4];
    dst->_y = m[5];
    dst->_z = m[6];
}

void Mat4::getDownVector(Vec3* dst) const
{
    assert(dst);
    
    dst->_x = -m[4];
    dst->_y = -m[5];
    dst->_z = -m[6];
}

void Mat4::getLeftVector(Vec3* dst) const
{
    assert(dst);
    
    dst->_x = -m[0];
    dst->_y = -m[1];
    dst->_z = -m[2];
}

void Mat4::getRightVector(Vec3* dst) const
{
    assert(dst);
    
    dst->_x = m[0];
    dst->_y = m[1];
    dst->_z = m[2];
}

void Mat4::getForwardVector(Vec3* dst) const
{
    assert(dst);
    
    dst->_x = -m[8];
    dst->_y = -m[9];
    dst->_z = -m[10];
}

void Mat4::getBackVector(Vec3* dst) const
{
    assert(dst);
    
    dst->_x = m[8];
    dst->_y = m[9];
    dst->_z = m[10];
}

Mat4 Mat4::getInversed() const
{
    Mat4 mat(*this);
    mat.inverse();
    return mat;
}

bool Mat4::inverse()
{
    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];
    
    // Calculate the determinant.
    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
    
    // Close to zero, can't invert.
    if (std::abs(det) <= MATH_TOLERANCE)
        return false;
    
    // Support the case where m == dst.
    Mat4 inverse;
    inverse.m[0]  = m[5] * b5 - m[6] * b4 + m[7] * b3;
    inverse.m[1]  = -m[1] * b5 + m[2] * b4 - m[3] * b3;
    inverse.m[2]  = m[13] * a5 - m[14] * a4 + m[15] * a3;
    inverse.m[3]  = -m[9] * a5 + m[10] * a4 - m[11] * a3;
    
    inverse.m[4]  = -m[4] * b5 + m[6] * b2 - m[7] * b1;
    inverse.m[5]  = m[0] * b5 - m[2] * b2 + m[3] * b1;
    inverse.m[6]  = -m[12] * a5 + m[14] * a2 - m[15] * a1;
    inverse.m[7]  = m[8] * a5 - m[10] * a2 + m[11] * a1;
    
    inverse.m[8]  = m[4] * b4 - m[5] * b2 + m[7] * b0;
    inverse.m[9]  = -m[0] * b4 + m[1] * b2 - m[3] * b0;
    inverse.m[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
    inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;
    
    inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
    inverse.m[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
    inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
    inverse.m[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;
    
    multiply(inverse, 1.0f / det, this);
    
    return true;
}

bool Mat4::isIdentity() const
{
    return (memcmp(m, &IDENTITY, MATRIX_SIZE) == 0);
}

void Mat4::multiply(float scalar)
{
    multiply(scalar, this);
}

void Mat4::multiply(float scalar, Mat4* dst) const
{
    multiply(*this, scalar, dst);
}

void Mat4::multiply(const Mat4& m, float scalar, Mat4* dst)
{
    assert(dst);
#ifdef __SSE__
    MathUtil::multiplyMatrix(m.col, scalar, dst->col);
#else
    MathUtil::multiplyMatrix(m.m, scalar, dst->m);
#endif
}

void Mat4::multiply(const Mat4& mat)
{
    multiply(*this, mat, this);
}

void Mat4::multiply(const Mat4& m1, const Mat4& m2, Mat4* dst)
{
    assert(dst);
#ifdef __SSE__
    MathUtil::multiplyMatrix(m1.col, m2.col, dst->col);
#else
    MathUtil::multiplyMatrix(m1.m, m2.m, dst->m);
#endif
}

void Mat4::negate()
{
#ifdef __SSE__
    MathUtil::negateMatrix(col, col);
#else
    MathUtil::negateMatrix(m, m);
#endif
}

Mat4 Mat4::getNegated() const
{
    Mat4 mat(*this);
    mat.negate();
    return mat;
}

void Mat4::rotate(const Quaternion& q)
{
    rotate(q, this);
}

void Mat4::rotate(const Quaternion& q, Mat4* dst) const
{
    Mat4 r;
    createRotation(q, &r);
    multiply(*this, r, dst);
}

void Mat4::rotate(const Vec3& axis, float angle)
{
    rotate(axis, angle, this);
}

void Mat4::rotate(const Vec3& axis, float angle, Mat4* dst) const
{
    Mat4 r;
    createRotation(axis, angle, &r);
    multiply(*this, r, dst);
}

void Mat4::rotateX(float angle)
{
    rotateX(angle, this);
}

void Mat4::rotateX(float angle, Mat4* dst) const
{
    Mat4 r;
    createRotationX(angle, &r);
    multiply(*this, r, dst);
}

void Mat4::rotateY(float angle)
{
    rotateY(angle, this);
}

void Mat4::rotateY(float angle, Mat4* dst) const
{
    Mat4 r;
    createRotationY(angle, &r);
    multiply(*this, r, dst);
}

void Mat4::rotateZ(float angle)
{
    rotateZ(angle, this);
}

void Mat4::rotateZ(float angle, Mat4* dst) const
{
    Mat4 r;
    createRotationZ(angle, &r);
    multiply(*this, r, dst);
}

void Mat4::scale(float value)
{
    scale(value, this);
}

void Mat4::scale(float value, Mat4* dst) const
{
    scale(value, value, value, dst);
}

void Mat4::scale(float xScale, float yScale, float zScale)
{
    scale(xScale, yScale, zScale, this);
}

void Mat4::scale(float xScale, float yScale, float zScale, Mat4* dst) const
{
    Mat4 s;
    createScale(xScale, yScale, zScale, &s);
    multiply(*this, s, dst);
}

void Mat4::scale(const Vec3& s)
{
    scale(s._x, s._y, s._z, this);
}

void Mat4::scale(const Vec3& s, Mat4* dst) const
{
    scale(s._x, s._y, s._z, dst);
}

void Mat4::set(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
    m[0]  = m11;
    m[1]  = m21;
    m[2]  = m31;
    m[3]  = m41;
    m[4]  = m12;
    m[5]  = m22;
    m[6]  = m32;
    m[7]  = m42;
    m[8]  = m13;
    m[9]  = m23;
    m[10] = m33;
    m[11] = m43;
    m[12] = m14;
    m[13] = m24;
    m[14] = m34;
    m[15] = m44;
}

void Mat4::set(const float* mat)
{
    assert(mat);
    memcpy(this->m, mat, MATRIX_SIZE);
}

void Mat4::set(const Mat4& mat)
{
    memcpy(this->m, mat.m, MATRIX_SIZE);
}

void Mat4::setIdentity()
{
    memcpy(m, &IDENTITY, MATRIX_SIZE);
}

void Mat4::setZero()
{
    memset(m, 0, MATRIX_SIZE);
}

void Mat4::subtract(const Mat4& mat)
{
    subtract(*this, mat, this);
}

void Mat4::subtract(const Mat4& m1, const Mat4& m2, Mat4* dst)
{
    assert(dst);
#ifdef __SSE__
    MathUtil::subtractMatrix(m1.col, m2.col, dst->col);
#else
    MathUtil::subtractMatrix(m1.m, m2.m, dst->m);
#endif
}

void Mat4::transformVector(Vec3* vector) const
{
    assert(vector);
    transformVector(vector->_x, vector->_y, vector->_z, 0.0f, vector);
}

void Mat4::transformVector(const Vec3& vector, Vec3* dst) const
{
    transformVector(vector._x, vector._y, vector._z, 0.0f, dst);
}

void Mat4::transformVector(float x, float y, float z, float w, Vec3* dst) const
{
    assert(dst);
    
    MathUtil::transformVec4(m, x, y, z, w, (float*)dst);
}

void Mat4::transformVector(Vec4* vector) const
{
    assert(vector);
    transformVector(*vector, vector);
}

void Mat4::transformVector(const Vec4& vector, Vec4* dst) const
{
    assert(dst);
#ifdef __SSE__
    MathUtil::transformVec4(col, vector.v, dst->v);
#else
    MathUtil::transformVec4(m, (const float*) &vector, (float*)dst);
#endif
}

void Mat4::translate(float x, float y, float z)
{
    translate(x, y, z, this);
}

void Mat4::translate(float x, float y, float z, Mat4* dst) const
{
    Mat4 t;
    createTranslation(x, y, z, &t);
    multiply(*this, t, dst);
}

void Mat4::translate(const Vec3& t)
{
    translate(t._x, t._y, t._z, this);
}

void Mat4::translate(const Vec3& t, Mat4* dst) const
{
    translate(t._x, t._y, t._z, dst);
}

void Mat4::transpose()
{
#ifdef __SSE__
    MathUtil::transposeMatrix(col, col);
#else
    MathUtil::transposeMatrix(m, m);
#endif
}

Mat4 Mat4::getTransposed() const
{
    Mat4 mat(*this);
    mat.transpose();
    return mat;
}

NS_MATH_END

NS_DY_END
