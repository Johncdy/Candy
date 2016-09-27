//
//  Application.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef Application_h
#define Application_h

#include "platform/PlatformConfig.h"

#if DY_TARGET_PLATFORM == DY_PLATFORM_MAC
    #include "platform/Mac/Application_Mac.h"
#endif

#endif /* Application_h */
