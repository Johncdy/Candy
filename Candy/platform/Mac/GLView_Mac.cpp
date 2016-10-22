//
//  GLView_Mac.cpp
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#include "assert.h"
#include "math.h"

#include "platform/Mac/GLView_Mac.h"
#include "platform/Mac/GLFWEventHandler.h"

NS_DY_BEGIN

NS_MATH_USE

#define drawOneLine(x1, y1, x2, y2) glBegin(GL_LINES); \
glVertex2f((x1), (y1)); glVertex2f((x2), (y2)); glEnd();

//default context attributions are set as follows
GLContextAttrs GLView::_glContextAttrs = {5, 6, 5, 0, 16, 0};

void GLView::setGLConextAttrs(candy::GLContextAttrs &attrs)
{
    _glContextAttrs = attrs;
}

GLContextAttrs GLView::getContextAttrs()
{
    return _glContextAttrs;
}

GLView::GLView()
: _viewName("")
, _frameSize(Size(0, 0))
, _frameZoomFactor(1.0f)
, _window(nullptr)
, _monitor(nullptr)
, _isRetinaEnabled(false)
, _retinaFactor(1)
, _isInRetinaMonitor(false)
, _resolutionPolicy(ResolutionPolicy::UNKNOWN)
, _designResolutionSize(Size(0, 0))
, _viewPort(Rect(0, 0, 0, 0))
{
}

GLView::~GLView()
{
    printf("deallocing GLViewImpl: %p", this);
    GLFWEventHandler::setGLView(nullptr);
    glfwTerminate();
}

GLView* GLView::create(const std::string &viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    auto view = new (std::nothrow) GLView;
    if (view && view->init(viewName, rect, frameZoomFactor, resizable)) {
        view->autoRelease();
        return view;
    }
    DY_SAFE_DELETE(view);
    return nullptr;
}

bool GLView::init(const std::string &viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    _viewName = viewName;
    _frameZoomFactor = frameZoomFactor;
    
    glfwSetErrorCallback(GLFWEventHandler::onGLFWError);
    
    /* Initialize the library */
    if (!glfwInit()) return false;
    
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_RED_BITS, _glContextAttrs.redBits);
    glfwWindowHint(GLFW_GREEN_BITS, _glContextAttrs.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, _glContextAttrs.blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS, _glContextAttrs.alphaBits);
    glfwWindowHint(GLFW_DEPTH_BITS, _glContextAttrs.depthBits);
    glfwWindowHint(GLFW_STENCIL_BITS, _glContextAttrs.stencilBits);
    
    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(rect._size._width * _frameZoomFactor, rect._size._height * _frameZoomFactor, viewName.c_str(), _monitor, NULL);
    if (!_window)
    {
        glfwTerminate();
        printf("Can't create window");
        return false;
    }
    
    /*
     *  Note that the created window and context may differ from what you requested,
     *  as not all parameters and hints are
     *  [hard constraints](@ref window_hints_hard).  This includes the size of the
     *  window, especially for full screen windows.  To retrieve the actual
     *  attributes of the created window and context, use queries like @ref
     *  glfwGetWindowAttrib and @ref glfwGetWindowSize.
     *
     *  see declaration glfwCreateWindow
     */
    int realW = 0, realH = 0;
    glfwGetWindowSize(_window, &realW, &realH);
    if (realW != rect._size._width * _frameZoomFactor)
    {
        rect._size._width = realW / _frameZoomFactor;
    }
    if (realH != rect._size._height * _frameZoomFactor)
    {
        rect._size._height = realH / _frameZoomFactor;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(_window);
    
    // Set glfw callback.
    glfwSetMouseButtonCallback(_window, GLFWEventHandler::onGLFWMouseCallBack);
    glfwSetCursorPosCallback(_window, GLFWEventHandler::onGLFWMouseMoveCallBack);
    glfwSetScrollCallback(_window, GLFWEventHandler::onGLFWMouseScrollCallback);
    glfwSetCharCallback(_window, GLFWEventHandler::onGLFWCharCallback);
    glfwSetKeyCallback(_window, GLFWEventHandler::onGLFWKeyCallback);
    glfwSetWindowPosCallback(_window, GLFWEventHandler::onGLFWWindowPosCallback);
    glfwSetFramebufferSizeCallback(_window, GLFWEventHandler::onGLFWFrameBufferSize);
    glfwSetWindowSizeCallback(_window, GLFWEventHandler::onGLFWWindowSizeFunCallback);
    glfwSetWindowIconifyCallback(_window, GLFWEventHandler::onGLFWWindowIconifyCallback);
    glfwSetWindowFocusCallback(_window, GLFWEventHandler::onGLFWWindowFocusCallback);
    
    setFrameSize(rect._size._width, rect._size._height);
    
    return true;
}

