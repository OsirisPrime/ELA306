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


PROGRAM Lab1
  VAR
    btn : BOOL := False;
  END_VAR
  VAR
    AllowedPress : BOOL := False;
    pressed : BOOL := False;
    Ped_wait : BOOL := False;
    Pedestrian : BOOL := False;
  END_VAR
  VAR
    north : BOOL := False;
    south : BOOL := False;
    west : BOOL := False;
    east : BOOL := False;
  END_VAR
  VAR
    state : BOOL := False;
    S0 : BOOL := False;
    S1 : BOOL := False;
    T10 : TIME := T#10s;
    T80 : TIME := T#40s;
    Allowed_timer : BOOL := False;
    Timer_cooldown : BOOL := False;
    FF1 : BOOL := False;
    FF2 : BOOL := False;
    FF_output : BOOL := False;
    TON0 : TON;
    TON1 : TON;
    TP0 : TP;
    TP1 : TP;
    R_TRIG1 : R_TRIG;
    R_TRIG0 : R_TRIG;
    R_TRIG2 : R_TRIG;
    R_TRIG3 : R_TRIG;
    R_TRIG4 : R_TRIG;
    R_TRIG5 : R_TRIG;
  END_VAR

  TON0(IN := NOT(S1) AND NOT(Pedestrian), PT := T10);
  S0 := TON0.Q;
  TON1(IN := S0 AND NOT(Pedestrian), PT := T10);
  S1 := TON1.Q;
  R_TRIG1(CLK := S1);
  R_TRIG0(CLK := S0);
  IF NOT(FF1) AND (R_TRIG0.Q OR R_TRIG1.Q) THEN
    FF1 := TRUE; (*set*)
  END_IF;
  R_TRIG2(CLK := S0);
  R_TRIG3(CLK := S1);
  IF FF1 AND FF_output AND (R_TRIG2.Q OR R_TRIG3.Q) THEN
    FF1 := FALSE; (*reset*)
  END_IF;
  FF_output := FF1;
  north := NOT(FF_output) AND NOT(Pedestrian);
  south := NOT(FF_output) AND NOT(Pedestrian);
  east := FF_output AND NOT(Pedestrian);
  west := FF_output AND NOT(Pedestrian);
  pressed := btn;
  AllowedPress := NOT(Timer_cooldown) AND pressed;
  TP0(IN := AllowedPress, PT := T80);
  Timer_cooldown := TP0.Q;
  IF AllowedPress THEN
    Ped_wait := TRUE; (*set*)
  END_IF;
  R_TRIG5(CLK := S1);
  R_TRIG4(CLK := S0);
  TP1(IN := Ped_wait AND (R_TRIG4.Q OR R_TRIG5.Q), PT := T10);
  IF TP1.Q THEN
    Ped_wait := FALSE; (*reset*)
  END_IF;
  Pedestrian := TP1.Q;
END_PROGRAM

PROGRAM Test1
  VAR
    TON0 : TON;
    S1 : BOOL;
    S0 : BOOL;
    State : BOOL := False;
    Button : BOOL := False;
    T80 : TIME := T#80s;
    TON1 : TON;
    T10 : TIME := T#10s;
    R_TRIG0 : R_TRIG;
    Button_pressed : BOOL;
  END_VAR

  TON0(IN := NOT(S1), PT := T10);
  S0 := TON0.Q;
  TON1(IN := S0, PT := T10);
  S1 := TON1.Q;
  R_TRIG0(CLK := Button);
  Button_pressed := R_TRIG0.Q;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Lab1;
  END_RESOURCE
END_CONFIGURATION
