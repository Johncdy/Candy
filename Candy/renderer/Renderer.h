//
//  Renderer.h
//  Candy
//
//  Created by Dongyang.Cai on 14/11/2016.
//
//

#ifndef Renderer_h
#define Renderer_h

#include "include/Candy.h"

NS_DY_BEGIN

NS_RENDERER_BEGIN

class Renderer {
public:
    Renderer();
    
    virtual ~Renderer();
    
    /*
     Clear GL buffer and screen
     */
    void clear();
};

NS_RENDERER_END

NS_DY_END

#endif /* Renderer_h */
