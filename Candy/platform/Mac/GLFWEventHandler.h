//
//  GLFWEventHandler.h
//  Candy
//
//  Created by Dongyang.Cai on 18/10/2016.
//
//

#ifndef GLFWEventHandler_h
#define GLFWEventHandler_h

#include "platform/Mac/GLView_Mac.h"

NS_DY_BEGIN

class GLFWEventHandler {
public:
    // GLFW callbacks.
    static void onGLFWError(int errorID, const char* errorDesc);
    
    static void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    
    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    
    static void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
    
    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    
    static void onGLFWFrameBufferSize(GLFWwindow* window, int w, int h);
    
    static void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
    
    static void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
    
    static void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified);
    
    static void onGLFWWindowFocusCallback(GLFWwindow* window, int focused);
    
    static void setGLView(GLView* view);
    
private:
    static GLView* _view;
};

NS_DY_END

#endif /* GLFWEventHandler_h */
