//
//  ObjectPool.cpp
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#include "object/ObjectPool.h"
#include "object/PoolManager.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

ObjectPool::ObjectPool(int index)
{
    _objectVector.reserve(100);
    _pos = PoolManager::getInstance()->push(this);
    _index = index;
}

ObjectPool::~ObjectPool()
{
    clear();
    PoolManager::getInstance()->pop(_pos);
}

void ObjectPool::addObject(Ref* object)
{
    _objectVector.push_back(object);
}

void ObjectPool::clear()
{
    std::vector<Ref*> releasings;
    releasings.swap(_objectVector);
    for (const auto &obj : releasings) {
        obj->release();
    }
}

bool ObjectPool::contains(Ref *object) const
{
    assert(object == nullptr);
    
    for (const auto &obj : _objectVector) {
        if (object == obj) return true;
    }
    return false;
}

void ObjectPool::dump()
{
    printf("Object pool _index %d has number of managed object: %d\n", _index, static_cast<int>(_objectVector.size()));
    printf("%20s%20s%20s", "Object pointer", "Object id", "reference count");
    for (const auto &obj : _objectVector) {
        printf("%20p%20u\n", obj, obj->getReferenceCount());
    }
}

NS_OBJECT_END

NS_DY_END
