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





void LAB1_init__(LAB1 *data__, BOOL retain) {
  __INIT_VAR(data__->BTN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ALLOWEDPRESS,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PRESSED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PED_WAIT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PEDESTRIAN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->NORTH,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SOUTH,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->WEST,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EAST,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->S0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->S1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T10,__time_to_timespec(1, 0, 10, 0, 0, 0),retain)
  __INIT_VAR(data__->T80,__time_to_timespec(1, 0, 40, 0, 0, 0),retain)
  __INIT_VAR(data__->ALLOWED_TIMER,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TIMER_COOLDOWN,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->FF1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->FF2,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->FF_OUTPUT,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
  TP_init__(&data__->TP0,retain);
  TP_init__(&data__->TP1,retain);
  R_TRIG_init__(&data__->R_TRIG1,retain);
  R_TRIG_init__(&data__->R_TRIG0,retain);
  R_TRIG_init__(&data__->R_TRIG2,retain);
  R_TRIG_init__(&data__->R_TRIG3,retain);
  R_TRIG_init__(&data__->R_TRIG4,retain);
  R_TRIG_init__(&data__->R_TRIG5,retain);
}

// Code part
void LAB1_body__(LAB1 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,(!(__GET_VAR(data__->S1,)) && !(__GET_VAR(data__->PEDESTRIAN,))));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->T10,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,S0,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TON1.,IN,,(__GET_VAR(data__->S0,) && !(__GET_VAR(data__->PEDESTRIAN,))));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->T10,));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,S1,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->R_TRIG1.,CLK,,__GET_VAR(data__->S1,));
  R_TRIG_body__(&data__->R_TRIG1);
  __SET_VAR(data__->R_TRIG0.,CLK,,__GET_VAR(data__->S0,));
  R_TRIG_body__(&data__->R_TRIG0);
  if ((!(__GET_VAR(data__->FF1,)) && (__GET_VAR(data__->R_TRIG0.Q,) || __GET_VAR(data__->R_TRIG1.Q,)))) {
    __SET_VAR(data__->,FF1,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->R_TRIG2.,CLK,,__GET_VAR(data__->S0,));
  R_TRIG_body__(&data__->R_TRIG2);
  __SET_VAR(data__->R_TRIG3.,CLK,,__GET_VAR(data__->S1,));
  R_TRIG_body__(&data__->R_TRIG3);
  if (((__GET_VAR(data__->FF1,) && __GET_VAR(data__->FF_OUTPUT,)) && (__GET_VAR(data__->R_TRIG2.Q,) || __GET_VAR(data__->R_TRIG3.Q,)))) {
    __SET_VAR(data__->,FF1,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->,FF_OUTPUT,,__GET_VAR(data__->FF1,));
  __SET_VAR(data__->,NORTH,,(!(__GET_VAR(data__->FF_OUTPUT,)) && !(__GET_VAR(data__->PEDESTRIAN,))));
  __SET_VAR(data__->,SOUTH,,(!(__GET_VAR(data__->FF_OUTPUT,)) && !(__GET_VAR(data__->PEDESTRIAN,))));
  __SET_VAR(data__->,EAST,,(__GET_VAR(data__->FF_OUTPUT,) && !(__GET_VAR(data__->PEDESTRIAN,))));
  __SET_VAR(data__->,WEST,,(__GET_VAR(data__->FF_OUTPUT,) && !(__GET_VAR(data__->PEDESTRIAN,))));
  __SET_VAR(data__->,PRESSED,,__GET_VAR(data__->BTN,));
  __SET_VAR(data__->,ALLOWEDPRESS,,(!(__GET_VAR(data__->TIMER_COOLDOWN,)) && __GET_VAR(data__->PRESSED,)));
  __SET_VAR(data__->TP0.,IN,,__GET_VAR(data__->ALLOWEDPRESS,));
  __SET_VAR(data__->TP0.,PT,,__GET_VAR(data__->T80,));
  TP_body__(&data__->TP0);
  __SET_VAR(data__->,TIMER_COOLDOWN,,__GET_VAR(data__->TP0.Q,));
  if (__GET_VAR(data__->ALLOWEDPRESS,)) {
    __SET_VAR(data__->,PED_WAIT,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->R_TRIG5.,CLK,,__GET_VAR(data__->S1,));
  R_TRIG_body__(&data__->R_TRIG5);
  __SET_VAR(data__->R_TRIG4.,CLK,,__GET_VAR(data__->S0,));
  R_TRIG_body__(&data__->R_TRIG4);
  __SET_VAR(data__->TP1.,IN,,(__GET_VAR(data__->PED_WAIT,) && (__GET_VAR(data__->R_TRIG4.Q,) || __GET_VAR(data__->R_TRIG5.Q,))));
  __SET_VAR(data__->TP1.,PT,,__GET_VAR(data__->T10,));
  TP_body__(&data__->TP1);
  if (__GET_VAR(data__->TP1.Q,)) {
    __SET_VAR(data__->,PED_WAIT,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->,PEDESTRIAN,,__GET_VAR(data__->TP1.Q,));

  goto __end;

__end:
  return;
} // LAB1_body__() 





void TEST1_init__(TEST1 *data__, BOOL retain) {
  TON_init__(&data__->TON0,retain);
  __INIT_VAR(data__->S1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->S0,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STATE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BUTTON,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->T80,__time_to_timespec(1, 0, 80, 0, 0, 0),retain)
  TON_init__(&data__->TON1,retain);
  __INIT_VAR(data__->T10,__time_to_timespec(1, 0, 10, 0, 0, 0),retain)
  R_TRIG_init__(&data__->R_TRIG0,retain);
  __INIT_VAR(data__->BUTTON_PRESSED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void TEST1_body__(TEST1 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->TON0.,IN,,!(__GET_VAR(data__->S1,)));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->T10,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,S0,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TON1.,IN,,__GET_VAR(data__->S0,));
  __SET_VAR(data__->TON1.,PT,,__GET_VAR(data__->T10,));
  TON_body__(&data__->TON1);
  __SET_VAR(data__->,S1,,__GET_VAR(data__->TON1.Q,));
  __SET_VAR(data__->R_TRIG0.,CLK,,__GET_VAR(data__->BUTTON,));
  R_TRIG_body__(&data__->R_TRIG0);
  __SET_VAR(data__->,BUTTON_PRESSED,,__GET_VAR(data__->R_TRIG0.Q,));

  goto __end;

__end:
  return;
} // TEST1_body__() 





