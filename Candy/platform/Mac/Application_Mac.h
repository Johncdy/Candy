//
//  Application_Mac.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef Application_Mac_h
#define Application_Mac_h

#include "platform/PlatformConfig.h"

#if DY_TARGET_PLATFORM == DY_PLATFORM_MAC

#include "platform/ApplicationProtocol.h"

NS_DY_BEGIN

class Application : public ApplicationProtocol {
public:

    Application();
    
    virtual ~Application();
    
    
    /**
     Get current application instance.
     
     @return Current application instance pointer.
     */
    static Application* getInstance();
    
    /**
     Application run loop.

     @return int   0: Application run success.
     */
    int run();
    
protected:
    
    static Application* s_application;
};

NS_DY_END

#endif

#endif /* Application_Mac_h */
