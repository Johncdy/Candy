//
//  Scene.cpp
//  Candy
//
//  Created by Dongyang.Cai on 25/11/2016.
//
//

#include "object/Scene.h"

#include <algorithm>

NS_DY_BEGIN

NS_OBJECT_BEGIN

Scene::Scene()
: _isCameraOrderDirty(true)
{
//    _defaultCamera = Camera::create();
}

Scene::~Scene()
{
}

Scene* Scene::create()
{
    Scene* ret = new (std::nothrow) Scene();
    if (ret && ret->init()) {
        ret->autoRelease();
        return ret;
    }
    
    DY_SAFE_DELETE(ret);
    return nullptr;
}

bool Scene::init()
{
    auto size = Director::getInstance()->getWinSize();
    setContentSize(size);
    
    return true;
}

const std::vector<Camera*>& Scene::getCameras()
{
    if (_isCameraOrderDirty) {
//        stable_sort();
    }
    return _cameras;
}

void Scene::render(renderer::Renderer *renderer, const math::Mat4 &eyeTransform, const math::Mat4* eyeProjection)
{
    
}

NS_OBJECT_END

NS_DY_END
