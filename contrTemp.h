byte ChangeLow, ChangeHIGH;


void kontr_temp()
{

  //  Serial.print(" СonnectedInternet ");
  //  Serial.println(connectedInternet);
  getDateTime();
  //    Serial.println("start readSensorsAddressTemp");
  readSensorsAddressTemp();//читаємо address з датчиків в обєкт ds18b20
  //  Serial.println("stop readSensorsAddressTemp ");
  // readEepromAddress();//читаємо address з памяті ЕЕПРОМ  в обєкт ds18b20EEprom
  byte  stanRele = 0;
  //  Serial.println();
  //  Serial.println();
  for (int numberRele = 0; numberRele < 8; numberRele++)// перебираємо всі реле
  {
    if (releControl[numberRele].manualAuto == 0) {
      //Якщо неручний режим


      //            Serial.println("*********************************************************");
      //            Serial.println(" AUTO ");

      //********************Реверс реле************************
      if (releControl[numberRele].bit5OnOffChange == 0) {//Реверс реле
        ChangeLow = 1;
        ChangeHIGH = 0;
      } else if (releControl[numberRele].bit5OnOffChange == 1) {
        ChangeLow = 0;
        ChangeHIGH = 1;
      }
      //********************Реверс реле************************


      //********************CONTROL TERMO SENSOR************************
      if (releControl[numberRele].numberSensorControl < 15 )//Якщо керуємо термодатчиком то в змінну буле записано номер термодатчика від 0 до 8 замість числа 15 - неуправляємо нічим
      {
        //Превірка чи підключений термодатчик яким управляємо реле, що записаний в памяті EEPROM

        boolean flag = true;
        for (int k = 0; k < deviceCountSensor; k++) {

          if (ds18b20EEprom[releControl[numberRele].numberSensorControl].strAddress == ds18b20[k].strAddress) { //Найдено сенсор який є в памяті EEPROM
            Serial.print("Kontrol sensor rele ");
            Serial.println(numberRele);
            releControl[numberRele].errorSensor = false;
            if (releControl[numberRele].bit4OneOrTwoRange == 0) {//Один діапазон
              if (ds18b20[k].temp > ds18b20[numberRele].tempVkl)
              {
                releControl[numberRele].flagsTermo = true;
              } else {
                releControl[numberRele].flagsTermo = false;
              }
            } else if (releControl[numberRele].bit4OneOrTwoRange == 1) {//Два діапазони
              if (ds18b20[k].temp > ds18b20[numberRele].tempVkl && ds18b20[k].temp < ds18b20[numberRele].tempOtkl)
              {
                releControl[numberRele].flagsTermo = true;
              } else {
                releControl[numberRele].flagsTermo = false;
              }
            }
            break;
          } else {
            Serial.print("NOT SENSOR ");
            Serial.println(numberRele);
            releControl[numberRele].errorSensor = true;
          }

        }
        //      if (flag)Serial.println("Send messeg not sensor");
      }
      else {

      }
      //********************CONTROL TERMO SENSOR************************

      boolean  timersFlagSections[5];//
      timersFlagSections[0] = false;
      timersFlagSections[1] = false;
      timersFlagSections[2] = false;
      timersFlagSections[3] = false;
      timersFlagSections[4] = false;

      for (byte numberDataTime = 0; numberDataTime < 9; numberDataTime += 2  ) { //numberDataTime 0 2 4 6 8     0 10 20 30 40

        if (dataAndTime[numberRele].data_datamiliseconds[numberDataTime] != 4294967295  &&  dataAndTime[numberRele].godyna[numberDataTime * 5] < 24)//Якщо в секції вибрано і  дата і година
        {

          if (controlRangeDate(numberRele, numberDataTime) && controlRangeHour(numberRele, numberDataTime)) {
            timersFlagSections[numberDataTime / 2] = true;
          }
          else {
            timersFlagSections[numberDataTime / 2] = false;
          }

        } else if (dataAndTime[numberRele].data_datamiliseconds[numberDataTime] != 4294967295)//Якщо в секції вибрана дата
        {

          timersFlagSections[numberDataTime / 2] = controlRangeDate(numberRele, numberDataTime);
        } else if (dataAndTime[numberRele].godyna[numberDataTime * 5] != 99) //Якщо в секції вибрана година
        {

          timersFlagSections[numberDataTime / 2] = controlRangeHour(numberRele, numberDataTime );
        } else
        {
          //            releControl[numberRele].timerControl = 0;
        }

        //Провіряємо флаги всіх блоків даного реле і якщо хоща б один дорівнює true то  flagsTimer = true
        //          Serial.print("timersFlagSections change:  ");
        //          Serial.print(timersFlagSections[0]);
        //          Serial.print("  ");
        //          Serial.print(timersFlagSections[1]);
        //          Serial.print("  ");
        //          Serial.print(timersFlagSections[2]);
        //          Serial.print("  ");
        //          Serial.print(timersFlagSections[3]);
        //          Serial.print("  ");
        //          Serial.println(timersFlagSections[4]);
        //
        //          Serial.print("flagsTimer:  ");
        //          Serial.println(releControl[numberRele].flagsTimer);

        if (timersFlagSections[0] ||  timersFlagSections[1] ||  timersFlagSections[2] ||  timersFlagSections[3] ||  timersFlagSections[4]) {
          releControl[numberRele].flagsTimer = true;
          //            Serial.println(releControl[numberRele].flagsTimer);
        } else {
          releControl[numberRele].flagsTimer = false;
          //            Serial.println(releControl[numberRele].flagsTimer);
        }
        //          Serial.print("flagsTimer change:  ");
        //          Serial.println(releControl[numberRele].flagsTimer);
      }
      //        Serial.println("OUOUOIUOIUOIUOIUOI  ");
      //        Serial.println(dataAndTime[numberRele].godyna[0]);
      //        Serial.println(dataAndTime[numberRele].godyna[10]);
      //        Serial.println(dataAndTime[numberRele].godyna[20]);
      //        Serial.println(dataAndTime[numberRele].godyna[30]);
      //        Serial.println(dataAndTime[numberRele].godyna[40]);
      //        Serial.println();


      if (dataAndTime[numberRele].data_datamiliseconds[0] != 4294967295  || dataAndTime[numberRele].data_datamiliseconds[2] != 4294967295 ||
          dataAndTime[numberRele].data_datamiliseconds[4] != 4294967295 || dataAndTime[numberRele].data_datamiliseconds[6] != 4294967295 ||
          dataAndTime[numberRele].data_datamiliseconds[8] != 4294967295 ||
          dataAndTime[numberRele].godyna[0] < 24 || dataAndTime[numberRele].godyna[10] < 24 || 
          dataAndTime[numberRele].godyna[20] < 24 || dataAndTime[numberRele].godyna[30] < 24 || 
          dataAndTime[numberRele].godyna[40] < 24) {
          releControl[numberRele].timerControl = 1;
        Serial.println("TIMER CONTROL GLOBAL ++++");
      } else {
        releControl[numberRele].timerControl = 0;
        //        Serial.println("TIMER CONTROL GLOBAL ----");
      }
      //********************CONTROL TIMER*******************************

      //********************CONTROL DELAY*******************************
      //      if (releControl[numberRele].timerControl > 0 )//Затримка при включенні якщо значення паузи 0 то постфйно включене якщо ні то чекаємо
      //      {
      //        releControl[numberRele].flagsTimer = false;
      //      }
      //********************CONTROL DELAY*******************************

      //********************CONTROL FLAGS*******************************
      if (releControl[numberRele].numberSensorControl < 15 && releControl[numberRele].timerControl == 1)   //Якщо реле регул двома
      {
        Serial.println("CONTROL  TIME AND SENSOR::::::::::::  ");
        Serial.println("numberSensorControl::::::::::::  ");
        Serial.println(releControl[numberRele].numberSensorControl);
        Serial.println("CONTROL  TIME AND SENSOR::::::::::::  ");
        if (!releControl[numberRele].errorSensor  && connectedInternet) {// Якщо датчик присутній  і є година з інтернету
          if (releControl[numberRele].flagsTermo &&  releControl[numberRele].flagsTimer) {
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          } else {
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
          }
        } else {// Якщо датчик помилка
          if (releControl[numberRele].bit6ReleError == 1)
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          else if (releControl[numberRele].bit6ReleError == 0)
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
        }

      } else if (releControl[numberRele].numberSensorControl < 15) {   //Якщо реле регул termo
        Serial.println("CONTROL  SENSOR ::::::::::::  ");

        if (!releControl[numberRele].errorSensor) {// Якщо датчик присутній
          if (releControl[numberRele].flagsTermo) {
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          } else {
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
          }
        } else {// Якщо датчик помилка
          if (releControl[numberRele].bit6ReleError == 1)
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          else if (releControl[numberRele].bit6ReleError == 0)
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
        }
      } else if (releControl[numberRele].timerControl == 1) {   //Якщо реле регул timer

        if (connectedInternet) {// Якщо є година з інтернету
          Serial.println("CONTROL  TIME ::::::::::::  ");
          if (releControl[numberRele].flagsTimer) {
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          } else {
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
          }
        } else {// Якщо година з інтернету помилка неррацює інтернет
          if (releControl[numberRele].bit6ReleError == 1)
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          else if (releControl[numberRele].bit6ReleError == 0)
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
        }

      } else { //Якщо реле нічого не регулює то ми його відключаємо
        Serial.println("NOT CONTROL RELE ::::::::::::  ");
        digitalWrite(releControl[numberRele].numberPin, 1);
      }
      //********************CONTROL FLAGS*******************************
      //        deleteAndMovingSection(numberRele);// Очистка пустої або простроченої дати
      //      Serial.println();
      //      Serial.println("*********************************************************");


    } else { //при ручному режимі
      //      Serial.print(" MANUAL MANUAL  ");
      if (releControl[numberRele].onOffManual == 0)
        digitalWrite(releControl[numberRele].numberPin, 1);
      else
        digitalWrite(releControl[numberRele].numberPin, 0);
    }
    digitalRead(releControl[numberRele].numberPin) == 0 ?  stanRele &= ~(1 << numberRele) : stanRele |= (1 << numberRele);//Для кожного реле читаємо в якому воно стані і записуємо певний біт
    //    digitalRead(releControl[numberRele].numberPin) == 0 ? releControl[numberRele].setOnOffManualEEPROM(1, numberRele) : releControl[numberRele].setOnOffManualEEPROM(0, numberRele);

  }

  //  Serial.println();
  //  Serial.println();
  //Відправляємо стани всіх реле
  client.publish(nameUser + "_stanRele", String(stanRele));
  client.publish(nameUser + "analogInputA0", String(analogRead(A0)));
  //  Serial.print(" stanRele>>>>>>>>>>>><<<<<<<<<<<  ");
  //  Serial.println(stanRele, BIN);
}
