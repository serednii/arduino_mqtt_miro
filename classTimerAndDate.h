class TimerDate {
  public:
    word delaySecondStart;
    unsigned long data_datamiliseconds[10];
    word data_rik[10];
    byte data_months[10];
    byte data_dey[10];
    byte data_godyna[10];
    byte data_minut[10];
    byte data_daywikend[10];
    byte godyna[50];
    byte minut[50];
    byte dey[35];
};

TimerDate dataAndTime[NUMBER_RELE];
String objectToJsonDate(TimerDate obj, byte num, byte numberPackege);
