/*
 * File: lfo.cpp
 *
 * Simple runtime test using LFO class as audio rate oscillator
 *
 * 
 * 
 * 2018 (c) Korg
 *
 */

#include "usermodfx.h"
#include "fx_api.h"

#include "saturation.hpp"

static vivsexion::Saturation s_sat;

enum {
  schetzen,
  tanh_alt,
  sigmoid,
  hard,
  saturator_count
};

static uint8_t s_saturator;
static float s_drive;
static const float s_min_drive = 1.f;
static const float s_max_drive = 8.f;

void MODFX_INIT(uint32_t platform, uint32_t api)
{
  // s_lfo.reset();
  // s_lfo.setF0(220.f,s_fs_recip);
}

void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn,  float *sub_yn,
                   uint32_t frames)
{
  const float * mx = main_xn;   
  float * __restrict my = main_yn;
  const float * my_e = my + 2*frames;
  float * __restrict sy = sub_yn;

  float sigOutL;                 // Signal output value L ch
  float sigOutR;                 // Signal output value R ch
  float sigInL;                  // Signal input value L ch
  float sigInR;                  // Signal input value R ch
  
  for (; my != my_e; ) {

    sigInL = (*mx++);
	sigInR = (*mx++);
    
    switch (s_saturator) {
    case schetzen:
      sigOutL = fx_sat_schetzenf(sigInL);
	  sigOutR = fx_sat_schetzenf(sigInR);
      break;
    case tanh_alt:
      sigOutL = s_sat.tanh_alt(sigInL, s_drive);
	  sigOutR = s_sat.tanh_alt(sigInR, s_drive);
      break;
      
    case sigmoid:
      sigOutL = s_sat.sigmoid_bipolar(sigInL, s_drive);
	  sigOutR = s_sat.sigmoid_bipolar(sigInR, s_drive);
      break;
      
    case hard:
      sigOutL = s_sat.hard_clip(sigInL, s_drive);
	  sigOutR = s_sat.hard_clip(sigInR, s_drive);
      break;
    }
    
    // Scale down the wave, full swing is way too loud. (polyphony headroom)
    // wave *= 0.1f;
    
    *(my++) = sigOutL;
    *(my++) = sigOutR;
    // *(sy++) = sat;
    // *(sy++) = sat;
  }

}


void MODFX_PARAM(uint8_t index, int32_t value)
{
  const float valf = q31_to_f32(value);
  switch (index) {
  case k_user_modfx_param_time:
    // this will select the saturation algorithm
    s_saturator = si_roundf(valf * (saturator_count - 1));
    break;
  case k_user_modfx_param_depth:
    // depth will control the input 'drive' to the saturation
    s_drive = valf * (s_max_drive - s_min_drive) + s_min_drive;
    break;
  default:
    break;
  }
}

