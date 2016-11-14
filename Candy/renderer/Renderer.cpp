//
//  Renderer.cpp
//  Candy
//
//  Created by Dongyang.Cai on 14/11/2016.
//
//

#include "renderer/Renderer.h"

#include "platform/PlatformMacros.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::clear()
{
    glDepthMask(true);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(false);
}

NS_RENDERER_END

NS_DY_END
