//
//  Node.cpp
//  Candy
//
//  Created by Dongyang.Cai on 19/11/2016.
//
//

#include "object/node/Node.h"
#include "object/Camera.h"

#include "assert.h"

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
, _cameraMask(1)
, _isUsingNormalizedPosition(false)
, _isNormalizedPositionDirty(false)
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

bool Node::isVisitableByCamera() const
{
    auto camera = Camera::getVisitingCamera();
    bool visible = ((unsigned short)camera->getCameraFlag() & _cameraMask) ?  : true;
    return visible;
}

void Node::setCameraMask(unsigned short mask, bool applayChildren)
{
    _cameraMask = mask;
    if (applayChildren) {
        for (const auto& child : _children) {
            child->setCameraMask(mask, applayChildren);
        }
    }
}

uint32_t Node::processParentFlags(const math::Mat4 &parentTransform, uint32_t parentFlags)
{
    if (_isUsingNormalizedPosition) {
        assert(_parent);
        
        if ((parentFlags & FLAGS_CONTENT_SIZE_DIRTY) || _isNormalizedPositionDirty) {
            math::Size s = _parent->getContentSize();
            _position._x = _normalizedPosition._x * s._width;
            _position._y = _normalizedPosition._y * s._height;
            _isTransformUpdated = _isInverseDirty = _isTransformDirty = true;
            _isNormalizedPositionDirty = false;
        }
    }
    
    if (!isVisitableByCamera()) {
        return parentFlags;
    }
    
    uint32_t flags = parentFlags;
    flags |= (_isTransformUpdated ? FLAGS_TRANSFORM_DIRTY : 0);
    flags |= (_isContentSizeDirty ? FLAGS_CONTENT_SIZE_DIRTY : 0);
    
    if (flags & FLAGS_DIRTY_MASK) {
        _modelViewTransform = transform(parentTransform);
    }
    
    _isTransformUpdated = false;
    _isContentSizeDirty = false;
    
    return flags;
}

void Node::visit(renderer::Renderer *renderer, const math::Mat4 &parentTransform, uint32_t parentFlags)
{
    if (!_visible) {
        return;
    }
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    _director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewTransform);
    
    bool visibleByCamera = isVisitableByCamera();
    
    int i = 0;
    if (!_children.empty()) {
        sortAllChildren();
        for (; i < _children.size(); i++) {
            Node* node = _children.at(i);
            if (node && node->_localZOrder < 0) {
                node->visit(renderer, _modelViewTransform, flags);
            } else {
                break;
            }
        }
        
        if (visibleByCamera) {
            this->draw(renderer, _modelViewTransform, flags);
        }
        
        for (auto it = _children.cbegin(); it != _children.end(); it++) {
            (*it)->visit(renderer, _modelViewTransform, flags);
        }
    } else if (visibleByCamera) {
        this->draw(renderer, _modelViewTransform, flags);
    }
    
    _director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Node::draw(renderer::Renderer *renderer, const math::Mat4 &transform, uint32_t flags)
{
    
}

math::Mat4 Node::transform(const math::Mat4& parentTransform)
{
    return math::Mat4::ZERO;
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

const math::Vec2& Node::getPosition() const
{
    return _position;
}

void Node::setNormalizedPosition(const math::Vec2 &position)
{
    
}

const math::Vec2& Node::getNormalizedPosition() const
{
    return _normalizedPosition;
}

void Node::setContentSize(const math::Size& contentSize)
{
    
}

const math::Size& Node::getContentSize() const
{
    return _contentSize;
}

NS_OBJECT_END

NS_DY_END
