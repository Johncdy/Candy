//
//  PoolManager.cpp
//  Candy
//
//  Created by Dongyang.Cai on 08/10/2016.
//
//

#include "include/CandyMacros.h"
#include "object/PoolManager.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

PoolManager* PoolManager::s_manager = nullptr;

PoolManager* PoolManager::getInstance()
{
    if (nullptr == s_manager) {
        s_manager = new (std::nothrow) PoolManager();
        
        assert(s_manager);
        
        new (std::nothrow) ObjectPool(1);
    }
    return s_manager;
}

void PoolManager::destroyInstance()
{
    DY_SAFE_DELETE(s_manager);
}

ObjectPool* PoolManager::getDefaultPool() const
{
    return _objectPoolVector[POOL_MANAGER_DEFAULT_POOL_INDEX];
}

ObjectPool* PoolManager::getPoolAt(int pos) const
{
    if (pos > _objectPoolVector.size()-1) {
        return nullptr;
    }
    return _objectPoolVector[pos];
}

PoolManager::PoolManager()
{
    _objectPoolVector.reserve(POOL_MANAGER_CAPACITY);
    
}

PoolManager::~PoolManager()
{
    printf("deallocing PoolManager: %p", this);
    
    while (!_objectPoolVector.empty()) {
        ObjectPool* pool = _objectPoolVector.back();
        delete pool;
    }
    
    s_manager = nullptr;
}

int PoolManager::push(ObjectPool* pool)
{
    assert(_objectPoolVector.size() <= POOL_MANAGER_CAPACITY);
    
    _objectPoolVector.push_back(pool);
    return static_cast<int>(_objectPoolVector.size());
}

void PoolManager::pop(int pos)
{
    _objectPoolVector.erase(_objectPoolVector.begin() + pos - 1);
}

NS_OBJECT_END

NS_DY_END
