//********************WRITE EEPROM****************************
void writeEeprom()
{
  String ssidTemp, passTemp;
  int sectionEeprom = START_SECTION_EEPROM_SSID_AND_PASSWORD;

  for (int i = 0; i < NUMBER_CLIENT_CONNECT; i++)
  {
    ssidTemp = arraySsidInput[i];
    passTemp = arrayPasswordInput[i];
//    Serial.print("passTemp  ");
//    Serial.println(passTemp);
//    Serial.print("ssidTemp  ");
//    Serial.println(ssidTemp);

    for (int j = 0; j < LENGTH_SSID; j++)
    {
      if (j < ssidTemp.length())
      {
        EEPROM.write(j + sectionEeprom, ssidTemp[j]); //Записуємо в память ssid
      }
      else
      {
        EEPROM.write(j + sectionEeprom, 0);
      }
    }


    for (int j = LENGTH_SSID; j < LENGTH_SSID + LENGTH_PASSWORD; j++)
    {
      if (j - LENGTH_SSID < passTemp.length())
      {
        EEPROM.write(j + sectionEeprom, passTemp[j - LENGTH_SSID]); //Записуємо в память password
      }
      else
      {
        EEPROM.write(j + sectionEeprom, 0);
      }
    }

    sectionEeprom += LENGTH_SSID + LENGTH_PASSWORD;
  }
  comitEprom();
}
//*************************************************************************************************************************************************

//********************READ EEPROM******************************
void readEeprom()
{
  int sectionEeprom = START_SECTION_EEPROM_SSID_AND_PASSWORD;
  //-----------------------------------------

  for (int i = 0; i < NUMBER_CLIENT_CONNECT; i++)
  {
    arraySsid[i] = "";
    arrayPassword[i] = "";

    for (int j = 0; j < LENGTH_SSID; j++)
    {
      byte ss = EEPROM.read(j + sectionEeprom);
      if (!(ss == 0))arraySsid[i] += char(ss);
    }


    for (int j = LENGTH_SSID; j < LENGTH_SSID + LENGTH_PASSWORD; j++)
    {
      byte pas = EEPROM.read(j + sectionEeprom);
      if (!(pas == 0))arrayPassword[i] += char(pas);
    }



    sectionEeprom += LENGTH_SSID + LENGTH_PASSWORD;
  }
}
//*******************READ EEPROM****************************


//*************************************************************************************************************************************************
void readEEPROMTimerToObjeckt() { // Читаємо дані з памяті еепром в обєкт
  for (int i = 0; i < 8; i++) {
    EEPROM.get(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate)*i) , dataAndTime[i]);
  }
}
//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
void clearEepromDate(byte relayNumber) {
  byte x = 99;
  dataAndTime[relayNumber].delaySecondStart = 65535;
  for (int i = 0; i < 10; i++) {
    dataAndTime[relayNumber].data_datamiliseconds[i] = 4294967295;
    dataAndTime[relayNumber].data_rik[i] = 65535;
    dataAndTime[relayNumber].data_months[i] = x;
    dataAndTime[relayNumber].data_dey[i] = x;
    dataAndTime[relayNumber].data_godyna[i] = x;
    dataAndTime[relayNumber].data_minut[i] = x;
    dataAndTime[relayNumber].data_daywikend[i] = x;
  }

  for (int i = 0; i < 50; i++) {
    dataAndTime[relayNumber].godyna[i] = x;
    dataAndTime[relayNumber].minut[i] = x;
  }

  for (int i = 0; i < 35; i++) {
    dataAndTime[relayNumber].dey[i] = x;
  }

  EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate)*relayNumber), dataAndTime[relayNumber]); //write objeck to EEPROM
  comitEprom();
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
void writeStringEeprom(word beginByteEeprom, word maxLengthString, String str, word symbol ) {
  //beginByteEeprom Початковий адресс
  //maxLengthString Виділена память під строку
  //str строка
  //symbol код символа яким заповняємо остаток памяті в EEPROM

  for (word k = 0; k < maxLengthString; k++)
  {
    if (k < str.length()) {
      String cc = str.substring(k, k + 1);
      char char_array[2];
      cc.toCharArray(char_array, 2);
      EEPROM.write(beginByteEeprom + k, (byte)char_array[0]);
    } else {
      EEPROM.write(beginByteEeprom + k, symbol);
    }
  }

  comitEprom();
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
//read eeprom string Читає с EEPROM строку певної довжини
String readStringEeprom(int beginByteEeprom, int lengthString ) {
  String tempString;
  for (int i = 0; i < lengthString; i++)
  {
    int addd = beginByteEeprom + i;
    byte data = EEPROM.read(addd);
    if (data > 0)tempString += char(data);
  }
  return tempString;
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
void comitEprom()
{
  if (EEPROM.commit())
  {
    Serial.println("EEPROM successfully committed");
  }
  else
  {
    Serial.println("ERROR! EEPROM commit failed");
  }
}
//*************************************************************************************************************************************************
