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
    Saturation(void) :
      
    { }
      
    /*===========================================================================*/
    /* Public Methods.                                                           */
    /*===========================================================================*/

    // --- Transfer functions --------------

    /**
     * Get value of tanh transform of one sample 
	 *
     * @param xn  Input sample
     *
     * @return Output sample
     */
    inline __attribute__((optimize("Ofast"),always_inline))
    float tanh(const float xn, const float gain) 
    {
      const float y = xn * gain;
      return (2 / (1 + exp(-2*y)) - 1);
    }

    /**
     * Get value of sigmoid bipolar transform of one sample 
	 *
     * @param xn  Input sample
     *
     * @return Output sample
     */
    inline __attribute__((optimize("Ofast"),always_inline))
    float sigmoid_bipolar(const float xn, const float gain) 
    {
      const float y = xn * gain;
      return (1 - exp(-y)) / (1 + exp(-y)));
    }

    /**
     * Get value of hard clipping transform of one sample 
	 *
     * @param xn  Input sample
     *
     * @return Output sample
     */
    inline __attribute__((optimize("Ofast"),always_inline))
    float hard_clip(const float xn, const float gain) 
    {
	  float out;
      const float y = xn * gain;
	  if (y > 1.0f) {
	    return 1.0f;
	  } else if (y < -1.0f) {
	    return -1f;
	  } else {
	    return y;
	  }
    }
      
  };
}

/** @} */
