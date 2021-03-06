//
//  Director.h
//  Candy
//
//  Created by Dongyang.Cai on 22/10/2016.
//
//

#ifndef Director_h
#define Director_h

#include "platform/Mac/GLView_Mac.h"
#include "object/Scene.h"
#include "math/math.h"

#include <stack>
#include <chrono>

NS_DY_BEGIN

NS_OBJECT_BEGIN

enum class MATRIX_STACK_TYPE
{
    /// Model view matrix stack
    MATRIX_STACK_MODELVIEW,
    
    /// projection matrix stack
    MATRIX_STACK_PROJECTION,
    
    /// texture matrix stack
    MATRIX_STACK_TEXTURE
};

class Director: public Ref {
public:
    
    enum class Projection {
        /// Sets a 2D projection (orthogonal projection).
        _2D,
        
        /// Sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
        _3D,
        
        /// It calls "updateProjection" on the projection delegate.
        CUSTOM,
        
        DEFAULT = _3D,
    };
    
    /**
     Returns a shared instance of the director.

     @return _getInstance
     */
    static Director* getInstance();
    
    /**
     Delete director manager singleton.
     */
    static void destroyInstance();
    
    bool init();
    
    /**
     Sets the GLView.
     */
    void setOpenGLView(GLView* view);
    
    /**
     Get the GLView.

     @return GLView
     */
    GLView* getOpenGLView() { return _glview; }
    
    /**
     * Clones a specified type matrix and put it to the top of specified type of matrix stack.
     * @js NA
     */
    void pushMatrix(MATRIX_STACK_TYPE type);
    
    /** Pops the top matrix of the specified type of matrix stack.
     * @js NA
     */
    void popMatrix(MATRIX_STACK_TYPE type);
    
    /** Adds an identity matrix to the top of specified type of matrix stack.
     * @js NA
     */
    void loadIdentityMatrix(MATRIX_STACK_TYPE type);
    
    /**
     * Adds a matrix to the top of specified type of matrix stack.
     *
     * @param type Matrix type.
     * @param mat The matrix that to be added.
     * @js NA
     */
    void loadMatrix(MATRIX_STACK_TYPE type, const math::Mat4& mat);
    
    /**
     * Multiplies a matrix to the top of specified type of matrix stack.
     *
     * @param type Matrix type.
     * @param mat The matrix that to be multiplied.
     * @js NA
     */
    void multiplyMatrix(MATRIX_STACK_TYPE type, const math::Mat4& mat);
    
    /**
     * Gets the top matrix of specified type of matrix stack.
     * @js NA
     */
    const math::Mat4& getMatrix(MATRIX_STACK_TYPE type) const;
    
    /**
     * Clear all types of matrix stack, and add identity matrix to these matrix stacks.
     * @js NA
     */
    void resetMatrixStack();
    
    Projection getProjection() { return _projection; }
    
    void setProjection(Projection projection);
    
    /** Enables/disables OpenGL alpha blending. */
    void setAlphaBlending(bool on);
    
    /**
     Returns the size of the OpenGL view in points.

     @return The size of the opengl view in points.
     */
    const math::Size& getWinSize() const;
    
    /**
     Returns the size of the OpenGL view in pixels.

     @return The size of the OpenGL view in pixels.
     */
    math::Size getWinSizeInPixels() const;
    
    /** The size in pixels of the surface. It could be different than the screen size.
     * High-res devices might have a higher surface size than the screen size.
     * Only available when compiled using SDK >= 4.0.
     * @since v0.99.4
     */
    void setContentScaleFactor(float scaleFactor);
    /**
     * Gets content scale factor.
     * @see Director::setContentScaleFactor()
     */
    float getContentScaleFactor() const { return _contentScaleFactor; }
    
    /**
     Background main loop.
     */
    void mainLoop();
    
    /**
     Draw function.
     */
    void draw();
    
    /**
     Calculates delta time since last time it was called.
     */
    void calculateDeltaTime();
    
    /**
     Resumes the paused scene.
     The scheduled timers will be activated again.
     The "delta time" will be 0 (as if the game wasn't paused).
     */
    void resume();
    
    /**
     Draw the scene.
     This method is called every frame. Don't call it manually.
     */
    void drawScene();
    
    /**
     Enters the Director's main loop with the given Scene.

     @param scene candy object Scene
     */
    void runWithScene(Scene* scene);
    
private:
    
    DY_CONSTRUCTOR_FUNC(Director);
    
    /**
     Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
     
     @param scene candy object Scene.
     */
    void pushScene(Scene* scene);
    
    /**
     Pops out a scene from the stack.
     This scene will replace the running one.
     */
    void popScene();
    
    // Director instance
    static Director* s_director;
    // GLview
    GLView* _glview;
    
    // Delta time since last tick to main loop
    float _deltaTime;
    // Whether or not the next delta time will be zero.
    bool _isDeltaZero;
    // Last time the main loop was updated.
    std::chrono::steady_clock::time_point _lastUpdateTime;
    
    // Renderer for the director.
    renderer::Renderer* _renderer;
    
    std::stack<math::Mat4> _modelViewMatrixStack;
    std::stack<math::Mat4> _projectionMatrixStack;
    std::stack<math::Mat4> _textureMatrixStack;
    
    // projection used
    Projection _projection;
    // window size in points
    math::Size _winSizeInPoints;
    // content scale factor
    float _contentScaleFactor;
    
    // The running scene
    Scene* _runningScene;
    // Scheduled scenes
    std::stack<Scene*> _sceneStack;
    // Is scene change
    bool _isSceneChanged;
};

NS_OBJECT_END

NS_DY_END

#endif /* Director_h */
