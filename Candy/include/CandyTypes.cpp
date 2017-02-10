//
//  CandyTypes.cpp
//  Candy
//
//  Created by Dongyang.Cai on 09/02/2017.
//
//

#include "include/CandyTypes.h"

const BlendFunc BlendFunc::DISABLE = {GL_ONE, GL_ZERO};
const BlendFunc BlendFunc::ALPHA_PREMULTIPLIED = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA};
const BlendFunc BlendFunc::ALPHA_NON_PREMULTIPLIED = {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
const BlendFunc BlendFunc::ADDITIVE = {GL_SRC_ALPHA, GL_ONE};

Color3B::Color3B()
: _r(0)
, _g(0)
, _b(0)
{}

Color3B::Color3B(GLubyte r, GLubyte g, GLubyte b)
: _r(r)
, _g(g)
, _b(b)
{}

Color4B::Color4B()
: _r(0)
, _g(0)
, _b(0)
, _a(0)
{}

Color4B::Color4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
: _r(r)
, _g(g)
, _b(b)
, _a(a)
{}

Color4F::Color4F()
: _r(0.0f)
, _g(0.0f)
, _b(0.0f)
, _a(0.0f)
{}

Color4F::Color4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
: _r(r)
, _g(g)
, _b(b)
, _a(a)
{}
