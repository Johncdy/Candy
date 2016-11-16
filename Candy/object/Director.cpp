//
//  Director.cpp
//  Candy
//
//  Created by Dongyang.Cai on 22/10/2016.
//
//

#include "assert.h"

#include "object/Director.h"
#include "object/PoolManager.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

Director* Director::s_director = nullptr;

Director* Director::getInstance()
{
    if (!s_director) {
        s_director = new (std::nothrow) Director;
        
        assert(s_director);
        s_director->init();
    }
    
    return s_director;
}

void Director::destroyInstance()
{
    DY_SAFE_DELETE(s_director);
}

Director::Director()
: _glview(nullptr)
{
}

Director::~Director()
{
    DY_SAFE_DELETE(_renderer);
    
    s_director = nullptr;
}

void Director::init()
{
    // Delta time init.
    _deltaTime = 0;
    _isDeltaZero = false;
    _lastUpdateTime = std::chrono::steady_clock::now();
    
    _renderer = new (std::nothrow) renderer::Renderer;
}

void Director::setOpenGLView(GLView *view)
{
    assert(view);
    
    if (_glview != view) {
        DY_SAFE_RELEASE(_glview);
        
        _glview = view;
        _glview->retain();
    }
}

void Director::mainLoop()
{
    draw();
    
    PoolManager::getInstance()->getDefaultPool()->clear();
}

void Director::draw()
{
    calculateDeltaTime();
    
    if (_glview) {
        _glview->pollEvents();
    }
    
    
    
//    _renderer->clear();
    
    if (_glview) {
        _glview->swapBuffers();
    }
}

void Director::calculateDeltaTime()
{
    auto now = std::chrono::steady_clock::now();
    
    if (_isDeltaZero) {
        _deltaTime = 0;
        _isDeltaZero = false;
    } else {
        _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdateTime).count() / 1000000.0f;
        _deltaTime = MAX(0, _deltaTime);
    }
    
    _lastUpdateTime = now;
}

void Director::resume()
{
    _deltaTime = 0;
    _isDeltaZero = true;
}

NS_OBJECT_END

NS_DY_END
