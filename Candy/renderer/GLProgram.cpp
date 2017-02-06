//
//  GLProgram.cpp
//  Candy
//
//  Created by Dongyang.Cai on 05/02/2017.
//
//

#include "renderer/GLProgram.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

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
}

GLProgram::~GLProgram()
{
}

GLProgram* GLProgram::create(const char *vertByteArray, const char *fragByteArray)
{
    GLProgram* ret = new (std::nothrow)GLProgram();
    if (ret && ret->init(vertByteArray, fragByteArray)) {
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

bool GLProgram::link()
{
    DY_ASSERT(_program && "Candy: Cannot link invalid program");
    
    GLint status = GL_TRUE:
    
    return true;
}

void GLProgram::use()
{
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

NS_RENDERER_END

NS_DY_END
