//
//  Layer.cpp
//  Candy
//
//  Created by Dongyang.Cai on 06/01/2017.
//
//

#include "math/math.h"

#include "object/Layer.h"
#include "object/Director.h"

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
    math::Size s = Director::getInstance()->getWinSize();
    return initWithParams(Color4F(0.0, 0.0, 0.0, 0.0), s._width, s._height);
}

bool Layer::initWithParams(const Color4F& color, GLfloat w, GLfloat h)
{
    // default blend function
    _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
    
    for (size_t i = 0; i < sizeof(_squareVertices) / sizeof(_squareVertices[0]); i++) {
        _squareVertices[i]._x = 0.0f;
        _squareVertices[i]._y = 0.0f;
    }
    
    updateColor();
    setContentSize(math::Size(w, h));
    
    
    
    return true;
}

void Layer::updateColor()
{
    for (unsigned int i = 0; i < 4; i++) {
        _squareColor[i]._r = _color._r / 255.0f;
        _squareColor[i]._g = _color._g / 255.0f;
        _squareColor[i]._b = _color._b / 255.0f;
        _squareColor[i]._a = _color._a / 255.0f;
    }
}

void Layer::setContentSize(const math::Size &size)
{
    _squareVertices[1]._x = size._width;
    _squareVertices[2]._y = size._height;
    _squareVertices[3]._x = size._width;
    _squareVertices[4]._y = size._height;
    
    Node::setContentSize(size);
}

NS_OBJECT_END

NS_DY_END
