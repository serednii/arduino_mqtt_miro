//class GetDate {
//  public:
//    time_t epochTime;
//    String formattedTime;
//    int currentHour;
//    int currentMinute;
//    int currentSecond;
//    int weekDayNumber;
//    String weekDay;
//    int monthDay;
//    int currentMonth;
//    String currentMonthName;
//    int currentYear;
//    String currentDate;
//};
//GetDate getDate;


void getDateTime() {
  timeClient.update();
  //
  //  Serial.println();
  //  Serial.println("------------------------------");

  getDate.epochTime = timeClient.getEpochTime() - 7196;
  getDate.formattedTime = timeClient.getFormattedTime();
  getDate.currentHour = timeClient.getHours();
  getDate.currentMinute = timeClient.getMinutes();
  getDate.currentSecond = timeClient.getSeconds();
  getDate.weekDayNumber = timeClient.getDay();
  getDate.weekDay = getDate.weekDays[getDate.weekDayNumber];
  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&getDate.epochTime);
  getDate.monthDay = ptm->tm_mday;
  getDate.currentMonth = ptm->tm_mon + 1;
  getDate.currentMonthName = getDate.months[getDate.currentMonth - 1];
  getDate.currentYear = ptm->tm_year + 1900;
  //Print complete date:
  getDate.currentDate = String(getDate.currentYear) + "-" + String(getDate.currentMonth) + "-" + String(getDate.monthDay);

//    Serial.print("Epoch Time: ");
//    Serial.println(getDate.epochTime);
//    Serial.print("Formatted Time: ");
//    Serial.println(getDate.formattedTime);
//    Serial.print("Hour: ");
//    Serial.println(getDate.currentHour);
//    Serial.print("Minutes: ");
//    Serial.println(getDate.currentMinute);
//    Serial.print("Seconds: ");
//    Serial.println(getDate.currentSecond);
//    Serial.print("Week Day Number: ");
//    Serial.println(getDate.weekDayNumber);
//    Serial.print("Week Day: ");
//    Serial.println(getDate.weekDay);
//    Serial.print("Month day: ");
//    Serial.println(getDate.monthDay);
//    Serial.print("Month: ");
//    Serial.println(getDate.currentMonth);
//    Serial.print("Month name: ");
//    Serial.println(getDate.currentMonthName);
//    Serial.print("Year: ");
//    Serial.println(getDate.currentYear);
//    Serial.print("Current date: ");
//    Serial.println(getDate.currentDate);

//    Serial.println("------------------------------");
//    Serial.println();
}


//******************************************************************************
byte controlRangeHour( byte numberRele, byte numberDataTime) {

  boolean  SubTimersFlagSections[5];//флаги для годин в секції
  for (byte numberTime = 0; numberTime < 9; numberTime += 2  ) { //numberTime 0 2 4 6 8) {//провіряємо в секії всі години і для кожної ставимо флаг
    word tempGod_0 = dataAndTime[numberRele].godyna[numberTime + numberDataTime * 5];
    word tempGod_1 = dataAndTime[numberRele].godyna[numberTime + numberDataTime * 5 + 1];
    word tempMinute_0 = dataAndTime[numberRele].minut[numberTime + numberDataTime * 5];
    word tempMinute_1 = dataAndTime[numberRele].minut[numberTime + numberDataTime * 5 + 1];
    word tempGodStart = tempGod_0 * 60 + tempMinute_0;
    word tempGodStop = tempGod_1 * 60 + tempMinute_1;
    word tempCurentGod = getDate.currentHour * 60 + getDate.currentMinute;


    if (tempGodStart <= tempCurentGod  &&  tempGodStop > tempCurentGod)
    {
      digitalWrite(releControl[numberRele].numberPin, ChangeLow);
      SubTimersFlagSections[numberTime / 2] = true;
    } else {
      digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
      SubTimersFlagSections[numberTime / 2] = false;
    }
  }

  //   0 2 4 6 8   0-6   7-13   14-20    21-27   28 - 34
  //   0 1 2 3 4
  //   1 2 3 4 5
  //getDate.weekDay
  //dataAndTime[numberRele].dey[]
  boolean flagDey;
  int tempweekDayNumber = getDate.weekDayNumber - 1;

  if (tempweekDayNumber == -1)tempweekDayNumber = 6;

  if (dataAndTime[numberRele].dey[tempweekDayNumber + numberDataTime / 2 * 7] == 1) {
    flagDey = true;
//    Serial.println("flagDey --true");
  } else {
    flagDey = false;
  }

  //Провіряємо флаги всіх годин даної секції і якщо хощаб одина дорівнює true то  timersFlagSections = true
  if ((SubTimersFlagSections[0] || SubTimersFlagSections[1] || SubTimersFlagSections[2] || SubTimersFlagSections[3] || SubTimersFlagSections[4]) && flagDey ) {
    return  1;
  } else {
    return  0;
  }
}




//*****************************************************************************
boolean controlRangeDate(byte numberRele, byte numberDataTime) {
  if (dataAndTime[numberRele].data_datamiliseconds[numberDataTime] <= (getDate.epochTime)  &&    dataAndTime[numberRele].data_datamiliseconds[numberDataTime + 1] >= (getDate.epochTime) )
  {
    //    Serial.print("RELE DATA VKL:");
    //    Serial.println(numberRele);
    return true;
  } else {
    //    Serial.print("RELE DATA OTKL:");
    //    Serial.println(numberRele);
    return false;
  }
}
//******************************************************************************












