//
//  Ref.cpp
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#include "memory/memory.h"

#include <assert.h>

NS_DY_BEGIN

Ref::Ref()
: referenceCount(1)
{
}

Ref::~Ref()
{
}

void Ref::retain()
{
    assert(referenceCount > 0);
    referenceCount++;
}

void Ref::release()
{
    assert(referenceCount > 0);
    referenceCount--;
    
    if (0 == referenceCount) {
        delete this;
    }
}

unsigned int Ref::getReferenceCount()
{
    return referenceCount;
}

NS_DY_END
