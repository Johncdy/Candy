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

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Director: public Ref {
public:
    
    /**
     Returns a shared instance of the director.

     @return _getInstance
     */
    static Director* getInstance();
    
    /**
     Sets the GLView.
     */
    void setOpenGLView(GLView* view);
    
    /**
     Get the GLView.

     @return GLView
     */
    GLView* getOpenGLView() { return _glview; }
    
private:
    
    Director();
    
    virtual ~Director();
    
    // Director instance
    static Director* s_director;
    // GLview
    GLView* _glview;
};

NS_OBJECT_END

NS_DY_END

#endif /* Director_h */
