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
    delete ret;
    ret = nullptr;
    return nullptr;
}

bool GLProgram::init(const char *vertByteArray, const char *fragByteArray)
{
    return true;
}

NS_RENDERER_END

NS_DY_END
