//
//  ObjectPool.h
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#ifndef ObjectPool_h
#define ObjectPool_h

#include <vector>

#include "platform/PlatformMacros.h"

#include "memory/Ref.h"

NS_DY_BEGIN

class ObjectPool {
public:
    /**
     Constructor.
     
     @param index  The identifier, 1 is game engine created.
     */
    ObjectPool(int index);
    
    /**
     Destructor.
     */
    virtual ~ObjectPool();
    
    /**
     Add a given object to this object pool.

     @param object The object to be added into the object pool.
     */
    void addObject(Ref* object);
    
    /**
     Clear the autorelease pool.
     */
    void clear();
    
    /**
     Checks whether the object pool contains the specified object.

     @param object The object to be checked.

     @return True if the object pool contains the object, false if not
     */
    bool contains(Ref* object) const;
    
    /**
     Dump the objects that are put into the object pool. It is used for debugging.
     */
    void dump();
    
private:
    // Object stack.
    std::vector<Ref*> _objectVector;
    // The identifier.
    int _index;
    // The position in manager.
    int _pos;
};

NS_DY_END

#endif /* ObjectPool_h */
