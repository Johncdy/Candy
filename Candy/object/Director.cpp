//
//  Director.cpp
//  Candy
//
//  Created by Dongyang.Cai on 22/10/2016.
//
//

#include "assert.h"

#include "math/MathMacros.h"

#include "object/Director.h"
#include "object/PoolManager.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

Director* Director::s_director = nullptr;

Director* Director::getInstance()
{
    if (nullptr == s_director) {
        s_director = new (std::nothrow) Director;
        
        assert(s_director);
        s_director->init();
    }
    
    return s_director;
}

void Director::destroyInstance()
{
    DY_SAFE_DELETE(s_director);
}

Director::Director()
: _glview(nullptr)
, _runningScene(nullptr)
, _isSceneChanged(false)
{
}

Director::~Director()
{
    DY_SAFE_DELETE(_renderer);
    
    s_director = nullptr;
}

void Director::init()
{
    // Delta time init.
    _deltaTime = 0;
    _isDeltaZero = false;
    _lastUpdateTime = std::chrono::steady_clock::now();
    
    _winSizeInPoints = math::Size::ZERO;
    _contentScaleFactor = 1.0f;
    
    resetMatrixStack();
    
    _renderer = new (std::nothrow) renderer::Renderer;
}

void Director::setOpenGLView(GLView *view)
{
    assert(view);
    
    if (_glview != view) {
        DY_SAFE_RELEASE(_glview);
        
        _glview = view;
        _glview->retain();
        
        _winSizeInPoints = _glview->getWindowSize();
    }
}

void Director::pushMatrix(candy::object::MATRIX_STACK_TYPE type)
{
    if (MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type) {
        _modelViewMatrixStack.push(_modelViewMatrixStack.top());
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type) {
        _projectionMatrixStack.push(_projectionMatrixStack.top());
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type) {
        _textureMatrixStack.push(_textureMatrixStack.top());
    }
    
    printf("Unknown matrix stack type");
}

void Director::popMatrix(candy::object::MATRIX_STACK_TYPE type)
{
    if (MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type) {
        _modelViewMatrixStack.pop();
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type) {
        _projectionMatrixStack.pop();
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type) {
        _textureMatrixStack.pop();
    }
    
    printf("Unknown matrix stack type");
}

void Director::loadIdentityMatrix(candy::object::MATRIX_STACK_TYPE type)
{
    if (MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type) {
        _modelViewMatrixStack.top() = math::Mat4::IDENTITY;
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type) {
        _projectionMatrixStack.top() = math::Mat4::IDENTITY;
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type) {
        _textureMatrixStack.top() = math::Mat4::IDENTITY;
    }
    
    printf("Unknown matrix stack type");
}

void Director::loadMatrix(candy::object::MATRIX_STACK_TYPE type, const math::Mat4 &mat)
{
    if (MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type) {
        _modelViewMatrixStack.top() = mat;
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type) {
        _projectionMatrixStack.top() = mat;
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type) {
        _textureMatrixStack.top() = mat;
    }
    
    printf("Unknown matrix stack type");
}

void Director::multiplyMatrix(candy::object::MATRIX_STACK_TYPE type, const math::Mat4 &mat)
{
    if (MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW == type) {
        _modelViewMatrixStack.top() *= mat;
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION == type) {
        _projectionMatrixStack.top() *= mat;
    } else if (MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE == type) {
        _textureMatrixStack.top() *= mat;
    }
    
    printf("Unknown matrix stack type");
}

const math::Mat4& Director::getMatrix(candy::object::MATRIX_STACK_TYPE type) const
{
    if (type == MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW) {
        return _modelViewMatrixStack.top();
    } else if (type == MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION) {
        return _projectionMatrixStack.top();
    } else if (type == MATRIX_STACK_TYPE::MATRIX_STACK_TEXTURE) {
        return _textureMatrixStack.top();
    }
    
    printf("Unknown matrix stack type");
    return math::Mat4::ZERO;
}

