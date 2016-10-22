//
//  Ref.h
//  Candy
//
//  Created by Dongyang.Cai on 07/10/2016.
//
//

#ifndef Ref_h
#define Ref_h

#include "include/CandyMacros.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Ref {
protected:
    /**
     Only subclass can construct this object.
     */
    Ref();
    
public:
    /**
     Destructor
     */
    virtual ~Ref();
    
    /**
     Retains the ownership.
     This increases the Ref's reference count.
     */
    void retain();
    
    /**
     Releases the ownership immediately.
     This decrements the Ref's reference count.
     */
    void release();
    
    /**
     Releases the ownership sometime soon automatically.

     @return The Ref itself.
     */
    Ref* autoRelease();
    
    /**
     Returns the Ref's current reference count.

     @return The Ref's reference count.
     */
    unsigned int getReferenceCount();
    
protected:
    // count of references
    unsigned int _referenceCount;
};

NS_OBJECT_END

NS_DY_END

#endif /* Ref_h */
