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

#include "math/math.h"
#include "memory/Ref.h"

#include "glfw3.h"

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
