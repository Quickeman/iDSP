#ifndef IDSP_TYPES_H
#define IDSP_TYPES_H

namespace idsp {

// Floating-point type
#ifndef IDSP_FLOAT_TYPE
    #define IDSP_FLOAT_TYPE double
#endif
/** Floating-point type. */
typedef IDSP_FLOAT_TYPE FloatT;

// Signed integer type
#ifndef IDSP_INT_TYPE
    #define IDSP_INT_TYPE int
#endif
/** Signed integer type. */
typedef IDSP_INT_TYPE IntT;

// Unsigned integer type
#ifndef IDSP_UINT_TYPE
    #define IDSP_UINT_TYPE unsigned int
#endif
/** Unsigned integer type. */
typedef IDSP_UINT_TYPE UIntT;

} // namespace idsp

#endif
