//
//  ApplicationDelegate.h
//  Candy_Samples
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef ApplicationDelegate_h
#define ApplicationDelegate_h

#include "include/Candy.h"

class ApplicationDelegate : public NS_DY::Application {
public:
    
    ApplicationDelegate();
    
    virtual ~ApplicationDelegate();
    
    /**
     Set OpenGL context attribution.
     */
    virtual void initGLContextAttrs();
    
    /**
     Application init function, include scene and config.
     
     @return    true    Init success, app can start.
     false   Init failed, app end.
     */
    virtual bool init();
    
    /**
     Application start function.
     
     @return    true    Start success.
     false   Start failed.
     */
    virtual bool start();
    
    
    /**
     Application stop function.
     
     @return    true    Stop success.
     false   Stop failed.
     */
    virtual bool stop();
    
    
    /**
     Application become active from stop.
     
     @return    true    Resume success.
     false   Resume failed.
     */
    virtual bool resume();
    
    
    /**
     Application end function.
     
     @return    true    End success.
     false   End failed.
     */
    virtual bool end();
};

#endif /* ApplicationDelegate_h */
