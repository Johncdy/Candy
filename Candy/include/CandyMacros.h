//
//  CandyMacros.h
//  Candy
//
//  Created by Dongyang.Cai on 26/09/2016.
//
//

#ifndef CandyMacros_h
#define CandyMacros_h

// 0x00 HI ME LO
// 00   01 00 00
#define CANDY_VERSION 0x00010000

// PoolManager max capacity.
#define POOL_MANAGER_CAPACITY               0x00000001
// Default engine object pool index.
#define POOL_MANAGER_DEFAULT_POOL_INDEX     0x00000000

#ifdef __cplusplus
#define NS_DY_BEGIN         namespace candy {
#define NS_DY_END           }
#define NS_DY_USE           using namespace candy;
#define NS_DY               candy

#define NS_GUI_BEGIN        namespace gui {
#define NS_GUI_END          }
#define NS_GUI_USE          using namespace gui;
#define NS_GUI              gui

#define NS_MATH_BEGIN       namespace math {
#define NS_MATH_END         }
#define NS_MATH_USE         using namespace math;
#define NS_MATH             math

#define NS_OBJECT_BEGIN     namespace object {
#define NS_OBJECT_END       }
#define NS_OBJECT_USE       using namespace object;
#define NS_OBJECT           object

#define NS_PLATFORM_BEGIN   namespace platform {
#define NS_PLATFORM_END     }
#define NS_PLATFORM_USE     using namespace platform;
#define NS_PLATFORM         platform

#define NS_RENDERER_BEGIN   namespace renderer {
#define NS_RENDERER_END     }
#define NS_RENDERER_USE     using namespace renderer;
#define NS_RENDERER         renderer
#endif

#define DY_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define DY_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define DY_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define DY_SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define DY_SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define DY_SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)

// Math
#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif /* CandyMacros_h */
