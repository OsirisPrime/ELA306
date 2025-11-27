PROGRAM Lab2
  VAR
    Potentiometer AT %IW1 : UINT := 1;
    Ljussensor AT %IW2 : UINT := 1;
  END_VAR
  VAR
    S0 : BOOL := False;
    S1 : BOOL := False;
    Light_sample : BOOL := False;
    Poten_sample : BOOL;
    Light_damaged : BOOL := False;
    Poten_damaged : BOOL := False;
    Dark : BOOL := False;
    Bright : BOOL := False;
    High : BOOL := False;
    Medium : BOOL := False;
    Low : BOOL := False;
    Damaged_comp : UINT := 0;
    Light_comp : UINT := 32768;
    High_comp : UINT := 43690;
    Low_comp : UINT := 21845;
  END_VAR
  VAR
    Relay AT %QX0.0 : BOOL := 0;
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
    _TMP_EQ31_OUT : BOOL;
    _TMP_GE6_OUT : BOOL;
    _TMP_LE46_OUT : BOOL;
    _TMP_GT34_OUT : BOOL;
    _TMP_LT35_OUT : BOOL;
    _TMP_EQ42_OUT : BOOL;
    _TMP_OR40_OUT : BOOL;
    _TMP_NOT41_OUT : BOOL;
    _TMP_AND59_OUT : BOOL;
    _TMP_AND60_OUT : BOOL;
    _TMP_AND63_OUT : BOOL;
    _TMP_AND62_OUT : BOOL;
    _TMP_AND69_OUT : BOOL;
    _TMP_AND68_OUT : BOOL;
    _TMP_AND71_OUT : BOOL;
    _TMP_AND75_OUT : BOOL;
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
  _TMP_EQ31_OUT := EQ(Ljussensor, Damaged_comp);
  IF Light_sample AND _TMP_EQ31_OUT THEN
    Light_damaged := TRUE; (*set*)
  END_IF;
  _TMP_GE6_OUT := GE(Ljussensor, Light_comp);
  Bright := Light_sample AND _TMP_GE6_OUT;
  _TMP_LE46_OUT := LE(Ljussensor, Light_comp);
  Dark := Light_sample AND _TMP_LE46_OUT;
  _TMP_GT34_OUT := GT(Potentiometer, High_comp);
  High := Poten_sample AND _TMP_GT34_OUT;
  _TMP_LT35_OUT := LT(Potentiometer, Low_comp);
  Low := Poten_sample AND _TMP_LT35_OUT;
  _TMP_EQ42_OUT := EQ(Potentiometer, Damaged_comp);
  _TMP_OR40_OUT := OR(_TMP_GT34_OUT, _TMP_LT35_OUT, _TMP_EQ42_OUT);
  _TMP_NOT41_OUT := NOT(_TMP_OR40_OUT);
  Medium := Poten_sample AND _TMP_NOT41_OUT;
  Poten_damaged := Poten_sample AND _TMP_EQ42_OUT;
  _TMP_AND59_OUT := AND(Low AND NOT(Light_damaged), Bright AND NOT(Light_damaged));
  _TMP_AND60_OUT := AND(Bright AND NOT(Light_damaged), Medium AND NOT(Light_damaged));
  _TMP_AND63_OUT := AND(Dark AND NOT(Light_damaged), High AND NOT(Light_damaged));
  _TMP_AND62_OUT := AND(Medium AND NOT(Light_damaged), Dark AND NOT(Light_damaged));
  IF _TMP_AND59_OUT OR _TMP_AND60_OUT OR _TMP_AND62_OUT OR _TMP_AND63_OUT THEN
    Relay := TRUE; (*set*)
  END_IF;
  _TMP_AND69_OUT := AND(Bright AND NOT(Light_damaged), Poten_damaged AND NOT(Light_damaged));
  _TMP_AND68_OUT := AND(High AND NOT(Light_damaged), Bright AND NOT(Light_damaged));
  _TMP_AND71_OUT := AND(Poten_damaged AND NOT(Light_damaged), Dark AND NOT(Light_damaged));
  IF _TMP_AND68_OUT OR _TMP_AND69_OUT OR _TMP_AND71_OUT THEN
    Relay := FALSE; (*reset*)
  END_IF;
  _TMP_AND75_OUT := AND(Dark, Low);
  IF Light_damaged OR _TMP_AND75_OUT THEN
    Relay := FALSE; (*reset*)
  END_IF;
  IF _TMP_AND75_OUT THEN
    Light_damaged := TRUE; (*set*)
  END_IF;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Lab2;
  END_RESOURCE
END_CONFIGURATION
