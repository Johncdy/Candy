//
//  GLView_Mac.cpp
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#include "GLView_Mac.h"

NS_DY_BEGIN

GLView::GLView()
{
}

GLView::~GLView()
{
}

GLView* GLView::create(const std::string &viewName, Rect rect, float frameZoomFactor, bool resizable)
{
    auto view = new (std::nothrow) GLView;
    if (view && view->init(viewName, rect, frameZoomFactor, resizable)) {
        
    }
    return view;
}

NS_DY_END
