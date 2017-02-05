//
//  GLProgram.h
//  Candy
//
//  Created by Dongyang.Cai on 05/02/2017.
//
//

#ifndef GLProgram_h
#define GLProgram_h

#include "include/CandyMacros.h"

#include "object/Ref.h"
#include "platform/platform.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

class GLProgram : public candy::object::Ref {
public:
    DY_CONSTRUCTOR_FUNC(GLProgram);
    
    /**
     Create or Initializes the GLProgram with a vertex and fragment with bytes array.

     @param vertByteArray vertex shader byte array
     @param fragByteArray frag shader byte array
     @return GLProgram
     */
    static GLProgram* create(const GLchar* vertByteArray, const GLchar* fragByteArray);
    
    bool init(const GLchar* vertByteArray, const GLchar* fragByteArray);
    
protected:
    // OpenGL handle for program.
    GLuint _program;
    // OpenGL handle for vertex shader.
    GLuint _vertShader;
    // OpenGL handle for fragment shader.
    GLuint _fragShader;
};

NS_RENDERER_END

NS_DY_END

#endif /* GLProgram_h */
