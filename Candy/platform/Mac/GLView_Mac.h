//
//  GLView_Mac.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef GLView_Mac_h
#define GLView_Mac_h

#include <stdio.h>
#include <string>

#include "math/Rect.h"
#include "memory/Ref.h"

#include "glfw3.h"
#ifndef GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_NSGL
#endif
#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "glfw3native.h"

NS_DY_BEGIN


/**
 There are opengl Context Attrs.
 */
struct GLContextAttrs
{
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
};

class GLView : public Ref {
public:
    /**
     GLView ctor.
     */
    GLView();
    
    /**
     GLView dtor.
     */
    virtual ~GLView();
    
    /**
     GLView build function.

     @param viewName        View Name.
     @param rect            View rect size.
     @param frameZoomFactor Frame zoom factor.
     @param resizable View  resizable.

     @return GLView.
     */
    static GLView *create(const std::string& viewName, Rect rect, float frameZoomFactor = 1.0f, bool resizable = false);
    
    /**
     GLView init function.
     
     @param viewName        View Name.
     @param rect            View rect size.
     @param frameZoomFactor Frame zoom factor.
     @param resizable View  resizable.
     
     @return bool.
     */
    bool init(const std::string& viewName, Rect rect, float frameZoomFactor, bool resizable);
    
    /**
     Static method and member so that we can modify it on all platforms before create OpenGL context.

     @param attrs The OpenGL context attrs.
     */
    static void setGLConextAttrs(GLContextAttrs& attrs);
    
    /**
     Return the OpenGL context attrs.

     @return Return the OpenGL context attrs.
     */
    static GLContextAttrs getContextAttrs();
    
    // The OpenGL context attrs.
    static GLContextAttrs _glContextAttrs;
    
    // GLFWEventHandler callbacks
    void onGLFWError(int errorID, const char* errorDesc);
    
    void onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify);
    
    void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    
    void onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y);
    
    void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    
    void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    
    void onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y);
    
    void onGLFWframebuffersize(GLFWwindow* window, int w, int h);
    
    void onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height);
    
    void onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified);
    
    void onGLFWWindowFocusCallback(GLFWwindow* window, int focused);
    
private:
    // View name.
    std::string _viewName;
    // Frame zoom factor.
    float _frameZoomFactor;
    
    // Opaque window object.
    GLFWwindow *_window;
    // Opaque monitor object.
    GLFWmonitor *_monitor;
};

NS_DY_END

#endif /* GLView_Mac_h */
