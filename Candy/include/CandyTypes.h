//
//  CandyTypes.h
//  Candy
//
//  Created by Dongyang.Cai on 05/02/2017.
//
//

#ifndef CandyTypes_h
#define CandyTypes_h

#include "platform/platform.h"

/**
 RGB color composed of bytes 3 bytes.
 */
struct Color3B {
    Color3B(GLubyte r, GLubyte g, GLubyte b)
    {
        _r = r;
        _g = g;
        _b = b;
    }
    
    GLubyte _r, _g, _b;
};

/**
 RGBA color composed of 4 bytes.
 */
struct Color4B {
    Color4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
    {
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }
    
    GLubyte _r, _g, _b, _a;
};

/**
 RGBA color composed of 4 floats.
 */
struct Color4F {
    Color4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    {
        _r = r;
        _g = g;
        _b = b;
        _a = a;
    }
    
    GLfloat _r;
    GLfloat _g;
    GLfloat _b;
    GLfloat _a;
};

#endif /* CandyTypes_h */
