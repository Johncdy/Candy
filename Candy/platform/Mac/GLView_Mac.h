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

#include "external/glfw3/mac/include/glfw3.h"
#ifndef GLFW_EXPOSE_NATIVE_NSGL
#define GLFW_EXPOSE_NATIVE_NSGL
#endif
#ifndef GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include "external/glfw3/mac/include/glfw3native.h"

NS_DY_BEGIN

/** There are some Resolution Policy for Adapt to the screen. */
enum class ResolutionPolicy
{
    /** The entire application is visible in the specified area without trying to preserve the original aspect ratio.
     * Distortion can occur, and the application may appear stretched or compressed.
     */
    EXACT_FIT,
    /** The entire application fills the specified area, without distortion but possibly with some cropping,
     * while maintaining the original aspect ratio of the application.
     */
    NO_BORDER,
    /** The entire application is visible in the specified area without distortion while maintaining the original
     * aspect ratio of the application. Borders can appear on two sides of the application.
     */
    SHOW_ALL,
    /** The application takes the height of the design resolution size and modifies the width of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_HEIGHT,
    /** The application takes the width of the design resolution size and modifies the height of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_WIDTH,
    
    UNKNOWN,
};

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
    
    /**
     Set the frame size of window(the extents of window).

     @param width  frame width
     @param height frame height
     */
    void setFrameSize(float width, float height);
    
    /**
     * Set the design resolution size.
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired, you may choose:
     *                         [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to height is different from the screen resolution ratio, your game view will be stretched.
     *                         [2] NO_BORDER Full screen without black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two areas of your game view will be cut.
     *                         [3] SHOW_ALL  Full screen with black border: if the design resolution ratio of width to height is different from the screen resolution ratio, two black borders will be shown.
     */
    void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);
    
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
    // The extents of window size.
    Size _frameSize;
    // Is enable retina model.
    bool _isRetinaEnabled;
    // Retina zoom factor
    int _retinaFactor;
    // Is in retina monitor.
    bool _isInRetinaMonitor;
    
    // Resolution Policy.
    ResolutionPolicy _resolutionPolicy;
    // resolution size, it is the size appropriate for the app resources.
    Size _designResolutionSize;
    // Frame size width / design size width.
    float _scaleX;
    // Frame size height / design size height.
    float _scaleY;
    // View port.
    Rect _viewPort;
    
    // Opaque window object.
    GLFWwindow *_window;
    // Opaque monitor object.
    GLFWmonitor *_monitor;
};

NS_DY_END

#endif /* GLView_Mac_h */
