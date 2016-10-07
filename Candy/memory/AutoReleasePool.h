//
//  AutoReleasePool.h
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#ifndef AutoReleasePool_h
#define AutoReleasePool_h

#include "platform/PlatformMacros.h"

#include "memory/Ref.h"

NS_DY_BEGIN

class AutoReleasePool {
public:
    /**
     Constructor.
     */
    AutoReleasePool();
    
    /**
     Destructor.
     */
    virtual ~AutoReleasePool();
    
    /**
     Add a given object to this autorelease pool.

     @param object The object to be added into the autorelease pool.
     */
    void addObject(Ref* object);
    
    /**
     Clear the autorelease pool.
     */
    void clear();
    
    bool contains(Ref* object) const;
};

NS_DY_END

#endif /* AutoReleasePool_h */
