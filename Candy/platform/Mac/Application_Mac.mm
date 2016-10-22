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
    
    while (!glview->windowShouldClose())
    {
        /* Draw a triangle */
        glBegin(GL_TRIANGLES);
        
        glColor3f(1.0, 0.0, 0.0);    // Red
        glVertex3f(0.0, 1.0, 0.0);
        
        glColor3f(0.0, 1.0, 0.0);    // Green
        glVertex3f(-1.0, -1.0, 0.0);
        
        glColor3f(0.0, 0.0, 1.0);    // Blue
        glVertex3f(1.0, -1.0, 0.0);
        
        glEnd();
        
        glview->swapBuffers();
        glview->pollEvents();
    }
    
    return 0;
}

NS_DY_END

#endif
