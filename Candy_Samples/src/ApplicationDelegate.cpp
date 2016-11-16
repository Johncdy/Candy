//
//  ApplicationDelegate.cpp
//  Candy_Samples
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#include "ApplicationDelegate.h"
#include "SamplesFramework.h"

#include "object/Director.h"

NS_DY_USE

static SamplesFramework* s_samples;

ApplicationDelegate::ApplicationDelegate()
{
}

ApplicationDelegate::~ApplicationDelegate()
{
    DY_SAFE_DELETE(s_samples);
}

void ApplicationDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLConextAttrs(glContextAttrs);
}

bool ApplicationDelegate::init()
{
    initGLContextAttrs();
    
    auto director = object::Director::getInstance();
    auto glview = GLView::create("Candy", NS_MATH::Rect(0, 0, 1024, 768));
    director->setOpenGLView(glview);
    
    glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
    
    s_samples = new (std::nothrow) SamplesFramework;
    s_samples->init();
    
    return true;
}

bool ApplicationDelegate::start()
{
    return true;
}

bool ApplicationDelegate::update()
{
    s_samples->renderSingleFrame(static_cast<float>(_elapsedTime));
    
    return true;
}

bool ApplicationDelegate::stop()
{
    return true;
}

bool ApplicationDelegate::resume()
{
    Application::resume();
    
    return true;
}

bool ApplicationDelegate::end()
{
    return true;
}
