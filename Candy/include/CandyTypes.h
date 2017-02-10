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
    Color3B();
    Color3B(GLubyte r, GLubyte g, GLubyte b);
    
    GLubyte _r, _g, _b;
};

/**
 RGBA color composed of 4 bytes.
 */
struct Color4B {
    Color4B();
    Color4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
    
    GLubyte _r, _g, _b, _a;
};

/**
 RGBA color composed of 4 floats.
 */
struct Color4F {
    Color4F();
    Color4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    
    GLfloat _r, _g, _b, _a;
};

/**
 Blend Function used for textures.
 */
struct BlendFunc
{
    // source blend function.
    GLenum src;
    // destination blend function.
    GLenum dst;
    
    // Blending disabled. Uses {GL_ONE, GL_ZERO}
    static const BlendFunc DISABLE;
    // Blending enabled for textures with Alpha premultiplied. Uses {GL_ONE, GL_ONE_MINUS_SRC_ALPHA}
    static const BlendFunc ALPHA_PREMULTIPLIED;
    // Blending enabled for textures with Alpha NON premultiplied. Uses {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA}
    static const BlendFunc ALPHA_NON_PREMULTIPLIED;
    // Enables Additive blending. Uses {GL_SRC_ALPHA, GL_ONE}
    static const BlendFunc ADDITIVE;
    
    bool operator==(const BlendFunc &a) const
    {
        return src == a.src && dst == a.dst;
    }
    
    bool operator!=(const BlendFunc &a) const
    {
        return src != a.src || dst != a.dst;
    }
    
    bool operator<(const BlendFunc &a) const
    {
        return src < a.src || (src == a.src && dst < a.dst);
    }
};

#endif /* CandyTypes_h */
