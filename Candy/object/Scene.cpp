//
//  Scene.cpp
//  Candy
//
//  Created by Dongyang.Cai on 25/11/2016.
//
//

#include "object/Scene.h"
#include "object/Director.h"

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

bool Scene::init()
{
    auto size = Director::getInstance()->getWinSize();
    setContentSize(size);
    
    return true;
}

static bool camera_cmp(const Camera* a, const Camera* b)
{
    return a->getRenderOrder() < b->getRenderOrder();
}

const std::vector<Camera*>& Scene::getCameras()
{
    if (_isCameraOrderDirty) {
        stable_sort(_cameras.begin(), _cameras.end(), camera_cmp);
        _isCameraOrderDirty = false;
    }
    return _cameras;
}

void Scene::render(renderer::Renderer *renderer, const math::Mat4 &eyeTransform, const math::Mat4* eyeProjection)
{
    auto director = Director::getInstance();
}

NS_OBJECT_END

NS_DY_END
