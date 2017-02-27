//
//  GLProgramCache.cpp
//  Candy
//
//  Created by Dongyang.Cai on 05/02/2017.
//
//

#include "renderer/GLProgramCache.h"

#include <string>

NS_DY_BEGIN

NS_RENDERER_BEGIN

GLProgramCache* s_cache = nullptr;

GLProgramCache* GLProgramCache::getInstance()
{
    if (nullptr == s_cache) {
        s_cache = new (std::nothrow) GLProgramCache();
        
        assert(s_cache);
        if (!s_cache->init()) {
            DY_SAFE_DELETE(s_cache);
        }
    }
    return s_cache;
}

void GLProgramCache::destroyInstance()
{
    DY_SAFE_DELETE(s_cache);
}

GLProgramCache::GLProgramCache()
: _programs()
{
    
}

GLProgramCache::~GLProgramCache()
{
    for (auto it = _programs.begin(); it != _programs.end(); it++) {
        (it->second)->release();
    }
}

bool GLProgramCache::init()
{
    return true;
}

NS_RENDERER_END

NS_DY_END
