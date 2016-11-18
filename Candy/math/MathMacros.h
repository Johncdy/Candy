//
//  MathMacros.h
//  Candy
//
//  Created by Dongyang.Cai on 18/11/2016.
//
//

#ifndef MathMacros_h
#define MathMacros_h

// Math
#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#define MATRIX_SIZE ( sizeof(float) * 16)

/**Util macro for conversion from degrees to radians.*/
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
/**Util macro for conversion from radians to degrees.*/
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)

/**
  @{ Util macro for const float such as epsilon, small float and float precision tolerance.
 */
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_EPSILON                0.000001f


#endif /* MathMacros_h */
