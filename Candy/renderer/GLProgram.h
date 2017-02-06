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

#include <unordered_map>

NS_DY_BEGIN

NS_RENDERER_BEGIN

// Uniform is a structure to encapsulate data got from glGetActiveUniform and glGetUniformLocation.
struct Uniform {
    // The place where the uniform placed, starts from 0.
    GLint _location;
    // Number of data type in attribute.
    GLint _size;
    // Data type of the attribute.
    GLenum _type;
    // String of the uniform name.
    std::string _name;
};

// VertexAttrib is a structure to encapsulate data got from glGetActiveAttrib.
struct VertexAttrib {
    // Index of attribute, start from 0.
    GLuint index;
    // Number of Data type in the attribute, could range from 0-4.
    GLint size;
    // Data type of the attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
    GLenum type;
    // The string name in vertex shader.
    std::string name;
};

class GLProgram : public object::Ref {
public:
    // ETC1 ALPHA supports for 2d.
    static const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR;
    static const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP;
    
    static const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY;
    static const char* SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP;
    
    // Built in shader for 2d. Support Position, Texture and Color vertex attribute.
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR;
    // Built in shader for 2d. Support Position, Texture and Color vertex attribute, but without multiply vertex by MVP matrix.
    static const char* SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP;
    // Built in shader for 2d. Support Position, Texture vertex attribute, but include alpha test.
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
    // Built in shader for 2d. Support Position, Texture and Color vertex attribute, include alpha test and without multiply vertex by MVP matrix.
    static const char* SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV;
    // Built in shader for 2d. Support Position, Color vertex attribute.
    static const char* SHADER_NAME_POSITION_COLOR;
    // Built in shader for 2d. Support Position, Color, Texture vertex attribute. texture coordinate will used as point size.
    static const char* SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE;
    // Built in shader for 2d. Support Position, Color vertex attribute, without multiply vertex by MVP matrix.
    static const char* SHADER_NAME_POSITION_COLOR_NO_MVP;
    // Built in shader for 2d. Support Position, Texture vertex attribute.
    static const char* SHADER_NAME_POSITION_TEXTURE;
    // Built in shader for 2d. Support Position, Texture vertex attribute. with a specified uniform as color.
    static const char* SHADER_NAME_POSITION_TEXTURE_U_COLOR;
    // Built in shader for 2d. Support Position, Texture and Color vertex attribute. but alpha will be the multiplication of color attribute and texture.
    static const char* SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
    // Built in shader for 2d. Support Position, with color specified by a uniform.
    static const char* SHADER_NAME_POSITION_U_COLOR;
    // Built in shader for draw a sector with 90 degrees with center at bottom left point.
    static const char* SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;
    
    // Built in shader for ui effects.
    static const char* SHADER_NAME_POSITION_GRAYSCALE;
    
    DY_CONSTRUCTOR_FUNC(GLProgram);
    
    /**
     Create or Initializes the GLProgram with a vertex and fragment with bytes array.

     @param vertByteArray vertex shader byte array
     @param fragByteArray frag shader byte array
     @return GLProgram
     */
    static GLProgram* create(const GLchar* vertByteArray, const GLchar* fragByteArray);
    
    bool init(const GLchar* vertByteArray, const GLchar* fragByteArray);
    
    /**
     links the glProgram

     @return link result
     */
    bool link();
    
    /**
     it will call glUseProgram()
     */
    void use();
    
    /**
     Compile the shader sources.

     @param shader shader opengl handle
     @param type gl type define
     @param source shader source
     @return compile result
     */
    bool compileShader(GLuint* shader, GLenum type, const GLchar* source);
    
protected:
    // OpenGL handle for program.
    GLuint _program;
    // OpenGL handle for vertex shader.
    GLuint _vertShader;
    // OpenGL handle for fragment shader.
    GLuint _fragShader;
    
    // User defined Uniforms.
    std::unordered_map<std::string, Uniform> _uniforms;
    // User defined vertex attributes.
    std::unordered_map<std::string, VertexAttrib> _vertexAttribs;
    // Hash value of uniforms for quick access.
    std::unordered_map<GLint, std::pair<GLvoid*, unsigned int>> _hashForUniform;
};

NS_RENDERER_END

NS_DY_END

#endif /* GLProgram_h */
