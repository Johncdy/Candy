//
//  Application_Mac.cpp
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#include "platform/PlatformMacros.h"
#include "object/Director.h"

#if DY_TARGET_PLATFORM == DY_PLATFORM_MAC

#include "platform/Application.h"
#include "platform/Mac/GLView_Mac.h"

#include <assert.h>

NS_DY_BEGIN

double Application::_frameTime = 0;
double Application::_elapsedTime = 0;

Application::Application()
{
}

Application::~Application()
{
}

int Application::run()
{
    if (!init()) {
        return 1;
    }
    
    auto director = object::Director::getInstance();
    auto glview = director->getOpenGLView();
    
    // set starting time
    _frameTime = glfwGetTime();
    
    while (!glview->windowShouldClose())
    {
        /* Draw a triangle */
//        glBegin(GL_TRIANGLES);
//        
//        glColor3f(1.0, 0.0, 0.0);    // Red
//        glVertex3f(0.0, 1.0, 0.0);
//        
//        glColor3f(0.0, 1.0, 0.0);    // Green
//        glVertex3f(-1.0, -1.0, 0.0);
//        
//        glColor3f(0.0, 0.0, 1.0);    // Blue
//        glVertex3f(1.0, -1.0, 0.0);
//        
//        glEnd();
        glClear(GL_COLOR_BUFFER_BIT);
        
        // calculate time elapsed since last frame
        double time_now = glfwGetTime();
        _elapsedTime = time_now - _frameTime;
        _frameTime = time_now;
        
        update();
        
        director->mainLoop();
    }
    
    glview->release();
    
    return 0;
}

bool Application::init()
{
    return true;
}

bool Application::start()
{
    return true;
}

bool Application::update()
{
    return true;
}

bool Application::stop()
{
    return true;
}

bool Application::resume()
{
    object::Director::getInstance()->resume();
    
    return true;
}

bool Application::end()
{
    return false;
}

NS_DY_END

#endif
