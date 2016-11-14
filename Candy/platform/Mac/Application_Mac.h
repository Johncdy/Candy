//
//  Application_Mac.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef Application_Mac_h
#define Application_Mac_h

#include "include/CandyMacros.h"

#if DY_TARGET_PLATFORM == DY_PLATFORM_MAC

#include "platform/ApplicationProtocol.h"

NS_DY_BEGIN

class Application : public NS_PLATFORM::ApplicationProtocol {
public:

    Application();
    
    virtual ~Application();
    
    /**
     Application run loop.

     @return int   0: Application run success.
     */
    int run();
    
    // Application function.
    virtual bool init();
    virtual bool start();
    virtual bool update();
    virtual bool stop();
    virtual bool resume();
    virtual bool end();
    
protected:
    
    static double _frameTime;
    static double _elapsedTime;
};

NS_DY_END

#endif

#endif /* Application_Mac_h */
