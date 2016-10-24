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

ApplicationDelegate::ApplicationDelegate()
{
}

ApplicationDelegate::~ApplicationDelegate()
{
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
    auto glview = GLView::create("Candy", NS_MATH::Rect(0, 0, 640, 480));
    director->setOpenGLView(glview);
    
    glview->setDesignResolutionSize(640, 480, ResolutionPolicy::NO_BORDER);
    
    auto samples = new (std::nothrow) SamplesFramework;
    samples->init();
    
    return true;
}

bool ApplicationDelegate::start()
{
    return true;
}

bool ApplicationDelegate::stop()
{
    return true;
}

bool ApplicationDelegate::resume()
{
    return true;
}

bool ApplicationDelegate::end()
{
    return true;
}
