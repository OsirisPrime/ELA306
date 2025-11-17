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
// PROGRAM LAB1
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,BTN)
  __DECLARE_VAR(BOOL,ALLOWEDPRESS)
  __DECLARE_VAR(BOOL,PRESSED)
  __DECLARE_VAR(BOOL,PED_WAIT)
  __DECLARE_VAR(BOOL,PEDESTRIAN)
  __DECLARE_VAR(BOOL,NORTH)
  __DECLARE_VAR(BOOL,SOUTH)
  __DECLARE_VAR(BOOL,WEST)
  __DECLARE_VAR(BOOL,EAST)
  __DECLARE_VAR(BOOL,STATE)
  __DECLARE_VAR(BOOL,S0)
  __DECLARE_VAR(BOOL,S1)
  __DECLARE_VAR(TIME,T10)
  __DECLARE_VAR(TIME,T80)
  __DECLARE_VAR(BOOL,ALLOWED_TIMER)
  __DECLARE_VAR(BOOL,TIMER_COOLDOWN)
  __DECLARE_VAR(BOOL,FF1)
  __DECLARE_VAR(BOOL,FF2)
  __DECLARE_VAR(BOOL,FF_OUTPUT)
  TON TON0;
  TON TON1;
  TP TP0;
  TP TP1;
  R_TRIG R_TRIG1;
  R_TRIG R_TRIG0;
  R_TRIG R_TRIG2;
  R_TRIG R_TRIG3;
  R_TRIG R_TRIG4;
  R_TRIG R_TRIG5;

} LAB1;

void LAB1_init__(LAB1 *data__, BOOL retain);
// Code part
void LAB1_body__(LAB1 *data__);
// PROGRAM TEST1
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  TON TON0;
  __DECLARE_VAR(BOOL,S1)
  __DECLARE_VAR(BOOL,S0)
  __DECLARE_VAR(BOOL,STATE)
  __DECLARE_VAR(BOOL,BUTTON)
  __DECLARE_VAR(TIME,T80)
  TON TON1;
  __DECLARE_VAR(TIME,T10)
  R_TRIG R_TRIG0;
  __DECLARE_VAR(BOOL,BUTTON_PRESSED)

} TEST1;

void TEST1_init__(TEST1 *data__, BOOL retain);
// Code part
void TEST1_body__(TEST1 *data__);
#endif //__POUS_H
