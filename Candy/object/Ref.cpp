//
//  Ref.cpp
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#include "object/Ref.h"
#include "object/PoolManager.h"

#include <assert.h>

NS_DY_BEGIN

NS_OBJECT_BEGIN

Ref::Ref()
: _referenceCount(1)
{
}

Ref::~Ref()
{
}

void Ref::retain()
{
    assert(_referenceCount > 0);
    _referenceCount++;
}

void Ref::release()
{
    assert(_referenceCount > 0);
    _referenceCount--;
    
    if (0 == _referenceCount) {
        delete this;
    }
}

Ref* Ref::autoRelease()
{
    PoolManager::getInstance()->getDefaultPool()->addObject(this);
    return this;
}

unsigned int Ref::getReferenceCount()
{
    return _referenceCount;
}

NS_OBJECT_END

NS_DY_END
