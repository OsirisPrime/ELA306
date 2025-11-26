TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM Lab2
  VAR
    Potentiometer : UINT := 0;
    Ljussensor : UINT;
  END_VAR
  VAR
    S0 : BOOL := False;
    S1 : BOOL := False;
    Light_sample : BOOL := False;
    Poten_sample : BOOL;
    Light_comp : UINT := 32768;
    Damaged : UINT := 0;
    High : UINT := 43690;
    Low : UINT := 21845;
  END_VAR
  VAR
    Relay : BOOL := 0;
  END_VAR
  VAR
    CTU0 : CTU;
    TON0 : TON;
    T50ms : TIME := T#50ms;
    Tick_100ms : BOOL := 0;
    Fifty_ticks : INT := 50;
    TON1 : TON;
    R_TRIG0 : R_TRIG;
    F_TRIG0 : F_TRIG;
    R_TRIG1 : R_TRIG;
    _TMP_GE6_OUT : BOOL;
    _TMP_EQ31_OUT : BOOL;
    _TMP_GT34_OUT : BOOL;
    _TMP_LT35_OUT : BOOL;
    _TMP_EQ42_OUT : BOOL;
    _TMP_OR40_OUT : BOOL;
    _TMP_NOT41_OUT : BOOL;
  END_VAR

  TON0(IN := NOT(S0), PT := T50ms);
  R_TRIG0(CLK := TON0.Q);
  F_TRIG0(CLK := TON0.Q);
  Tick_100ms := F_TRIG0.Q OR R_TRIG0.Q;
  R_TRIG1(CLK := Tick_100ms);
  CTU0(CU := R_TRIG1.Q, R := CTU0.Q, PV := Fifty_ticks);
  Light_sample := CTU0.Q;
  TON1(IN := S1, PT := T50ms);
  S0 := TON1.Q;
  S1 := TON0.Q;
  Poten_sample := Tick_100ms;
  _TMP_GE6_OUT := GE(Ljussensor, Light_comp);
  _TMP_EQ31_OUT := EQ(Ljussensor, Damaged);
  _TMP_GT34_OUT := GT(Potentiometer, High);
  _TMP_LT35_OUT := LT(Potentiometer, Low);
  _TMP_EQ42_OUT := EQ(Potentiometer, Damaged);
  _TMP_OR40_OUT := OR(_TMP_GT34_OUT, _TMP_LT35_OUT, _TMP_EQ42_OUT);
  _TMP_NOT41_OUT := NOT(_TMP_OR40_OUT);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Lab2;
  END_RESOURCE
END_CONFIGURATION
