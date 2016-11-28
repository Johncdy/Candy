//
//  Node.h
//  Candy
//
//  Created by Dongyang.Cai on 19/11/2016.
//
//

#ifndef Node_h
#define Node_h

#include "include/CandyMacros.h"

#include "object/Ref.h"
#include "object/Director.h"
#include "math/math.h"

#include <vector>

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Node : public Ref {
public:
    /** Default tag used for all the nodes */
    static const int INVALID_TAG = -1;
    
    enum {
        FLAGS_TRANSFORM_DIRTY = (1 << 0),
        FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),
        FLAGS_RENDER_AS_3D = (1 << 3),
        FLAGS_DIRTY_MASK = (FLAGS_TRANSFORM_DIRTY | FLAGS_CONTENT_SIZE_DIRTY),
    };
    
    /**
     * Allocates and initializes a node.
     * @return A initialized node which is marked as "autorelease".
     */
    static Node* create();
    
    virtual bool init();
    
    /**
     LocalZOrder is the 'key' used to sort the node relative to its siblings.
     
     The Node's parent will sort all its children based on the LocalZOrder value.
     If two nodes have the same LocalZOrder, then the node that was added first to the children's array will be in front of the other node in the array.
     
     Also, the Scene Graph is traversed using the "In-Order" tree traversal algorithm ( http://en.wikipedia.org/wiki/Tree_traversal#In-order )
     And Nodes that have LocalZOrder values < 0 are the "left" subtree
     While Nodes with LocalZOrder >=0 are the "right" subtree.
     
     @see `setGlobalZOrder`
     @see `setVertexZ`
     *
     * @param localZOrder The local Z order value.
     */
    virtual void setLocalZOrder(int localZOrder);
    
    virtual int getLocalZOrder() const { return _localZOrder; }
    
    /** !!! ONLY FOR INTERNAL USE
     * Sets the arrival order when this node has a same ZOrder with other children.
     *
     * A node which called addChild subsequently will take a larger arrival order,
     * If two children have the same Z order, the child with larger arrival order will be drawn later.
     *
     * @warning This method is used internally for localZOrder sorting, don't change this manually
     *
     */
    void updateOrderOfArrival();
    
    /**
     * Sorts the children array once before drawing, instead of every time when a child is added or reordered.
     * This approach can improves the performance massively.
     * @note Don't call this manually unless a child added needs to be removed in the same frame.
     */
    virtual void sortAllChildren();
    
    /**
     * Sorts helper function
     *
     */
    template<typename _T> inline
    static void sortNodes(std::vector<_T*>& nodes)
    {
        static_assert(std::is_base_of<Node, _T>::value, "Node::sortNodes: Only accept derived of Node!");
#if DY_64
        std::sort(std::begin(nodes), std::end(nodes), [](_T* n1, _T* n2) {
            return (n1->_localZOrderAndArrival < n2->_localZOrderAndArrival);
        });
#else
        std::stable_sort(std::begin(nodes), std::end(nodes), [](_T* n1, _T* n2) {
            return (n1->_localZOrder < n2->_localZOrder);
        });
#endif
    }
    
    /**
     * Visits this node's children and draw them recursively.
     *
     * @param renderer A given renderer.
     * @param parentTransform A transform matrix.
     * @param parentFlags Renderer flag.
     */
    virtual void visit(renderer::Renderer *renderer, const math::Mat4& parentTransform, uint32_t parentFlags);
    
    /**
     * Override this method to draw your own node.
     * The following GL states will be enabled by default:
     * - `glEnableClientState(GL_VERTEX_ARRAY);`
     * - `glEnableClientState(GL_COLOR_ARRAY);`
     * - `glEnableClientState(GL_TEXTURE_COORD_ARRAY);`
     * - `glEnable(GL_TEXTURE_2D);`
     * AND YOU SHOULD NOT DISABLE THEM AFTER DRAWING YOUR NODE
     * But if you enable any other GL state, you should disable it after drawing your node.
     *
     * @param renderer A given renderer.
     * @param transform A transform matrix.
     * @param flags Renderer flag.
     */
    virtual void draw(renderer::Renderer *renderer, const math::Mat4& transform, uint32_t flags);
    
    /**
     Defines the order in which the nodes are renderer.
     Nodes that have a Global Z Order lower, are renderer first.
     
     In case two or more nodes have the same Global Z Order, the order is not guaranteed.
     The only exception if the Nodes have a Global Z Order == 0. In that case, the Scene Graph order is used.
     
     By default, all nodes have a Global Z Order = 0. That means that by default, the Scene Graph order is used to render the nodes.
     
     Global Z Order is useful when you need to render nodes in an order different than the Scene Graph order.
     
     Limitations: Global Z Order can't be used by Nodes that have SpriteBatchNode as one of their ancestors.
     And if ClippingNode is one of the ancestors, then "global Z order" will be relative to the ClippingNode.
     
     @see `setLocalZOrder()`
     @see `setVertexZ()`
     
     @since v3.0
     *
     * @param globalZOrder The global Z order value.
     */
    virtual void setGlobalZOrder(float globalZOrder);
    
    /**
     * Returns the Node's Global Z Order.
     *
     * @see `setGlobalZOrder(int)`
     *
     * @return The node's global Z order
     */
    virtual float getGlobalZOrder() const { return _globalZOrder; }
    
    /**
     * Sets the scale (x) of the node.
     *
     * It is a scaling factor that multiplies the width of the node and its children.
     *
     * @param scaleX   The scale factor on X axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScaleX(float scaleX);
    /**
     * Returns the scale factor on X axis of this node
     *
     * @see setScaleX(float)
     *
     * @return The scale factor on X axis.
     */
    virtual float getScaleX() const;
    
    /**
     * Sets the scale (y) of the node.
     *
     * It is a scaling factor that multiplies the height of the node and its children.
     *
     * @param scaleY   The scale factor on Y axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScaleY(float scaleY);
    /**
     * Returns the scale factor on Y axis of this node
     *
     * @see `setScaleY(float)`
     *
     * @return The scale factor on Y axis.
     */
    virtual float getScaleY() const;
    
    /**
     * Changes the scale factor on Z axis of this node
     *
     * The Default value is 1.0 if you haven't changed it before.
     *
     * @param scaleZ   The scale factor on Z axis.
     *
     * @warning The physics body doesn't support this.
     */
    virtual void setScaleZ(float scaleZ);
    /**
     * Returns the scale factor on Z axis of this node
     *
     * @see `setScaleZ(float)`
     *
     * @return The scale factor on Z axis.
     */
    virtual float getScaleZ() const;
    
    /**
     * Sets the untransformed size of the node.
     *
     * The contentSize remains the same no matter the node is scaled or rotated.
     * All nodes has a size. Layer and Scene has the same size of the screen.
     *
     * @param contentSize   The untransformed size of the node.
     */
    virtual void setContentSize(const math::Size& contentSize);
    /**
     * Returns the untransformed size of the node.
     *
     * @see `setContentSize(const Size&)`
     *
     * @return The untransformed size of the node.
     */
    virtual const math::Size& getContentSize() const;

    /**
     * Sets the position (x,y) of the node in its parent's coordinate system.
     *
     * Usually we use `Vec2(x,y)` to compose Vec2 object.
     * This code snippet sets the node in the center of screen.
     @code
     Size size = Director::getInstance()->getWinSize();
     node->setPosition(size.width/2, size.height/2);
     @endcode
     *
     * @param position  The position (x,y) of the node in OpenGL coordinates.
     */
    virtual void setPosition(const math::Vec2 &position);
    
    /** Sets the position (x,y) using values between 0 and 1.
     The positions in pixels is calculated like the following:
     @code
     // pseudo code
     void setNormalizedPosition(Vec2 pos) {
     Size s = getParent()->getContentSize();
     _position = pos * s;
     }
     @endcode
     *
     * @param position The normalized position (x,y) of the node, using value between 0 and 1.
     */
    virtual void setNormalizedPosition(const math::Vec2 &position);
    
    /**
     * Gets the position (x,y) of the node in its parent's coordinate system.
     *
     * @see setPosition(const Vec2&)
     *
     * @return The position (x,y) of the node in OpenGL coordinates.
     * @code
     * In js and lua return value is table which contains x,y.
     * @endcode
     */
    virtual const math::Vec2& getPosition() const;
    
    /** Returns the normalized position.
     *
     * @return The normalized position.
     */
    virtual const math::Vec2& getNormalizedPosition() const;
    
    //check whether this camera mask is visible by the current visiting camera
    bool isVisitableByCamera() const;
    
    /**
     * get & set camera mask, the node is visible by the camera whose camera flag & node's camera mask is true
     */
    unsigned short getCameraMask() const { return _cameraMask; }
    /**
     * Modify the camera mask for current node.
     * If applyChildren is true, then it will modify the camera mask of its children recursively.
     * @param mask A unsigned short bit for mask.
     * @param applyChildren A boolean value to determine whether the mask bit should apply to its children or not.
     */
    virtual void setCameraMask(unsigned short mask, bool applyChildren = true);
    
