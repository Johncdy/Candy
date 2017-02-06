//
//  GLProgramState.cpp
//  Candy
//
//  Created by Dongyang.Cai on 06/02/2017.
//
//

#include "renderer/GLProgramState.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

GLProgramState::GLProgramState()
: _program(nullptr)
{
}

GLProgramState::~GLProgramState()
{
    DY_SAFE_DELETE(_program);
}

GLProgramState* GLProgramState::create(candy::renderer::GLProgram *program)
{
    GLProgramState* ret = new (std::nothrow)GLProgramState;
    if (ret && ret->init(program)) {
        ret->autoRelease();
        return ret;
    }
    DY_SAFE_DELETE(ret);
    ret = nullptr;
    return nullptr;
}

bool GLProgramState::init(candy::renderer::GLProgram *program)
{
    DY_ASSERT(program && "Invalid program");
    
    _program = program;
    _program->retain();
    
    
    return true;
}

void GLProgramState::setGLProgram(candy::renderer::GLProgram *glprogram)
{
    
}

NS_RENDERER_END

NS_DY_END
