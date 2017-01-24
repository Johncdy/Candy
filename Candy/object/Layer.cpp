//
//  Layer.cpp
//  Candy
//
//  Created by Dongyang.Cai on 06/01/2017.
//
//

#include "object/Layer.h"
#include "math/math.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

Layer::Layer()
{
    setAnchorPoint(math::Vec2(0.5, 0.5));
}

Layer::~Layer()
{
}

bool Layer::init()
{
    return true;
}

Layer* Layer::create()
{
    Layer* ret = new (std::nothrow)Layer();
    if (ret && ret->init()) {
        ret->autoRelease();
        return ret;
    }
    DY_SAFE_DELETE(ret);
    return ret;
}

NS_OBJECT_END

NS_DY_END