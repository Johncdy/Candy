//
//  PlatformMacros.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef PlatformMacros_h
#define PlatformMacros_h

// Define supported target platform macro with DY uses.
#define DY_PLATFORM_UNKNOW        0
#define DY_PLATFORM_IOS           1
#define DY_PLATFORM_ANDROID       2
#define DY_PLATFORM_WIN           3
#define DY_PLATFORM_MAC           4

// Determine target platform by compile environment macro.
#define DY_TARGET_PLATFORM  DY_PLATFORM_UNKNOWN

// Apple: Mac and iOS
/**
 @param __APPLE__ This macro is defined in any Apple computer.
 */
#if defined(__APPLE__)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#undef DY_TARGET_PLATFORM
#define DY_TARGET_PLATFORM      DY_PLATFORM_IOS
#elif TARGET_OS_MAC
#undef DY_TARGET_PLATFORM
#define DY_TARGET_PLATFORM      DY_PLATFORM_MAC
#endif
#endif

// Android
#if defined(ANDROID)
#undef DY_TARGET_PLATFORM
#define DY_TARGET_PLATFORM      DY_PLATFORM_ANDROID
#endif

// Win
#if defined(_WIN32) && defined(_WINDOWS)
#undef DY_TARGET_PLATFORM
#define DY_TARGET_PLATFORM      DY_PLATFORM_WIN
#endif

#endif /* PlatformMacros_h */
