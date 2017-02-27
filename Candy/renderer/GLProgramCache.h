//
//  GLStateCache.h
//  Candy
//
//  Created by Dongyang.Cai on 05/02/2017.
//
//

#ifndef GLStateCache_h
#define GLStateCache_h

#include "include/CandyMacros.h"
#include "object/Ref.h"
#include "renderer/GLProgram.h"

#include <unordered_map>

NS_DY_BEGIN

NS_RENDERER_BEGIN

class GLProgramCache : public object::Ref
{
public:
    /**
     returns the shared instance
     
     @return the shared instance
     */
    static GLProgramCache* getInstance();
    
    /**
     purges the cache. It releases the retained instance.
     */
    static void destroyInstance();
    
protected:
    DY_CONSTRUCTOR_FUNC(GLProgramCache);
    
    bool init();
    
private:
    // Predefined shaders.
    std::unordered_map<std::string, GLProgram*> _programs;
    
    static GLProgramCache* s_cache;
};

NS_RENDERER_END

NS_DY_END

#endif /* GLStateCache_h */
