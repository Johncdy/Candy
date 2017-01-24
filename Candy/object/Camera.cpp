//
//  Camera.cpp
//  Candy
//
//  Created by Dongyang.Cai on 22/11/2016.
//
//

#include "object/Camera.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

ViewPort::ViewPort(float left, float bottom, float width, float height)
: _left(left)
, _bottom(bottom)
, _width(width)
, _height(height)
{
}

Camera* Camera::_visitingCamera = nullptr;
ViewPort Camera::_defaultViewPort = ViewPort(0.f, 0.f, 1.0f, 1.0f);

Camera::Camera()
: _flag(Camera::Flag::DEFAULT)
, _depth(-1)
{
}

Camera::~Camera()
{
}

Camera* Camera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    Camera* ret = new (std::nothrow) Camera();
    if (ret && ret->initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)) {
        ret->autoRelease();
        return ret;
    }
    
    DY_SAFE_DELETE(ret);
    return nullptr;
}

bool Camera::initPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    _fieldOfView = fieldOfView;
    _aspectRatio = aspectRatio;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
    math::Mat4::createPerspective(fieldOfView, aspectRatio, nearPlane, fieldOfView, &_projection);
    
    return true;
}

Camera* Camera::createOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
    Camera* ret = new (std::nothrow) Camera();
    if (ret && ret->initOrthographic(zoomX, zoomY, nearPlane, farPlane)) {
        ret->autoRelease();
        return ret;
    }
    
    DY_SAFE_DELETE(ret);
    return nullptr;
}

bool Camera::initOrthographic(float zoomX, float zoomY, float nearPlane, float farPlane)
{
    _zoom[0] = zoomX;
    _zoom[1] = zoomY;
    _nearPlane = nearPlane;
    _farPlane = farPlane;
    math::Mat4::createOrthographicOffCenter(0, _zoom[0], 0, _zoom[1], _nearPlane, _farPlane, &_projection);
    
    return true;
}

const Camera* Camera::getVisitingCamera()
{
    return _visitingCamera;
}

const math::Mat4& Camera::getProjectionMatrix() const
{
    return _projection;
}

void Camera::setDepth(int8_t depth)
{
    if (_depth != depth) {
        _depth = depth;
    }
}

int Camera::getRenderOrder() const
{
    int result(0);
    result = 127 << 8;
    result += _depth;
    
    return result;
}

NS_OBJECT_END

NS_DY_END
