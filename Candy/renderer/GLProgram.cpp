//
//  GLProgram.cpp
//  Candy
//
//  Created by Dongyang.Cai on 05/02/2017.
//
//

#include "renderer/GLProgram.h"

#include <string.h>

NS_DY_BEGIN

NS_RENDERER_BEGIN

/*********************************/
// Built Shader types
/*********************************/
const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR = "#ShaderETC1ASPositionTextureColor";
const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_COLOR_NO_MVP = "#ShaderETC1ASPositionTextureColor_noMVP";

const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY = "#ShaderETC1ASPositionTextureGray";
const char* GLProgram::SHADER_NAME_ETC1AS_POSITION_TEXTURE_GRAY_NO_MVP = "#ShaderETC1ASPositionTextureGray_noMVP";

const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR = "ShaderPositionTextureColor";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP = "ShaderPositionTextureColor_noMVP";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST = "ShaderPositionTextureColorAlphaTest";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST_NO_MV = "ShaderPositionTextureColorAlphaTest_NoMV";
const char* GLProgram::SHADER_NAME_POSITION_COLOR = "ShaderPositionColor";
const char* GLProgram::SHADER_NAME_POSITION_COLOR_TEXASPOINTSIZE = "ShaderPositionColorTexAsPointsize";
const char* GLProgram::SHADER_NAME_POSITION_COLOR_NO_MVP = "ShaderPositionColor_noMVP";

const char* GLProgram::SHADER_NAME_POSITION_TEXTURE = "ShaderPositionTexture";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR = "ShaderPositionTexture_uColor";
const char* GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR = "ShaderPositionTextureA8Color";
const char* GLProgram::SHADER_NAME_POSITION_U_COLOR = "ShaderPosition_uColor";
const char* GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR = "ShaderPositionLengthTextureColor";
const char* GLProgram::SHADER_NAME_POSITION_GRAYSCALE = "ShaderUIGrayScale";

/*********************************/
// Built Attribute names
/*********************************/
const char* GLProgram::ATTRIBUTE_NAME_COLOR = "a_color";
const char* GLProgram::ATTRIBUTE_NAME_POSITION = "a_position";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD0 = "a_texCoord";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD1 = "a_texCoord1";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD2 = "a_texCoord2";
const char* GLProgram::ATTRIBUTE_NAME_TEX_COORD3 = "a_texCoord3";
const char* GLProgram::ATTRIBUTE_NAME_NORMAL = "a_normal";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT = "a_blendWeight";
const char* GLProgram::ATTRIBUTE_NAME_BLEND_INDEX = "a_blendIndex";
const char* GLProgram::ATTRIBUTE_NAME_TANGENT = "a_tangent";
const char* GLProgram::ATTRIBUTE_NAME_BINORMAL = "a_binormal";

static const char* DY_SHADER_UNIFORMS =
    "uniform mat4 DY_PMatrix;\n"
    "uniform mat4 DY_MVMatrix;\n"
    "uniform mat4 DY_MVPMatrix;\n"
    "uniform mat3 DY_NormalMatrix;\n"
    "uniform vec4 DY_Time;\n"
    "uniform vec4 DY_SinTime;\n"
    "uniform vec4 DY_CosTime;\n"
    "uniform vec4 DY_Random01;\n"
    "uniform sampler2D DY_Texture0;\n"
    "uniform sampler2D DY_Texture1;\n"
    "uniform sampler2D DY_Texture2;\n"
    "uniform sampler2D DY_Texture3;\n";

static std::string logForOpenGLShader(GLuint shader)
{
    GLint logLength = 0;
    
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength < 1) {
        return "";
    }
    
    char* logBytes = (char*)malloc(sizeof(char) * logLength);
    glGetShaderInfoLog(shader, logLength, nullptr, logBytes);
    std::string ret(logBytes);
    free(logBytes);
    
    return ret;
}

GLProgram::GLProgram()
: _program(0)
, _vertShader(0)
, _fragShader(0)
{
    memset(_builtInUniforms, 0, sizeof(_builtInUniforms));
}

GLProgram::~GLProgram()
{
}

GLProgram* GLProgram::create(const char *vertByteArray, const char *fragByteArray)
{
    GLProgram* ret = new (std::nothrow)GLProgram();
    if (ret && ret->init(vertByteArray, fragByteArray)) {
        ret->link();
        
        ret->autoRelease();
        return ret;
    }
    DY_SAFE_DELETE(ret);
    return nullptr;
}

