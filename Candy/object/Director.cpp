//
//  Director.cpp
//  Candy
//
//  Created by Dongyang.Cai on 22/10/2016.
//
//

#include "assert.h"

#include "object/Director.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

Director* Director::s_director = nullptr;

Director* Director::getInstance()
{
    if (!s_director) {
        s_director = new (std::nothrow) Director;
        
        assert(s_director);
    }
    
    return s_director;
}

Director::Director()
: _glview(nullptr)
{
}

Director::~Director()
{
    
}

void Director::setOpenGLView(GLView *view)
{
    assert(view);
    
    if (_glview != view) {
        DY_SAFE_RELEASE(_glview);
        _glview = view;
    }
}

NS_OBJECT_END

NS_DY_END
