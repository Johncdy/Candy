//
//  Director.h
//  Candy
//
//  Created by Dongyang.Cai on 22/10/2016.
//
//

#ifndef Director_h
#define Director_h

#include "object/Ref.h"
#include "platform/Mac/GLView_Mac.h"

#include <chrono>

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Director: public Ref {
public:
    
    /**
     Returns a shared instance of the director.

     @return _getInstance
     */
    static Director* getInstance();
    
    void init();
    
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
    
private:
    
    Director();
    
    virtual ~Director();
    
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
};

NS_OBJECT_END

NS_DY_END

#endif /* Director_h */
