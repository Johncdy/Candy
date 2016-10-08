//
//  PlatformMacros.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef PlatformMacros_h
#define PlatformMacros_h

#ifdef __cplusplus
    #define NS_DY_BEGIN     namespace candy {
    #define NS_DY_END       }
    #define NS_DY_USE       using namespace candy;
    #define NS_DY           candy
#endif

#define DY_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define DY_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define DY_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define DY_SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define DY_SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define DY_SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)

#endif /* PlatformMacros_h */