void Director::resetMatrixStack()
{
    while (!_modelViewMatrixStack.empty()) {
        _modelViewMatrixStack.pop();
    }
    
    while (!_projectionMatrixStack.empty()) {
        _projectionMatrixStack.pop();
    }
    
    while (!_textureMatrixStack.empty()) {
        _textureMatrixStack.pop();
    }
    
    _modelViewMatrixStack.push(math::Mat4::IDENTITY);
    _projectionMatrixStack.push(math::Mat4::IDENTITY);
    _textureMatrixStack.push(math::Mat4::IDENTITY);
}

void Director::setProjection(candy::object::Director::Projection projection)
{
    math::Size size = _winSizeInPoints;
    
    if (_glview) {
        _glview->setViewPortInPoints(0, 0, size._width, size._height);
    }
    
    switch (projection) {
        case Projection::_2D:
        {
            math::Mat4 orthoMatrix;
            math::Mat4::createOrthographicOffCenter(0, size._width, 0, size._height, -1024, 1024, &orthoMatrix);
            
            loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
            break;
        }
        case Projection::_3D:
        {
            float zeye = _winSizeInPoints._height / 1.1566f;
            
            math::Mat4 matrixPerspective, matrixLookup;
            
            math::Mat4::createPerspective(60, size._width/size._height, 10, zeye+size._height/2, &matrixPerspective);
            math::Vec3 eye(size._width/2, size._height/2, zeye), center(size._width/2, size._height/2, 0.f), up(0.f, 1.0f, 0.f);
            math::Mat4::createLookAt(eye, center, up, &matrixLookup);
            math::Mat4 proj3d = matrixPerspective * matrixLookup;
            
            loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, proj3d);
            loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
        }
        case Projection::CUSTOM:
            break;
        default:
            printf("Director: unrecognized projection");
            break;
    }
}

void Director::setAlphaBlending(bool on)
{
    if (on) {
//        GL::blend
    }
}

const math::Size& Director::getWinSize() const
{
    return _winSizeInPoints;
}

math::Size Director::getWinSizeInPixels() const
{
    return math::Size(_winSizeInPoints._width * _contentScaleFactor, _winSizeInPoints._height * _contentScaleFactor);
}

void Director::setContentScaleFactor(float scaleFactor)
{
    if (scaleFactor != _contentScaleFactor) {
        _contentScaleFactor = scaleFactor;
    }
}

void Director::mainLoop()
{
    draw();
    
    PoolManager::getInstance()->getDefaultPool()->clear();
}

void Director::draw()
{
    calculateDeltaTime();
    
    if (_glview) {
        _glview->pollEvents();
    }
    
    drawScene();
    
    if (_glview) {
        _glview->swapBuffers();
    }
}

void Director::calculateDeltaTime()
{
    auto now = std::chrono::steady_clock::now();
    
    if (_isDeltaZero) {
        _deltaTime = 0;
        _isDeltaZero = false;
    } else {
        _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdateTime).count() / 1000000.0f;
        _deltaTime = MAX(0, _deltaTime);
    }
    
    _lastUpdateTime = now;
}

void Director::resume()
{
    _deltaTime = 0;
    _isDeltaZero = true;
}

/*********************************/
// Scene management
/*********************************/

/**
 Draw the scene.
 This method is called every frame. Don't call it manually.
 */
void Director::drawScene()
{
//    _renderer->clear();
    
    if (_isSceneChanged) {
        _isSceneChanged = false;
        
        if (_runningScene) {
            _runningScene->release();
            _runningScene = nullptr;
        }
        _runningScene = _sceneStack.top();
    }
}

/**
 Enters the Director's main loop with the given Scene.
 
 @param scene candy object Scene
 */
void Director::runWithScene(candy::object::Scene *scene)
{
    DY_ASSERT(scene != nullptr && _runningScene == nullptr);
    
    pushScene(scene);
    scene->retain();
}

/**
 Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
 
 @param scene candy object Scene.
 */
void Director::pushScene(Scene* scene)
{
    DY_ASSERT(scene != nullptr);
    
    _sceneStack.push(scene);
    _isSceneChanged = true;
}

/**
 Pops out a scene from the stack.
 This scene will replace the running one.
 */
void Director::popScene()
{
    DY_ASSERT(_runningScene != nullptr);
    
    _sceneStack.pop();
}

NS_OBJECT_END

NS_DY_END
