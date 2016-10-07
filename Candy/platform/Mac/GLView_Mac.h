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

NS_DY_BEGIN

class GLView {
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
    
    
};

NS_DY_END

#endif /* GLView_Mac_h */
