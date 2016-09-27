//
//  Application_Mac.cpp
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#include "platform/PlatformConfig.h"

#if DY_TARGET_PLATFORM == DY_PLATFORM_MAC

#include "platform/Application.h"

#include "glfw3.h"

#include <assert.h>

NS_DY_BEGIN

Application* Application::s_application = nullptr;

Application::Application()
{
    assert(!s_application);
    s_application = this;
}

Application::~Application()
{
    assert(s_application == this);
    s_application = 0;
}

Application* Application::getInstance()
{
    assert(s_application);
    return s_application;
}

int Application::run()
{
    
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

NS_DY_END

#endif