bool GLProgram::init(const char *vertByteArray, const char *fragByteArray)
{
    _program = glCreateProgram();
    DY_CHECK_GLERROR();
    
    _vertShader = _fragShader = 0;
    
    if (vertByteArray) {
        if (!compileShader(&_vertShader, GL_VERTEX_SHADER, vertByteArray)) {
            printf("Candy: Failed to compile vertex shader");
            return false;
        }
    }
    
    if (fragByteArray) {
        if (!compileShader(&_fragShader, GL_FRAGMENT_SHADER, fragByteArray)) {
            printf("Candy: Failed to compile fragment shader");
            return false;
        }
    }
    
    if (_vertShader) {
        glAttachShader(_program, _vertShader);
    }
    DY_CHECK_GLERROR();
    
    if (_fragShader) {
        glAttachShader(_program, _fragShader);
    }
    DY_CHECK_GLERROR();
    
    return true;
}

bool GLProgram::compileShader(GLuint* shader, GLenum type, const GLchar* source)
{
    GLint status;
    
    if (!source) {
        return false;
    }
    
    const GLchar* sources[] = {
        DY_SHADER_UNIFORMS,
        source
    };
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, sizeof(sources)/sizeof(*sources), sources, nullptr);
    glCompileShader(*shader);
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    
    if (!status) {
        GLsizei length;
        glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &status);
        GLchar* src = (GLchar*)malloc(sizeof(GLchar) * length);
        
        glGetShaderSource(*shader, length, nullptr, src);
        printf("Candy Error: Failed to compile shader:\n%s", src);
        
        if (GL_VERTEX_SHADER == type) {
            printf("Candy: %s", logForOpenGLShader(_vertShader).c_str());
        } else {
            printf("Candy: %s", logForOpenGLShader(_fragShader).c_str());
        }
        free(src);
        
        return false;
    }
    
    return (status == GL_TRUE);
}

bool GLProgram::link()
{
    DY_ASSERT(_program && "Candy: Cannot link invalid program");
    
    GLint status = GL_TRUE;
    
    bindPredefinedVertexAttribs();
    
    glLinkProgram(_program);
    
    // Calling glGetProgramiv(...GL_LINK_STATUS...) will force linking of the program at this moment.
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    
    if (GL_FALSE == status) {
        printf("Candy: Failed to link program: %i", _program);
        glDeleteProgram(_program);
        _program = 0;
    } else {
        parseVertexAttribs();
        parseUniforms();
        
        clearShader();
    }
    
    return (status == GL_TRUE);
}

void GLProgram::bindPredefinedVertexAttribs()
{
    // Bind predefined vertexAttribs.
    struct attributeLocation {
        const char* attributeName;
        int location;
    };
    attributeLocation locations[] = {
        {ATTRIBUTE_NAME_POSITION,   VERTEX_ATTRIB_POSITION},
        {ATTRIBUTE_NAME_COLOR,      VERTEX_ATTRIB_COLOR},
        {ATTRIBUTE_NAME_TEX_COORD0, VERTEX_ATTRIB_TEX_COORD0},
        {ATTRIBUTE_NAME_TEX_COORD1, VERTEX_ATTRIB_TEX_COORD1},
        {ATTRIBUTE_NAME_TEX_COORD2, VERTEX_ATTRIB_TEX_COORD2},
        {ATTRIBUTE_NAME_TEX_COORD3, VERTEX_ATTRIB_TEX_COORD3},
        {ATTRIBUTE_NAME_NORMAL,     VERTEX_ATTRIB_NORMAL},
    };
    
    const int size = sizeof(locations) / sizeof(locations[0]);
    
    for (int i = 0; i < size; i++) {
        glBindAttribLocation(_program, locations[i].location, locations[i].attributeName);
    }
}

void GLProgram::parseVertexAttribs()
{
    // Query and store vertex attribute meta-data from the program.
    GLint activeAttributes;
    GLint length;
    glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &activeAttributes);
    if (activeAttributes > 0) {
        VertexAttrib attribute;
        
        glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &length);
        if (length > 0) {
            GLchar* attribName = (GLchar*)alloca(length + 1);
            for (int i = 0; i < activeAttributes; i++) {
                // Query attribute info.
                glGetActiveAttrib(_program, i, length, nullptr, &attribute._size, &attribute._type, attribName);
                attribName[length] = '\0';
                attribute._name = std::string(attribName);
                
                // Query the pre-assigned attribute location
                attribute._index = glGetAttribLocation(_program, attribName);
                
                _vertexAttribs[attribute._name] = attribute;
            }
        }
    } else {
        GLchar errorLog[1024];
        glGetProgramInfoLog(_program, sizeof(errorLog), nullptr, errorLog);
        printf("Candy: Error linking shader program: %s\n", errorLog);
    }
}

