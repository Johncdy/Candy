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
     Setter and Getter of the owner GLProgram binded in this program state.

     @param glprogram GLProgram
     */
    void setGLProgram(GLProgram* glprogram);
    GLProgram* getGLProgram() { return _program; }
    
protected:
    DY_CONSTRUCTOR_FUNC(GLProgramState);
    
    bool init(GLProgram* program);
    
    // Binded glprogram.
    GLProgram* _program;
    
    
};

NS_RENDERER_END

NS_DY_END

#endif /* GLProgramState_h */