//void deleteAndMovingSection(byte numberRele) {
//  for (byte x = 0; x < 9; x += 2) {
//    if (dataAndTime[numberRele].data_datamiliseconds[x + 1] < (getDate.epochTime)) { //Якщо  елемент з датою  простроченo
//      deleteOldDate(numberRele, x);//Видаляємо прострочену секцію
//      for (byte startSection = x + 2; startSection < 9; startSection += 2 ) {
//        //        Serial.print("data_datamiliseconds:<><><><><><><> ");
//        //        Serial.println(startSection);
//        //        Serial.println(startSection - 2);
//        movingSection(numberRele,  startSection,  startSection - 2);
//      }
//      deleteOldDate(numberRele, 8);//Видаляємо останню секцію
//      EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(timerDate)*numberRele), dataAndTime[numberRele]); //write objeck to EEPROM
//      comitEprom();
//      x -= 2; //Повторно перевіряємо ту саму мекцію адже на її місце приїхали нові дані
//      //      client.publish(nameUser+"_out-web-rele-data-time", objectToJsonDate(dataAndTime[numberRele], numberRele));
//    }
//  }
//
//}

//void deleteOldDate(byte numberRele, byte numberDataTime) {
//  //  Serial.print("delete the old date:");
//  dataAndTime[numberRele].data_datamiliseconds[numberDataTime] = 4294967295;
//  dataAndTime[numberRele].data_datamiliseconds[numberDataTime + 1] = 4294967295;
//  dataAndTime[numberRele].data_rik[numberDataTime] = 65535;
//  dataAndTime[numberRele].data_rik[numberDataTime + 1] = 65535;
//  dataAndTime[numberRele].data_months[numberDataTime] = 99;
//  dataAndTime[numberRele].data_months[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_dey[numberDataTime] = 99;
//  dataAndTime[numberRele].data_dey[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_godyna[numberDataTime] = 99;
//  dataAndTime[numberRele].data_godyna[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_minut[numberDataTime] = 99;
//  dataAndTime[numberRele].data_minut[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_daywikend[numberDataTime] = 99;
//  dataAndTime[numberRele].data_daywikend[numberDataTime + 1] = 99;
//
//  for (byte i = 0; i < 10; i++ ) {
//    dataAndTime[numberRele].godyna[numberDataTime * 5 + i] = 99;
//    dataAndTime[numberRele].minut[numberDataTime * 5 + i] = 99;
//    if (i < 7)dataAndTime[numberRele].dey[numberDataTime * 5 + i] = 0;
//  }
//}

//void movingSection(byte numberRele, byte numberSectionStart, byte numberSectionEnd) {
//  //  Serial.println("movingSection:");
//  dataAndTime[numberRele].data_datamiliseconds[numberSectionEnd] = dataAndTime[numberRele].data_datamiliseconds[numberSectionStart];
//  dataAndTime[numberRele].data_datamiliseconds[numberSectionEnd + 1] = dataAndTime[numberRele].data_datamiliseconds[numberSectionStart + 1];
//  dataAndTime[numberRele].data_rik[numberSectionEnd] =  dataAndTime[numberRele].data_rik[numberSectionStart];
//  dataAndTime[numberRele].data_rik[numberSectionEnd + 1] = dataAndTime[numberRele].data_rik[numberSectionStart + 1];
//  dataAndTime[numberRele].data_months[numberSectionEnd] = dataAndTime[numberRele].data_months[numberSectionStart];
//  dataAndTime[numberRele].data_months[numberSectionEnd + 1] = dataAndTime[numberRele].data_months[numberSectionStart + 1];
//  dataAndTime[numberRele].data_dey[numberSectionEnd] = dataAndTime[numberRele].data_dey[numberSectionStart];
//  dataAndTime[numberRele].data_dey[numberSectionEnd + 1] = dataAndTime[numberRele].data_dey[numberSectionStart + 1];
//  dataAndTime[numberRele].data_godyna[numberSectionEnd] = dataAndTime[numberRele].data_godyna[numberSectionStart];
//  dataAndTime[numberRele].data_godyna[numberSectionEnd + 1] = dataAndTime[numberRele].data_godyna[numberSectionStart + 1];
//  dataAndTime[numberRele].data_minut[numberSectionEnd] = dataAndTime[numberRele].data_minut[numberSectionStart] ;
//  dataAndTime[numberRele].data_minut[numberSectionEnd + 1] = dataAndTime[numberRele].data_minut[numberSectionStart + 1];
//  dataAndTime[numberRele].data_daywikend[numberSectionEnd] = dataAndTime[numberRele].data_daywikend[numberSectionStart];
//  dataAndTime[numberRele].data_daywikend[numberSectionEnd + 1] = dataAndTime[numberRele].data_daywikend[numberSectionStart + 1];
//
//  for (byte i = 0; i < 10; i++ ) {
//    dataAndTime[numberRele].godyna[numberSectionEnd * 5 + i] = dataAndTime[numberRele].godyna[numberSectionStart * 5 + i];
//    dataAndTime[numberRele].minut[numberSectionEnd * 5 + i] = dataAndTime[numberRele].minut[numberSectionStart * 5 + i];
//    if (i < 7)dataAndTime[numberRele].dey[numberSectionEnd * 5 + i] = dataAndTime[numberRele].dey[numberSectionStart * 5 + i];
//  }
//}
