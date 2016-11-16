//
//  Size.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef Size_h
#define Size_h

#include "include/CandyMacros.h"

NS_DY_BEGIN

NS_MATH_BEGIN

class Size {
public:
    /**
     * Constructs a new size initialized to all zeros.
     */
    inline Size();
    
    /**
     Constructs a new size initialized to the specified values.

     @param w   The width of size.
     @param h  The height of size.
     */
    inline Size(float w, float h);
    
    /**
     * Constructs a new size that is a copy of the specified size.
     *
     * @param copy The size to copy.
     */
    inline Size(const Size& copy);
    
    /**
     Setter of Size.
     
     @param w   The width of size.
     @param h  The height of size.
     */
    inline void set(float w, float h);
    
    /**
     Operator equal.

     @param other Refrence from other size.
     @return Size.
     */
    inline const Size& operator= (const Size &other);
    
    /**
     Opeartor plus.

     @param other Refrence from other size.
     @return A plus size.
     */
    inline const Size operator+ (const Size &other) const;
    
    /**
     Operator minus.

     @param other Refrence form other size.
     @return A minus size.
     */
    inline const Size operator- (const Size &other) const;

    /**
     Operator multiply.

     @param a Float number.
     @return A multiply size.
     */
    inline const Size operator* (float a) const;
    
    /**
     Operator division.

     @param a Float number.
     @return A divide size.
     */
    inline const Size operator/ (float a) const;
    
public:
    // Width of size.
    float _width;
    // Height of size.
    float _height;
};

NS_MATH_END

NS_DY_END

#include "math/Size.inl"

#endif /* Size_h */
