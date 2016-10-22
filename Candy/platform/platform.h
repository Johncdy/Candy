//
//  platform.h
//  Candy
//
//  Created by Dongyang.Cai on 27/09/2016.
//
//

#ifndef platform_h
#define platform_h

#include "platform/PlatformMacros.h"

#if (DY_TARGET_PLATFORM == DY_PLATFORM_MAC)
    #include "platform/Mac/Application_Mac.h"
    #include "platform/Mac/GLView_Mac.h"
#endif // DY_TARGET_PLATFORM == DY_PLATFORM_MAC

#endif /* platform_h */