protected:
    // Nodes should be created using create();
    Node();
    virtual ~Node();
    
    ///< rotation on the X-axis
    float _rotationX;
    ///< rotation on the Y-axis
    float _rotationY;
    
    ///< rotation angle on Z-axis, component X
    float _rotationZ_X;
    ///< rotation angle on Z-axis, component Y
    float _rotationZ_Y;
    
    ///rotation using quaternion, if _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX, else _rotationQuat = RotationY * RotationX
    math::Quaternion _rotationQuat;
    
    ///< scaling factor on x-axis
    float _scaleX;
    ///< scaling factor on y-axis
    float _scaleY;
    ///< scaling factor on z-axis
    float _scaleZ;
    
    ///< position of the node
    math::Vec2 _position;
    ///< OpenGL real Z position
    float _positionZ;
    math::Vec2 _normalizedPosition;
    bool _isUsingNormalizedPosition;
    bool _isNormalizedPositionDirty;
    
    ///< skew angle on x-axis
    float _skewX;
    ///< skew angle on y-axis
    float _skewY;
    
    ///< anchor point in points
    math::Vec2 _anchorPointInPoints;
    ///< anchor point normalized (NOT in points)
    math::Vec2 _anchorPoint;
    
    ///< untransformed size of the node
    math::Size _contentSize;
    ///< whether or not the contentSize is dirty
    bool _isContentSizeDirty;
    
    ///< ModelView transform of the Node.
    math::Mat4 _modelViewTransform;
    
    // "cache" variables are allowed to be mutable
    ///< transform
    mutable math::Mat4 _transform;
    ///< transform dirty flag
    mutable bool _isTransformDirty;
    ///< inverse transform
    mutable math::Mat4 _inverse;
    ///< inverse dirty flag
    mutable bool _isInverseDirty;
    ///< two transforms needed by additional transforms
    mutable math::Mat4 _additionalTransform;
    ///< transform dirty ?
    mutable bool _isAdditionalTransform;
    ///< Whether or not the Transform object was updated since the last frame
    bool _isTransformUpdated;
    
    /// cache, for 64bits compress optimize.
    std::int64_t _localZOrderAndArrival;
    /// < Local order (relative to its siblings) used to sort the node
    int _localZOrder;
    ///< Global order used to sort the node
    float _globalZOrder;
    ///< children order dirty flag
    bool _isReorderChildDirty;
    
    static unsigned int s_globalOrderOfArrival;
    
    ///< array of children nodes
    std::vector<Node*> _children;
    ///< weak reference to parent node
    Node* _parent;
    //cached director pointer to improve rendering performance
    Director* _director;
    ///< a tag. Can be any number you assigned just to identify this node
    int _tag;
    
    ///<a string label, an user defined string to identify this node
    std::string _name;
    ///<hash value of _name, used for speed in getChildByName
    size_t _hashOfName;
    
    ///< A user assigned void pointer, Can be point to any cpp object
    void* _userData;
    ///< A user assigned Object
    object::Ref* _userObject;
    
    ///< is this node visible
    bool _visible;
    
    // camera mask, it is visible only when _cameraMask & current camera' camera flag is true
    unsigned short _cameraMask;
    
protected:
    uint32_t processParentFlags(const math::Mat4& parentTransform, uint32_t parentFlags);
    
    math::Mat4 transform(const math::Mat4 &parentTransform);
    
private:
    /*
     Helper function used by `setLocalZOrder`. Don't use it unless you know what you are doing.
     @js NA
     */
    virtual void _setLocalZOrder(int z);
    
    /**
     * Reorders a child according to a new z value.
     *
     * @param child     An already added child node. It MUST be already added.
     */
    virtual void _reorderChild(Node * child);
};

NS_OBJECT_END

NS_DY_END

#endif /* Node_h */
