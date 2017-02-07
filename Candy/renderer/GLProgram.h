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
    GLuint _index;
    // Number of Data type in the attribute, could range from 0-4.
    GLint _size;
    // Data type of the attribute, could be GL_FLOAT, GL_UNSIGNED_BYTE etc.
    GLenum _type;
    // The string name in vertex shader.
    std::string _name;
};

class GLProgram : public object::Ref {
public:
    /*********************************/
    // Built Shader types
    /*********************************/
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
    
    /*********************************/
    // Built Uniform names.
    /*********************************/
    // Ambient Color uniform.
    static const char* UNIFORM_NAME_AMBIENT_COLOR;
    // Projection Matrix uniform.
    static const char* UNIFORM_NAME_P_MATRIX;
    // Model view matrix uniform.
    static const char* UNIFORM_NAME_MV_MATRIX;
    // Model view projection uniform.
    static const char* UNIFORM_NAME_MVP_MATRIX;
    // Normal matrix uniform.
    static const char* UNIFORM_NAME_NORMAL_MATRIX;
    // Time uniform.
    static const char* UNIFORM_NAME_TIME;
    // Sin time uniform.
    static const char* UNIFORM_NAME_SIN_TIME;
    // Cos time uniform.
    static const char* UNIFORM_NAME_COS_TIME;
    // Random number uniform.
    static const char* UNIFORM_NAME_RANDOM01;
    
    // Sampler uniform 0-3, used for textures.
    static const char* UNIFORM_NAME_SAMPLER0;
    static const char* UNIFORM_NAME_SAMPLER1;
    static const char* UNIFORM_NAME_SAMPLER2;
    static const char* UNIFORM_NAME_SAMPLER3;
    
    // Alpha test value uniform.
    static const char* UNIFORM_NAME_ALPHA_TEST_VALUE;
    
    // Preallocated uniform handle.
    enum
    {
        // Ambient color.
        UNIFORM_AMBIENT_COLOR,
        // Projection matrix.
        UNIFORM_P_MATRIX,
        // Model view matrix.
        UNIFORM_MV_MATRIX,
        // Model view projection matrix.
        UNIFORM_MVP_MATRIX,
        // Normal matrix.
        UNIFORM_NORMAL_MATRIX,
        // Time.
        UNIFORM_TIME,
        // sin(Time).
        UNIFORM_SIN_TIME,
        // cos(Time).
        UNIFORM_COS_TIME,
        // Random number.
        UNIFORM_RANDOM01,
        
        // Sampler 0-3, used for texture.
        UNIFORM_SAMPLER0,
        UNIFORM_SAMPLER1,
        UNIFORM_SAMPLER2,
        UNIFORM_SAMPLER3,
        
        // Index length.
        UNIFORM_MAX,
    };
    
    /*********************************/
    // Built Attribute names
    /*********************************/
    // Attribute color.
    static const char* ATTRIBUTE_NAME_COLOR;
    // Attribute position.
    static const char* ATTRIBUTE_NAME_POSITION;
    // Attribute Texcoord 0-3.
    static const char* ATTRIBUTE_NAME_TEX_COORD0;
    static const char* ATTRIBUTE_NAME_TEX_COORD1;
    static const char* ATTRIBUTE_NAME_TEX_COORD2;
    static const char* ATTRIBUTE_NAME_TEX_COORD3;
    // Attribute normal.
    static const char* ATTRIBUTE_NAME_NORMAL;
    // Attribute blend weight.
    static const char* ATTRIBUTE_NAME_BLEND_WEIGHT;
    // Attribute blend index.
    static const char* ATTRIBUTE_NAME_BLEND_INDEX;
    // Attribute blend tangent.
    static const char* ATTRIBUTE_NAME_TANGENT;
    // Attribute blend binormal.
    static const char* ATTRIBUTE_NAME_BINORMAL;
    
    // Enum the preallocated vertex attribute.
    enum
    {
        // Index 0 will be used as Position.
        VERTEX_ATTRIB_POSITION,
        // Index 1 will be used as Color.
        VERTEX_ATTRIB_COLOR,
        // Index 2 will be used as Tex coord unit 0.
        VERTEX_ATTRIB_TEX_COORD0,
        // Index 3 will be used as Tex coord unit 1.
        VERTEX_ATTRIB_TEX_COORD1,
        // Index 4 will be used as Tex coord unit 2.
        VERTEX_ATTRIB_TEX_COORD2,
        // Index 5 will be used as Tex coord unit 3.
        VERTEX_ATTRIB_TEX_COORD3,
        // Index 6 will be used as Normal.
        VERTEX_ATTRIB_NORMAL,
        // Index 7 will be used as Blend weight for hardware skin.
        VERTEX_ATTRIB_BLEND_WEIGHT,
        // Index 8 will be used as Blend index.
        VERTEX_ATTRIB_BLEND_INDEX,
        // Index 9 will be used as Tangent.
        VERTEX_ATTRIB_TANGENT,
        // Index 10 will be used as Binormal.
        VERTEX_ATTRIB_BINORMAL,
        VERTEX_ATTRIB_MAX,
        
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD0,
    };
    
    // Flags used by the uniforms.
    struct UniformFlags {
        unsigned int usesTime:1;
        unsigned int usesNormal:1;
        unsigned int usesMVP:1;
        unsigned int usesMV:1;
        unsigned int usesP:1;
        unsigned int usesRandom:1;
        // handy way to initialize the bitfield
        UniformFlags() { memset(this, 0, sizeof(*this)); }
    };
    
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
     Compile the shader sources.

     @param shader shader opengl handle
     @param type gl type define
     @param source shader source
     @return compile result
     */
    bool compileShader(GLuint* shader, GLenum type, const GLchar* source);
    
    /**
     links the glProgram
     
     @return link result
     */
    bool link();
    
    /**
     Bind the predefined vertex attributes to their specific slot.
     */
    void bindPredefinedVertexAttribs();
    
    /**
     Parse user defined Vertex Attributes automatically.
     */
    void parseVertexAttribs();
    
    /**
     Parse user defined uniform automatically.
     */
    void parseUniforms();
    
    /**
     Clear vertex and fragment shader.
     */
    void clearShader();
    
    /**
     It will create 4 uniforms:
     - kUniformPMatrix
     - kUniformMVMatrix
     - kUniformMVPMatrix
     - GLProgram::UNIFORM_SAMPLER
     
     And it will bind "GLProgram::UNIFORM_SAMPLER" to 0
     */
    void updateUniforms();
    
    /**
     it will call glUseProgram()
     */
    void use();
    
protected:
    // OpenGL handle for program.
    GLuint _program;
    // OpenGL handle for vertex shader.
    GLuint _vertShader;
    // OpenGL handle for fragment shader.
    GLuint _fragShader;
    // Built in uniforms.
    GLint _builtInUniforms[UNIFORM_MAX];
    
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
