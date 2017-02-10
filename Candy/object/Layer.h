//
//  Layer.hpp
//  Candy
//
//  Created by Dongyang.Cai on 06/01/2017.
//
//

#ifndef Layer_h
#define Layer_h

#include "include/CandyMacros.h"
#include "include/CandyTypes.h"

#include "object/node/Node.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Layer : public Node {
public:
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased Layer object.
     */
    DY_CREATE_FUNC(Layer);
    
protected:
    Layer();
    virtual ~Layer();
    
    virtual bool init() override;
    
    /**
     Init with color and size.

     @param color Layer color.
     @param w Layer width.
     @param h Layer height.
     @return Init result.
     */
    bool initWithParams(const Color4F& color, GLfloat w, GLfloat h);
    
    /**
     Update Color vector.
     */
    void updateColor();
    
    /**
     Set layer content size.

     @param size content size.
     */
    virtual void setContentSize(const math::Size& size) override;
    
    // Layer blend function.
    BlendFunc _blendFunc;
    // Layer square vertices.
    math::Vec2 _squareVertices[4];
    // Layer square color.
    Color4F _squareColor[4];
    
private:
    // Layer render color.
    Color4F _color;
    
    DY_DISALLOW_COPY_AND_ASSIGN(Layer);
};

NS_OBJECT_END

NS_DY_END

#endif /* Layer_h */
