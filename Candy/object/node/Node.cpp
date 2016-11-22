//
//  Node.cpp
//  Candy
//
//  Created by Dongyang.Cai on 19/11/2016.
//
//

#include "object/node/Node.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

unsigned int Node::s_globalOrderOfArrival = 0;

Node::Node()
: _rotationX(0.0f)
, _rotationY(0.0f)
, _rotationZ_X(0.0f)
, _rotationZ_Y(0.0f)
, _scaleX(1.0f)
, _scaleY(1.0f)
, _scaleZ(1.0f)
, _positionZ(0.0f)
, _skewX(0.0f)
, _skewY(0.0f)
, _contentSize(math::Size::ZERO)
, _isContentSizeDirty(true)
, _isTransformDirty(true)
, _isInverseDirty(true)
, _isAdditionalTransform(false)
, _isTransformUpdated(true)
, _localZOrderAndArrival(0)
, _localZOrder(0)
, _globalZOrder(0.0f)
, _isReorderChildDirty(false)
, _parent(nullptr)
, _tag(Node::INVALID_TAG)
, _name("")
, _hashOfName(0)
, _userData(nullptr)
, _userObject(nullptr)
, _visible(true)
{
    _director = Director::getInstance();
}

Node::~Node()
{
}

Node* Node::create()
{
    Node* ret = new (std::nothrow) Node();
    if (ret && ret->init()) {
        ret->autoRelease();
        return ret;
    }
    
    DY_SAFE_DELETE(ret);
    return nullptr;
}

bool Node::init()
{
    return true;
}

void Node::setLocalZOrder(int z)
{
    if (_localZOrder == z) {
        return;
    }
    
    _setLocalZOrder(z);
    if (_parent) {
        _parent->_reorderChild(this);
    }
}

void Node::_setLocalZOrder(int z)
{
    _localZOrderAndArrival = (static_cast<int64_t>(z) << 32) | (_localZOrderAndArrival & 0xffffffff);
    _localZOrder = z;
}

void Node::_reorderChild(candy::object::Node *child)
{
    _isReorderChildDirty = true;
    child->updateOrderOfArrival();
}

void Node::updateOrderOfArrival()
{
    _localZOrderAndArrival = (_localZOrderAndArrival & 0xffffffff00000000) | (++s_globalOrderOfArrival);
}

void Node::sortAllChildren()
{
    if (_isReorderChildDirty) {
        sortNodes(_children);
        _isReorderChildDirty = false;
    }
}

void Node::visit(renderer::Renderer *renderer, const math::Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible) {
        return;
    }
    
    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    
    
    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Node::draw(renderer::Renderer *renderer, const math::Mat4 &transform, uint32_t flags)
{
    
}

void Node::setGlobalZOrder(float globalZOrder)
{
    
}

void Node::setScaleX(float scaleX)
{
    
}

float Node::getScaleX() const
{
    return _scaleX;
}

void Node::setScaleY(float scaleY)
{
    
}

float Node::getScaleY() const
{
    return _scaleY;
}

void Node::setScaleZ(float scaleZ)
{
    
}

float Node::getScaleZ() const
{
    return _scaleZ;
}

void Node::setPosition(const math::Vec2 &position)
{
    
}

NS_OBJECT_END

NS_DY_END
