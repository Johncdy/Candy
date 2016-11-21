//
//  RenderCommand.cpp
//  Candy
//
//  Created by Dongyang.Cai on 19/11/2016.
//
//

#include "renderer/RenderCommand.h"

#include "object/node/Node.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

RenderCommand::RenderCommand()
: _type(RenderCommand::Type::UNKNOW_COMMAND)
, _globalOrder(0)
, _isTransparent(true)
, _isSkipBatching(false)
, _is3D(false)
, _depth(0)
{
}

RenderCommand::~RenderCommand()
{
}

void RenderCommand::init(float globalZOrder, const math::Mat4& modelViewTransform, uint32_t flags)
{
    _globalOrder = globalZOrder;
    if (flags & object::Node::FLAGS_RENDER_AS_3D) {
        
    } else {
        set3D(false);
        _depth = 0;
    }
}

void RenderCommand::printID()
{
    printf("Command Depth: %f\n", _depth);
}

NS_RENDERER_END

NS_DY_END
