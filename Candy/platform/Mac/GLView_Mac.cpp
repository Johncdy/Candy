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
        view->autoRelease();
        return view;
    }
    DY_SAFE_DELETE(view);
    return nullptr;
}

bool GLView::init(const std::string &viewName, candy::Rect rect, float frameZoomFactor, bool resizable)
{
    _viewName = viewName;
    
    return true;
}

NS_DY_END