void GLProgram::parseUniforms()
{
    // Query and store uniforms from the program.
    GLint activeUniforms;
    GLint length;
    glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &activeUniforms);
    if (activeUniforms > 0) {
        Uniform uniform;
        
        glGetProgramiv(_program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
        if (length > 0) {
            GLchar* uniformName = (GLchar*)alloca(length + 1);
            for (int i = 0; i < activeUniforms; i++) {
                // Query uniform info.
                glGetActiveUniform(_program, i, length, nullptr, &uniform._size, &uniform._type, uniformName);
                uniformName[length] = '\0';
                uniform._name = uniformName;
                
                // Only add uniforms that are not built-in.
                // The ones that start with 'DY_' are built-ins
                if (strncmp("DY_", uniformName, 3) != 0) {
                    // remove possible array '[]' from uniform name
                    if (length > 3) {
                        char* c = strrchr(uniformName, '[');
                        if (c) {
                            *c = '\0';
                        }
                    }
                    uniform._location = glGetUniformLocation(_program, uniformName);
                    uniform._name = std::string(uniformName);
                    GLenum __gl_error_code = glGetError();
                    if (__gl_error_code != GL_NO_ERROR)
                    {
                        printf("error: 0x%x  uniformName: %s", (int)__gl_error_code, uniformName);
                    }
                    DY_ASSERT(__gl_error_code == GL_NO_ERROR);
                    
                    _uniforms[uniform._name] = uniform;
                }
            }
        }
    } else {
        GLchar errorLog[1024];
        glGetProgramInfoLog(_program, sizeof(errorLog), nullptr, errorLog);
        printf("Candy: Error linking shader program: %s\n", errorLog);
    }
}

void GLProgram::clearShader()
{
    if (_vertShader) {
        glDeleteShader(_vertShader);
    }
    
    if (_fragShader) {
        glDeleteShader(_fragShader);
    }
    
    _vertShader = _fragShader = 0;
}

void GLProgram::updateUniforms()
{
    _builtInUniforms[UNIFORM_AMBIENT_COLOR] = glGetUniformLocation(_program, UNIFORM_NAME_AMBIENT_COLOR);
    _builtInUniforms[UNIFORM_P_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_P_MATRIX);
    _builtInUniforms[UNIFORM_MV_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MV_MATRIX);
    _builtInUniforms[UNIFORM_MVP_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_MVP_MATRIX);
    _builtInUniforms[UNIFORM_NORMAL_MATRIX] = glGetUniformLocation(_program, UNIFORM_NAME_NORMAL_MATRIX);
    
    _builtInUniforms[UNIFORM_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_TIME);
    _builtInUniforms[UNIFORM_SIN_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_SIN_TIME);
    _builtInUniforms[UNIFORM_COS_TIME] = glGetUniformLocation(_program, UNIFORM_NAME_COS_TIME);
    
    _builtInUniforms[UNIFORM_RANDOM01] = glGetUniformLocation(_program, UNIFORM_NAME_RANDOM01);
    
    _builtInUniforms[UNIFORM_SAMPLER0] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER0);
    _builtInUniforms[UNIFORM_SAMPLER1] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER1);
    _builtInUniforms[UNIFORM_SAMPLER2] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER2);
    _builtInUniforms[UNIFORM_SAMPLER3] = glGetUniformLocation(_program, UNIFORM_NAME_SAMPLER3);
    
    _flags.usesP = _builtInUniforms[UNIFORM_P_MATRIX] != -1;
    _flags.usesMV = _builtInUniforms[UNIFORM_MV_MATRIX] != -1;
    _flags.usesMVP = _builtInUniforms[UNIFORM_MVP_MATRIX] != -1;
    _flags.usesNormal = _builtInUniforms[UNIFORM_NORMAL_MATRIX] != -1;
    _flags.usesTime = (
                       _builtInUniforms[UNIFORM_TIME] != -1 ||
                       _builtInUniforms[UNIFORM_SIN_TIME] != -1 ||
                       _builtInUniforms[UNIFORM_COS_TIME] != -1
                       );
    _flags.usesRandom = _builtInUniforms[UNIFORM_RANDOM01] != -1;
    
    use();
}

void GLProgram::use()
{
    glUseProgram(_program);
}

void GLProgram::setUniformLocationWith1i(GLint location, GLint i1)
{
    
}

NS_RENDERER_END

NS_DY_END
