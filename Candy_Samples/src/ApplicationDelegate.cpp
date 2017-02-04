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
    auto glview = GLView::create("Candy", NS_MATH::Rect(0, 0, 1280, 720));
    director->setOpenGLView(glview);
    
    glview->setWindowSize(1280, 720, ResolutionPolicy::NO_BORDER);
    
//    s_samples = new (std::nothrow) SamplesFramework;
//    s_samples->init();
    auto scene = SamplesFramework::scene();
    director->runWithScene(scene);
    
    return true;
}

bool ApplicationDelegate::start()
{
    return true;
}

bool ApplicationDelegate::update()
{
    SamplesFramework::getInstance()->renderSingleFrame(static_cast<float>(_elapsedTime));
    
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
