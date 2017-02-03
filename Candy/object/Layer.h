//
//  Layer.hpp
//  Candy
//
//  Created by Dongyang.Cai on 06/01/2017.
//
//

#ifndef Layer_h
#define Layer_h

#include "include/CandyMacros.h"

#include "object/node/Node.h"

NS_DY_BEGIN

NS_OBJECT_BEGIN

class Layer : public Node {
public:
    /** Creates a fullscreen black layer.
     *
     * @return An autoreleased Layer object.
     */
    DY_CREATE_FUNC(Layer);
    
protected:
    Layer();
    virtual ~Layer();
    
    virtual bool init() override;
};

NS_OBJECT_END

NS_DY_END

#endif /* Layer_h */
