//
//  ApplicationProtocol.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef ApplicationProtocol_h
#define ApplicationProtocol_h

#include "platform/PlatformMacros.h"

NS_DY_BEGIN

class ApplicationProtocol {
public:
    
    /**
     Application destructor.
     */
    virtual ~ApplicationProtocol() {}
    
    /**
     Application init function, include scene and config.
     
     @return    true    Init success, app can start.
                false   Init failed, app end.
     */
    virtual bool init() = 0;
    
    /**
     Application start function.

     @return    true    Start success.
                false   Start failed.
     */
    virtual bool start() = 0;
    
    
    /**
     Application stop function.

     @return    true    Stop success.
                false   Stop failed.
     */
    virtual bool stop() = 0;
    
    
    /**
     Application become active from stop.

     @return    true    Resume success.
                false   Resume failed.
     */
    virtual bool resume() = 0;
    
    
    /**
     Application end function.

     @return    true    End success.
                false   End failed.
     */
    virtual bool end() = 0;
};

NS_DY_END

#endif /* ApplicationProtocol_h */