void GLView::setFrameSize(float width, float height)
{
    assert(width != 0 && height != 0);
    
    _frameSize._width = width;
    _frameSize._height = height;
    
    int window_w = 0, window_h = 0;
    glfwGetWindowSize(_window, &window_w, &window_h);
    
    int frame_w = 0, frame_h = 0;
    glfwGetFramebufferSize(_window, &frame_w, &frame_h);
    
    if (2 * window_w == frame_w && 2 * window_h == frame_h) {
        _isInRetinaMonitor = true;
        _retinaFactor = _isRetinaEnabled ? 1 : 2;
        glfwSetWindowSize(_window, _frameSize._width / 2 * _retinaFactor, _frameSize._height / 2 * _retinaFactor);
    } else {
        _isInRetinaMonitor = false;
        glfwSetWindowSize(_window, _frameSize._width, _frameSize._height);
    }
}

void GLView::setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy)
{
    assert(resolutionPolicy != ResolutionPolicy::UNKNOWN);
    assert(width != 0 && height != 0 && _frameSize._width != 0 && _frameSize._height != 0);
    
    _resolutionPolicy = resolutionPolicy;
    
    _designResolutionSize._width = width;
    _designResolutionSize._height = height;
    
    _scaleX = _frameSize._width / _designResolutionSize._width;
    _scaleY = _frameSize._height / _designResolutionSize._height;
    
    if (ResolutionPolicy::NO_BORDER == _resolutionPolicy) {
        _scaleX = _scaleY = MAX(_scaleX, _scaleY);
    } else if (ResolutionPolicy::SHOW_ALL == _resolutionPolicy) {
        _scaleX = _scaleY = MIN(_scaleX, _scaleY);
    } else if (ResolutionPolicy::FIXED_HEIGHT == _resolutionPolicy) {
        _scaleX = _scaleY;
        _designResolutionSize._width = ceilf(_frameSize._width / _scaleX);
    } else if (ResolutionPolicy::FIXED_WIDTH == _resolutionPolicy) {
        _scaleY = _scaleX;
        _designResolutionSize._height = ceilf(_frameSize._height / _scaleY);
    }
    
    float _viewW = _designResolutionSize._width * _scaleX;
    float _viewH = _designResolutionSize._height * _scaleY;
    
    _viewPort.set(0, 0, _viewW, _viewH);
    
    glViewport(0, 0, _frameSize._width, _frameSize._height);
}

bool GLView::windowShouldClose()
{
    if (_window) {
        return glfwWindowShouldClose(_window) ? true : false;
    } else {
        return true;
    }
}

void GLView::swapBuffers()
{
    if (_window) {
        glfwSwapBuffers(_window);
    }
}

void GLView::pollEvents()
{
    glfwPollEvents();
}

void GLView::onGLFWError(int errorID, const char* errorDesc)
{
    printf("GLFWError #%d Happen, %s\n", errorID, errorDesc);
}

void GLView::onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{
    
}

void GLView::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{
    
}

void GLView::onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
{
    
}

void GLView::onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
}

void GLView::onGLFWCharCallback(GLFWwindow* window, unsigned int character)
{
    
}

void GLView::onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
{
    
}

void GLView::onGLFWframebuffersize(GLFWwindow* window, int w, int h)
{
    
}

void GLView::onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
{
    
}

void GLView::onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
{
    
}

void GLView::onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
{
    
}

NS_DY_END
