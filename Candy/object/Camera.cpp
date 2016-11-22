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

NS_OBJECT_END

NS_DY_END
