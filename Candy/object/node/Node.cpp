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

#include <math.h>

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

bool Node::isVisitableByVisitingCamera() const
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
    
    if (!isVisitableByVisitingCamera()) {
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
    
    bool visibleByCamera = isVisitableByVisitingCamera();
    
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
    if (!_normalizedPosition.equals(position)) {
        
        _normalizedPosition = position;
        _isUsingNormalizedPosition = true;
        _isNormalizedPositionDirty = true;
        _isTransformUpdated = _isTransformDirty = _isInverseDirty = true;
    }
}

const math::Vec2& Node::getNormalizedPosition() const
{
    return _normalizedPosition;
}

void Node::setAnchorPoint(const math::Vec2 &anchorPoint)
{
    if (!anchorPoint.equals(_anchorPoint)) {
        _anchorPoint = anchorPoint;
        
        _isTransformUpdated = _isTransformDirty = _isInverseDirty = true;
    }
}

const math::Vec2& Node::getAnchorPoint() const
{
    return _anchorPoint;
}

void Node::setContentSize(const math::Size& contentSize)
{
    if (!contentSize.equals(_contentSize)) {
        _contentSize = contentSize;
        
        _anchorPointInPoints.set(_contentSize._width * _anchorPoint._x, _contentSize._height * _anchorPoint._y);
        _isTransformUpdated = _isTransformDirty = _isInverseDirty = _isContentSizeDirty = true;
    }
}

const math::Size& Node::getContentSize() const
{
    return _contentSize;
}

const math::Mat4& Node::getNodeToParentTransform() const
{
    if (_isTransformDirty) {
        // Translate values
        float x = _position._x;
        float y = _position._y;
        float z = _positionZ;
        
        bool needsSkewMatrix = (_skewX || _skewY);
        
        math::Vec2 anchorPoint(_anchorPointInPoints._x * _scaleX, _anchorPointInPoints._y * _scaleY);
        
        // calculate real position
        if (!needsSkewMatrix && !anchorPoint.isZero()) {
            x += anchorPoint._x;
            y += anchorPoint._y;
        }
        
        // Build Transform Matrix = translation * rotation * scale
        math::Mat4 translation;
        //move to anchor point first, then rotate
        math::Mat4::createTranslation(x + anchorPoint._x, y + anchorPoint._y, z, &translation);
        
        math::Mat4::createRotation(_rotationQuat, &translation);
        
        if (_rotationZ_X != _rotationZ_Y) {
            // Rotation values
            // Change rotation code to handle X and Y
            // If we skew with the exact same value for both x and y then we're simply just rotating
            float radiansX = -MATH_DEG_TO_RAD(_rotationZ_X);
            float radiansY = -MATH_DEG_TO_RAD(_rotationZ_Y);
            float cx = cosf(radiansX);
            float sx = sinf(radiansX);
            float cy = cosf(radiansY);
            float sy = sinf(radiansY);
            
            float m0 = _transform.m[0], m1 = _transform.m[1], m4 = _transform.m[4], m5 = _transform.m[5], m8 = _transform.m[8], m9 = _transform.m[9];
            _transform.m[0] = cy * m0 - sx * m1, _transform.m[4] = cy * m4 - sx * m5, _transform.m[8] = cy * m8 - sx * m9;
            _transform.m[1] = sy * m0 + cx * m1, _transform.m[5] = sy * m4 + cx * m5, _transform.m[9] = sy * m8 + cx * m9;
        }
        _transform = translation * _transform;
        //move by (-anchorPoint.x, -anchorPoint.y, 0) after rotation
        _transform.translate(-anchorPoint._x, -anchorPoint._y, 0);
        
        if (_scaleX != 1.f)
        {
            _transform.m[0] *= _scaleX, _transform.m[1] *= _scaleX, _transform.m[2] *= _scaleX;
        }
        if (_scaleY != 1.f)
        {
            _transform.m[4] *= _scaleY, _transform.m[5] *= _scaleY, _transform.m[6] *= _scaleY;
        }
        if (_scaleZ != 1.f)
        {
            _transform.m[8] *= _scaleZ, _transform.m[9] *= _scaleZ, _transform.m[10] *= _scaleZ;
        }
        
        // FIXME:: Try to inline skew
        // If skew is needed, apply skew and then anchor point
        if (needsSkewMatrix) {
            float skewMatArray[16] =
            {
                1, (float)tanf(MATH_DEG_TO_RAD(_skewY)), 0, 0,
                (float)tanf(MATH_DEG_TO_RAD(_skewX)), 1, 0, 0,
                0,  0,  1, 0,
                0,  0,  0, 1
            };
            math::Mat4 skewMatrix(skewMatArray);
            
            _transform = _transform * skewMatrix;
            
            // adjust anchor point
            if (!_anchorPointInPoints.isZero())
            {
                // FIXME:: Argh, Mat4 needs a "translate" method.
                // FIXME:: Although this is faster than multiplying a vec4 * mat4
                _transform.m[12] += _transform.m[0] * -_anchorPointInPoints._x + _transform.m[4] * -_anchorPointInPoints._y;
                _transform.m[13] += _transform.m[1] * -_anchorPointInPoints._x + _transform.m[5] * -_anchorPointInPoints._y;
            }
        }
    }
    
    return _transform;
}

math::AffineTransform Node::getNodeToParentAffineTransform() const
{
    
}

math::AffineTransform Node::getNodeToParentAffineTransform(candy::object::Node *ancestor) const
{
    
}

void Node::setVisible(bool visible)
{
    if (!_visible == visible) {
        _visible = visible;
        if (_visible) {
            _isTransformUpdated = _isTransformDirty = _isInverseDirty = true;
        }
    }
}

bool Node::isVisible() const
{
    return _visible;
}

NS_OBJECT_END

NS_DY_END
