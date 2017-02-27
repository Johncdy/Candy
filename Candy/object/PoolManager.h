//
//  PoolManager.h
//  Candy
//
//  Created by Dongyang.Cai on 08/10/2016.
//
//

#ifndef PoolManager_h
#define PoolManager_h

#include "object/ObjectPool.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

class PoolManager {
public:
    /**
     Get pool manager singleton.

     @return The singleton of pool manager.
     */
    static PoolManager* getInstance();
    
    /**
     Delete pool manager singleton.
     */
    static void destroyInstance();
    
    /**
     Get current auto release pool, there is at least one auto release pool that created by engine.

     @return Auto release pool.
     */
    ObjectPool* getDefaultPool() const;
    
    /**
     Get current pool at position.

     @param pos Position.

     @return The object pool at position.
     */
    ObjectPool* getPoolAt(int pos) const;
    
    friend class ObjectPool;
    
private:
    /**
     Constructor.
     */
    PoolManager();
    
    /**
     Destructor.
     */
    virtual ~PoolManager();
    
    /**
     Add a given pool to the manager.

     @param pool A given object pool.
     */
    int push(ObjectPool* pool);
    
    /**
     Removes the last element in the manager.
     
     @param pos The position of pool.
     */
    void pop(int pos);
    
    // PoolManager singleton instance.
    static PoolManager* s_manager;
    
    // Object pool stack.
    std::vector<ObjectPool*> _objectPoolVector;
};

NS_OBJECT_END

NS_DY_END

#endif /* PoolManager_h */
