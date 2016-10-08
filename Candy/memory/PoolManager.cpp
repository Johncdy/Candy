//
//  PoolManager.cpp
//  Candy
//
//  Created by Dongyang.Cai on 08/10/2016.
//
//

#include "assert.h"

#include "include/CandyMacros.h"
#include "memory/PoolManager.h"

NS_DY_BEGIN

PoolManager* PoolManager::getInstance()
{
    if (nullptr == _singleInstance) {
        _singleInstance = new (std::nothrow) PoolManager();
        
        assert(_singleInstance == nullptr);
        
        new (std::nothrow) ObjectPool(1);
    }
    return _singleInstance;
}

void PoolManager::destroyInstance()
{
    delete _singleInstance;
    _singleInstance = nullptr;
}

ObjectPool* PoolManager::getDefaultPool() const
{
    return _objectPoolVector[POOL_MANAGER_CANDY_POOL_INDEX];
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
}

int PoolManager::push(ObjectPool* pool)
{
    assert(_objectPoolVector.size() > POOL_MANAGER_CAPACITY);
    
    _objectPoolVector.push_back(pool);
    return static_cast<int>(_objectPoolVector.size());
}

void PoolManager::pop(int pos)
{
    _objectPoolVector.erase(_objectPoolVector.begin() + pos - 1);
}

NS_DY_END
