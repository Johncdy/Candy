//
//  GLFWEventHandler.cpp
//  Candy
//
//  Created by Dongyang.Cai on 18/10/2016.
//
//

#include "platform/Mac/GLFWEventHandler.h"

NS_DY_BEGIN

GLView* GLFWEventHandler::_view = nullptr;

void GLFWEventHandler::onGLFWError(int errorID, const char* errorDesc)
{
    if (_view) {
        _view->onGLFWError(errorID, errorDesc);
    }
}

void GLFWEventHandler::onGLFWMouseCallBack(GLFWwindow* window, int button, int action, int modify)
{
    if (_view) {
        _view->onGLFWMouseCallBack(window, button, action, modify);
    }
}

void GLFWEventHandler::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{
    if (_view) {
        _view->onGLFWMouseMoveCallBack(window, x, y);
    }
}

void GLFWEventHandler::onGLFWMouseScrollCallback(GLFWwindow* window, double x, double y)
{
    if (_view) {
        _view->onGLFWMouseScrollCallback(window, x, y);
    }
}

void GLFWEventHandler::onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (_view) {
        _view->onGLFWKeyCallback(window, key, scancode, action, mods);
    }
}

void GLFWEventHandler::onGLFWCharCallback(GLFWwindow* window, unsigned int character)
{
    if (_view) {
        _view->onGLFWCharCallback(window, character);
    }
}

void GLFWEventHandler::onGLFWFrameBufferSize(GLFWwindow* window, int w, int h)
{
    if (_view) {
        _view->onGLFWframebuffersize(window, w, h);
    }
}

void GLFWEventHandler::onGLFWWindowPosCallback(GLFWwindow* windows, int x, int y)
{
    if (_view) {
        _view->onGLFWWindowPosCallback(windows, x, y);
    }
}

void GLFWEventHandler::onGLFWWindowSizeFunCallback(GLFWwindow *window, int width, int height)
{
    if (_view) {
        _view->onGLFWWindowSizeFunCallback(window, width, height);
    }
}

void GLFWEventHandler::onGLFWWindowIconifyCallback(GLFWwindow* window, int iconified)
{
    if (_view) {
        _view->onGLFWWindowIconifyCallback(window, iconified);
    }
}

void GLFWEventHandler::onGLFWWindowFocusCallback(GLFWwindow* window, int focused)
{
    if (_view) {
        _view->onGLFWWindowFocusCallback(window, focused);
    }
}

void GLFWEventHandler::setGLView(GLView* view)
{
    _view = view;
}

NS_DY_END
