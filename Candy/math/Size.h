//
//  Size.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef Size_h
#define Size_h

#include "platform/PlatformMacros.h"

NS_DY_BEGIN

class Size {
public:
    
    /**
     Constructs a new size initialized to the specified values.

     @param width   The width of size.
     @param height  The height of size.
     */
    Size(float width, float height);
    
public:
    // Width of size.
    float width;
    // Height of size.
    float height;
};

NS_DY_END

#endif /* Size_h */
