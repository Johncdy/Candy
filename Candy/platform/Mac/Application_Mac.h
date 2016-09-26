//
//  Application_Mac.hpp
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef Application_Mac_h
#define Application_Mac_h

#include "platform/ApplicationProtocol.h"

NS_DY_BEGIN

class Application : public ApplicationProtocol {
public:
    
    Application();
    
    ~Application();
    
    bool run() override;
};

NS_DY_END

#endif /* Application_Mac_hpp */
