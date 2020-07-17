PROGRAM io_esp_01
  VAR
    IN AT %IX100.0 : BOOL;
    OUT AT %QX100.3 : BOOL;
  END_VAR

  OUT := IN;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : io_esp_01;
  END_RESOURCE
END_CONFIGURATION