#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// PROGRAM LAB2
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(UINT,POTENTIOMETER)
  __DECLARE_VAR(UINT,LJUSSENSOR)
  __DECLARE_VAR(BOOL,S0)
  __DECLARE_VAR(BOOL,S1)
  __DECLARE_VAR(BOOL,LIGHT_SAMPLE)
  __DECLARE_VAR(BOOL,POTEN_SAMPLE)
  __DECLARE_VAR(UINT,LIGHT_COMP)
  __DECLARE_VAR(UINT,DAMAGED)
  __DECLARE_VAR(UINT,HIGH)
  __DECLARE_VAR(UINT,LOW)
  __DECLARE_VAR(BOOL,RELAY)
  CTU CTU0;
  TON TON0;
  __DECLARE_VAR(TIME,T50MS)
  __DECLARE_VAR(BOOL,TICK_100MS)
  __DECLARE_VAR(INT,FIFTY_TICKS)
  TON TON1;
  R_TRIG R_TRIG0;
  F_TRIG F_TRIG0;
  R_TRIG R_TRIG1;
  __DECLARE_VAR(BOOL,_TMP_GE6_OUT)
  __DECLARE_VAR(BOOL,_TMP_EQ31_OUT)
  __DECLARE_VAR(BOOL,_TMP_GT34_OUT)
  __DECLARE_VAR(BOOL,_TMP_LT35_OUT)
  __DECLARE_VAR(BOOL,_TMP_EQ42_OUT)
  __DECLARE_VAR(BOOL,_TMP_OR40_OUT)
  __DECLARE_VAR(BOOL,_TMP_NOT41_OUT)

} LAB2;

void LAB2_init__(LAB2 *data__, BOOL retain);
// Code part
void LAB2_body__(LAB2 *data__);
#endif //__POUS_H
