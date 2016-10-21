//
//  ApplicationDelegate.cpp
//  Candy_Samples
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#include "ApplicationDelegate.h"

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
    
    auto glview = GLView::create("Candy", candy::Rect(0, 0, 640, 480));
    glview->setDesignResolutionSize(640, 480, ResolutionPolicy::NO_BORDER);
    
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
