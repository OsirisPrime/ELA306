void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void LAB2_init__(LAB2 *data__, BOOL retain) {
  __INIT_VAR(data__->POTENTIOMETER,0,retain)
  __INIT_VAR(data__->LJUSSENSOR,0,retain)
  __INIT_VAR(data__->S0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->S1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LIGHT_SAMPLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->POTEN_SAMPLE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->LIGHT_COMP,32768,retain)
  __INIT_VAR(data__->DAMAGED,0,retain)
  __INIT_VAR(data__->HIGH,43690,retain)
  __INIT_VAR(data__->LOW,21845,retain)
  __INIT_VAR(data__->RELAY,0,retain)
  CTU_init__(&data__->CTU0,retain);
  TON_init__(&data__->TON0,retain);
  __INIT_VAR(data__->T50MS,__time_to_timespec(1, 50, 0, 0, 0, 0),retain)
  __INIT_VAR(data__->TICK_100MS,0,retain)
  __INIT_VAR(data__->FIFTY_TICKS,50,retain)
  TON_init__(&data__->TON1,retain);
  R_TRIG_init__(&data__->R_TRIG0,retain);
  F_TRIG_init__(&data__->F_TRIG0,retain);
  R_TRIG_init__(&data__->R_TRIG1,retain);
  __INIT_VAR(data__->_TMP_GE6_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ31_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_GT34_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_LT35_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ42_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR40_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT41_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LAB2_body__(LAB2 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,!(__GET_VAR(data__->S0,)));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->T50MS,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->R_TRIG0.,CLK,,__GET_VAR(data__->TON0.Q,));
  R_TRIG_body__(&data__->R_TRIG0);
  __SET_VAR(data__->F_TRIG0.,CLK,,__GET_VAR(data__->TON0.Q,));
  F_TRIG_body__(&data__->F_TRIG0);
  __SET_VAR(data__->,TICK_100MS,,(__GET_VAR(data__->F_TRIG0.Q,) || __GET_VAR(data__->R_TRIG0.Q,)));
  __SET_VAR(data__->R_TRIG1.,CLK,,__GET_VAR(data__->TICK_100MS,));
  R_TRIG_body__(&data__->R_TRIG1);
  __SET_VAR(data__->CTU0.,CU,,__GET_VAR(data__->R_TRIG1.Q,));
  __SET_VAR(data__->CTU0.,R,,__GET_VAR(data__->CTU0.Q,));
  __SET_VAR(data__->CTU0.,PV,,__GET_VAR(data__->FIFTY_TICKS,));
  CTU_body__(&data__->CTU0);
  __SET_VAR(data__->,LIGHT_SAMPLE,,__GET_VAR(data__->CTU0.Q,));
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->S1,));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->T50MS,));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,S0,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->,S1,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->,POTEN_SAMPLE,,__GET_VAR(data__->TICK_100MS,));
  __SET_VAR(data__->,_TMP_GE6_OUT,,GE__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->LJUSSENSOR,),
    (UINT)__GET_VAR(data__->LIGHT_COMP,)));
  __SET_VAR(data__->,_TMP_EQ31_OUT,,EQ__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->LJUSSENSOR,),
    (UINT)__GET_VAR(data__->DAMAGED,)));
  __SET_VAR(data__->,_TMP_GT34_OUT,,GT__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->POTENTIOMETER,),
    (UINT)__GET_VAR(data__->HIGH,)));
  __SET_VAR(data__->,_TMP_LT35_OUT,,LT__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->POTENTIOMETER,),
    (UINT)__GET_VAR(data__->LOW,)));
  __SET_VAR(data__->,_TMP_EQ42_OUT,,EQ__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->POTENTIOMETER,),
    (UINT)__GET_VAR(data__->DAMAGED,)));
  __SET_VAR(data__->,_TMP_OR40_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->_TMP_GT34_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_LT35_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_EQ42_OUT,)));
  __SET_VAR(data__->,_TMP_NOT41_OUT,,!(__GET_VAR(data__->_TMP_OR40_OUT,)));

  goto __end;

__end:
  return;
} // LAB2_body__() 





