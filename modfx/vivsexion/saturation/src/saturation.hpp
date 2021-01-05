#include "fixed_math.h"
#include "int_math.h"
#include "float_math.h"

/**
 * @file    saturation.hpp
 * @brief   Saturation functions.
 *
 * @addtogroup vivsexion vivsexion
 * @{
 */

/**
 * Saturation utilities
 */
namespace vivsexion {    

  /**
   * Saturation
   */
  struct Saturation {
    
    /*===========================================================================*/
    /* Types and Data Structures.                                                */
    /*===========================================================================*/
      
    /*===========================================================================*/
    /* Constructor / Destructor.                                                 */
    /*===========================================================================*/

    /**
     * Default constructor
     */
    Saturation(void) = default;
      
    /*===========================================================================*/
    /* Public Methods.                                                           */
    /*===========================================================================*/

    // --- Transfer functions --------------

    /**
     * Get value of tanh transform of one sample 
     *
     * @param xn  Input sample
     * @param drive Input drive (gain)
     *
     * @return Output sample
     */
    inline __attribute__((optimize("Ofast"),always_inline))
    float tanh_alt(const float xn, const float drive) 
    {
      // return (fastertanhf(xn * drive))
      const float y = xn * drive;
      return (2 / (1 + fasterexpf(-2*y)) - 1);
    }

    /**
     * Get value of sigmoid bipolar transform of one sample 
     *
     * @param xn  Input sample
     * @param drive Input drive (gain)
     *
     * @return Output sample
     */
    inline __attribute__((optimize("Ofast"),always_inline))
    float sigmoid_bipolar(const float xn, const float drive) 
    {
      const float y = xn * drive;
      return (1 - fasterexpf(-y)) / (1 + fasterexpf(-y));
    }

    /**
     * Get value of hard clipping transform of one sample 
     *
     * @param xn  Input sample
     * @param drive Input drive (gain)
     *
     * @return Output sample
     */
    inline __attribute__((optimize("Ofast"),always_inline))
    float hard_clip(const float xn, const float drive) 
    {
      /*
      const float y = xn * drive;
      if (y > 1.0f) {
        return 1.0f;
      } else if (y < -1.0f) {
        return -1.0f;
      } else {
        return y;
      }
      */
      return clip1m1f(xn * drive);
    }
      
  };
}

/** @} */
