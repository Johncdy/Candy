//
//  GLProgramState.h
//  Candy
//
//  Created by Dongyang.Cai on 06/02/2017.
//
//

#ifndef GLProgramState_h
#define GLProgramState_h

#include "include/CandyMacros.h"

#include "object/Ref.h"
#include "platform/platform.h"
#include "renderer/GLProgram.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Node;

NS_OBJECT_END

NS_RENDERER_BEGIN

/**
 GLProgramState holds the 'state' (uniforms and attributes) of the GLProgram.
 A GLProgram can be used by thousands of Nodes, but if different uniform values
 are going to be used, then each node will need its own GLProgramState
 */
class GLProgramState : public object::Ref {
public:
    
    /**
     returns a new instance of GLProgramState for a given GLProgram

     @param glprogram GLProgram
     @return GLProgram state
     */
    static GLProgramState* create(GLProgram* glprogram);
    
    /**
     gets-or-creates an instance of GLProgramState for a given GLProgramName

     @param glProgramName glProgramName
     @return GLProgramState
     */
    static GLProgramState* getOrCreateWithGLProgramName(const std::string& glProgramName);
    
    /**
     Setter and Getter of the owner GLProgram binded in this program state.

     @param glprogram GLProgram
     */
    void setGLProgram(GLProgram* glprogram);
    GLProgram* getGLProgram() { return _program; }

    /**
     Returns the Node bound to the GLProgramState

     @return the Node bound to the GLProgramState
     */
    object::Node* getNodeBinding() const;
    
    /**
     * Sets the node that this render state is bound to.
     *
     * The specified node is used to apply auto-bindings for the render state.
     * This is typically set to the node of the model that a material is
     * applied to.
     *
     * @param node The node to use for applying auto-bindings.
     */
    void setNodeBinding(object::Node* node);
    
protected:
    DY_CONSTRUCTOR_FUNC(GLProgramState);
    
    bool init(GLProgram* program);
    
    // Binded glprogram.
    GLProgram* _program;
    
    // weak ref
    object::Node* _nodeBinding;
};

NS_RENDERER_END

NS_DY_END

#endif /* GLProgramState_h */
