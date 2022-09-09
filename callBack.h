//--------------------------------------callback--------------------------------
//-----------------------------------------------------------------------------
//boolean blockGetMessega = false;
void callback(const MQTT::Publish & pub) //було
{
  Serial.print(pub.topic()); // выводим в сериал порт название топика
  Serial.print(" => ");
  Serial.println(pub.payload_string()); // выводим в сериал порт значение полученных данных
  String payload = pub.payload_string();

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_resetFunction") // перегрузка чипа
  {
    if (payload == "resetFunction")
      resetFunc(); //вызываем reset });
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_cleareEPROM") // перегрузка чипа
  {
    //0001-4096-255
    if (payload == "ff")
      for (int i = 1; i < 4096; i++) {
        EEPROM.write(i, 255);
      }
    if (payload == "00")
      for (int i = 1; i < 4096; i++) {
        EEPROM.write(i, 0);
      }
    comitEprom();
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_define_device") // міняєм імя пристрою
  {
    //    if(payload == "setDefineDevice"){
    Serial.print("GET mesage setDefineDevice  ----  ");
    //    Serial.println(payload);
    defineDevice();
    //    }
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_get_name_device") // получаєм нове імя приистрою
  {
    //    EEPROM_ADRESS_NAME_DEVICE
    if (payload.length() > 0 && payload.length() < 20) {
    }
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_set-rele-data-time") //прийом дати і часу
  {

    int numRele = parseStringToData(payload);
    EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate)*numRele), dataAndTime[numRele]); //write objeck to EEPROM
    comitEprom();
    readEEPROMTimerToObjeckt();

    for (byte numPak = 1; numPak < 5; numPak++)
      client.publish(nameUser + "_out-web-rele-data-time", objectToJsonDate(dataAndTime[numRele], numRele, numPak));
    kontr_temp();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_start-data-sensor-eepromAndDevice") // при запросі відправити в топік адреса EEPROM i реальних датчиків
  {
      prin("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
    refreshData();
    kontr_temp();
    if (payload == "readAddressSensor" || payload == "ALL")
    {
      sendSensorData();
      prin("readAddressSensor WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }

    //-------------------------------------------------------------------------
    
    if (payload == "releControl" || payload == "ALL")
    {
      client.publish(nameUser + "_rele_eprom_upr", EEPROMDataToJSONSensor());
      prin("releControl WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }

    //-------------------------------------------------------------------------

    if (payload == "ReadTempVklOtkl" || payload == "ALL" )
    {
      client.publish(nameUser + "_sensor-vkl-otkl", EEPROMDataToJSONOnOff());//send temp on temp off
       prin("ReadTempVklOtkl WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }

    //-------------------------------------------------------------------------
    
    if (payload == "ReadDate" || payload == "ALL" )
    {
      refreshobjectToJsonDate();
       prin("ReadDate WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }

    //-------------------------------------------------------------------------

    if (payload == "ReleManual" || payload == "ALL")
    {
      client.publish(nameUser + "_rele-out-eprom_upr-manual", objectToJSONRele(releControl, NUMBER_RELE, "manualAuto"));
       prin("ReleManual WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
      //      prin("**********************", objectToJSONRele(releControl, NUMBER_RELE, "manualAuto"));
    }
    
    //-------------------------------------------------------------------------
    
    if (payload == "NameSensor" || payload == "ALL")
    {
      client.publish(nameUser + "_sensor-name", ds18b20EEpromToJSONnameSensor());
       prin("NameSensor WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }

    //-------------------------------------------------------------------------

    if (payload == "NameRele" || payload == "ALL")
    {
      client.publish(nameUser + "_rele-name", objectToJSONRele(releControl, NUMBER_RELE, "nameRele"));
       prin("NameRele WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
      //      Serial.println(nameUser + "_rele-name  ---- ");
      //      Serial.println(objectToJSONRele(releControl, NUMBER_RELE, "nameRele"));
    }

  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_save-data-sensor-temp") // проверяем из нужного ли нам топика пришли данные
  {
    // 0v255o255k START_SECTION_EEPROM_TEMP_ON_OFF температуру вкл і відкл  для термодатчика
    String s = payload.substring(0, payload.indexOf('v')); //номер термодатчика
    String s1 = payload.substring(payload.indexOf('v') + 1, payload.indexOf('o')); //перша температура
    String s2 = payload.substring(payload.indexOf('o') + 1, payload.indexOf('k')); //друга температура
    int a = s.toInt() * 2 + START_SECTION_EEPROM_TEMP_ON_OFF;
    EEPROM.write(a, s1.toInt() + 50);
    EEPROM.write(a + 1, s2.toInt() + 50);
    comitEprom();
    refreshData();
    kontr_temp();
    client.publish(nameUser + "_start-data-sensor-eepromAndDevice", "ReadTempVklOtkl");
    Serial.print("Send mesage ReadTempVklOtkl");
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_save-rele-name") // проверяем из нужного ли нам топика пришли данные
  {
    //    const byte kilkistyBukv = 20;
    // 0vname1k START_SECTION_EEPROM_RELE_NAME //Зберігаємо імя реле

    //    Serial.println(payload);
    byte numberRele = payload.substring(0, payload.indexOf("*#*")).toInt(); //номер реле
    String nameRele = payload.substring(payload.indexOf("*#*") + 3, payload.indexOf("*&*")); //імя реле
    int address = numberRele * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR + START_SECTION_EEPROM_RELE_NAME;

    writeStringEeprom(address, MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR, nameRele, 0);
    client.publish(nameUser + "_start-data-sensor-eepromAndDevice", "NameRele");
    //    Serial.println("Send mesage NameRele");

    readEepromNameRele();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_save-name-sensor-eeprom") // проверяем из нужного ли нам топика пришли данные
  {
    //Записуємо імя термодатчиків
    //*&name1*&name2*&name3*&name4*&name5*&name6*&name7*&name8
    //Зберігаємо імя термодатчика
    Sensor ds18b20_temp[8];
    String tempStr = payload;

    for (int i = 0; i < 8; i++)
    { //заносимо імена в обєкт
      tempStr = tempStr.substring(tempStr.indexOf("*&") + 2);
      String tempName = tempStr.substring(0, tempStr.indexOf("*&"));

      char buffer[tempName.length() + 1];
      tempName.toCharArray(buffer, tempName.length() + 1);
      //      Serial.println(tempName);
      ds18b20_temp[i].nameSensor = tempName;
      Serial.println(ds18b20_temp[i].nameSensor);
    }

    writeEEPROMNameSensor(ds18b20_temp); //записуємо адреса в EEPROM з обєкта
    client.publish(nameUser + "_sensor-name", ds18b20EEpromToJSONnameSensor());

    //    sendSensorData();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_rele-get-eprom_upr-manual") // проверяем из нужного ли нам топика пришли данные
  {
    // 0x2k START_SECTION_RELE_EEPROM_UPR bit-0 Ручний або автоматичний режим
    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt(); //номер реле
    byte manualOrAuto = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //Ручний або автоматичний режим 1 або 0
    prin("manualOrAuto", manualOrAuto);
    manualOrAuto &= ~0b11111110;//reset bit 7-1
    prin("manualOrAuto ---- manualOrAuto", manualOrAuto);
    releControl[numberRele].setManualAutoEEPROM(manualOrAuto, numberRele);//Запмсуємо в память новий стан ручний або автоматичений режим

    if (manualOrAuto == 1) {//Якщо переходимо в ручний режим то стан реле неміняємо
      manual_vklOtkl(releControl[numberRele].getOnOffManualEEPROM(numberRele), numberRele);
    }
    //    refreshData();
    kontr_temp();

    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_set-rele-vkl-otkl") // проверяем из нужного ли нам топика пришли данные
  {
    //0x2k START_SECTION_RELE_EEPROM_UPR //Включаєм і виключаєм реле в ручному режимі
    byte numRele = payload.substring(0, payload.indexOf('x')).toInt(); //номер реле
    byte onOff = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //Включаєм або вииключаємо реле

    manual_vklOtkl(onOff, numRele);

    byte stanRele = 0;
    for (int i = 0; i < NUMBER_RELE; i++) {
      digitalRead(releControl[i].numberPin) == 0 ?  stanRele &= ~(1 << i) : stanRele |= (1 << i);//Формуємо маску бітів про стан кожного реле і відправляємо
    }

    client.publish(nameUser + "_stanRele", String(stanRele));
    //    Serial.print("Send mesage stanRele");
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_rele_eprom_upr-set_number_sensor") // проверяем из нужного ли нам топика пришли данные
  {
    // 0x2k START_SECTION_RELE_EEPROM_SENSOR номер термодатчика для реле

    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt(); //номер реле
    byte numSensorControlRele = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //номер термодатчика який управляє реле
    prin("numSensorControlRele", numSensorControlRele);
    prinEEPROMDebag(START_SECTION_RELE_EEPROM_SENSOR, LENGTH_RELE_EEPROM_SENSOR, "START_SECTION_RELE_EEPROM_SENSOR");
    releControl[numberRele].setNumberSensorControlEEPROM(numSensorControlRele, numberRele);
    prinEEPROMDebag(START_SECTION_RELE_EEPROM_SENSOR, LENGTH_RELE_EEPROM_SENSOR, "START_SECTION_RELE_EEPROM_SENSOR");
    refreshData();
    kontr_temp();
    client.publish(nameUser + "_rele_eprom_upr", EEPROMDataToJSONSensor());
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_rele_eprom_upr-set_erorr_rele_vkl_vukl") // проверяем из нужного ли нам топика пришли данные
  {
    //0x2k START_SECTION_RELE_EEPROM_SENSOR біт 6 при несправності термодатчика або не можливості керувати таймером  в якому стані залишаємо реле
    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt(); //номер реле
    byte errorOnOrOff = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //
    errorOnOrOff = (errorOnOrOff & ~0b10111111) >> 6; //Залишаємо  тільки 6 біт і переміщаємо на нулоьовий біт
    releControl[numberRele].setReleErrorEEPROM(errorOnOrOff, numberRele);
    kontr_temp();
    client.publish(nameUser + "_rele_eprom_upr", EEPROMDataToJSONSensor());
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_rele_eprom_upr-set_change_on_or_off") // проверяем из нужного ли нам топика пришли данные
  {
    //0x2k START_SECTION_RELE_EEPROM_SENSOR біт 5 при переключенні реле включається або виключається
    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt(); //номер реле
    byte OnOrOff = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //
    OnOrOff = (OnOrOff & ~0b11011111) >> 5; //Залишаємо  тільки 5 біт і переміщаємо на нулоьовий біт
    releControl[numberRele].setOnOffChangeEEPROM(OnOrOff, numberRele);

    kontr_temp();
    client.publish(nameUser + "_rele_eprom_upr", EEPROMDataToJSONSensor());
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_rele_eprom_upr-set_one_or_two_range_temp") // проверяем из нужного ли нам топика пришли данные
  {
    //0x2k START_SECTION_RELE_EEPROM_SENSOR біт 4 1-два діапазона температур включенн і відключеня 0-один діапазон температур  включення або відключення

    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt(); //номер реле
    byte oneOrTworange = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //номер термодатчика який управляє реле

    oneOrTworange = (oneOrTworange & ~0b11101111) >> 4; //Залишаємо  тільки 4 біт і переміщаємо на нулоьовий біт

    releControl[numberRele].setOneOrTwoRangeEEPROM(oneOrTworange, numberRele);

    kontr_temp();

    client.publish(nameUser + "_rele_eprom_upr", EEPROMDataToJSONSensor());
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_save-data-sensor-eeprom") // проверяем из нужного ли нам топика пришли данные
  {

    Sensor ds18b20_temp[8];
    String sas = payload;

    for (int i = 0; i < 8; i++)
    {
      sas = sas.substring(sas.indexOf("na") + 2);
      String address = sas.substring(0, sas.indexOf("na"));
      char buffer[address.length() + 1];
      address.toCharArray(buffer, address.length() + 1);
      //      Serial.println(address);
      ds18b20_temp[i].strAddress = address;
    }
    writeEEPROMDataSensor(ds18b20_temp); //записуємо адреса в EEPROM
    readEepromAddress();                 //читаємо address з памяті ЕЕПРОМ  в обєкт ds18b20EEprom

    //    client.publish(nameUser + "_start-data-sensor-eepromAndDevice", "NameSensor");
    client.publish(nameUser + "_sensor-name", ds18b20EEpromToJSONnameSensor());
    //    client.publish(nameUser + "_start-data-sensor-eepromAndDevice", "readAddressSensor");
    sendSensorData();
    return;
  }
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
void searchCodeSennsorInEEPROM() {
  for (int i = 0; i < 8; i++)
  {
    for (int k = 0; k < deviceCountSensor; k++)
    {
      if (ds18b20EEprom[i].strAddress == ds18b20[k].strAddress)//Якщо в памяті є адрес датчика який підключений реально
      {
        ds18b20EEprom[i].temp = ds18b20[k].temp;//То присвоюємо температуру номеру, що записаний в памяті
        break;
      }
    }
  }
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
void sendSensorData() {
  readEepromAddress(); //читаємо address з памяті ЕЕПРОМ  в обєкт ds18b20EEprom
  //---------------------------------------------------------------------
  //Якщо в памяті є записаний реальний мас адрес датчика то присвоюємо йому температуру датчика
  readSensorsAddressTemp(); //читаємо в обєкт адреса і температуру датчиків
  searchCodeSennsorInEEPROM();//Записуємо температуру в EEPROM sensory з реальних датчиків
  //формуємо в формат JSON дані з памяті EEPROM і відправляємо в топік
  client.publish(nameUser + "_eepromSensorData", objectToJSON(ds18b20EEprom, 8));
  //формуємо в формат JSON дані з датчиків температури  і відправляємо в топік
  client.publish(nameUser + "_deviceSensorData", objectToJSON(ds18b20, deviceCountSensor));
  //  Serial.println(objectToJSON(ds18b20, deviceCountSensor));
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
int parseStringToData(String stringData) {//пошук наступного елемента в строці якщо кінець повертає -1

  symbolStart = stringData.indexOf('RELE') + 3;
  symbolEnd = stringData.indexOf('-');
  int numRele = stringData.substring(symbolStart, symbolEnd ).toInt(); //номер реле


  symbolStart = symbolEnd;
  symbolEnd = stringData.indexOf('-', symbolStart + 1);


  dataAndTime[numRele].delaySecondStart = stringData.substring(symbolStart + 1, symbolEnd ).toInt();//Затримка в секундах для включення реле

  for (int i = 0; i < 10; i++) {

    unsigned long temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_datamiliseconds[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_rik[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_months[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_dey[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_godyna[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_minut[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].data_daywikend[i] = temp;
  }

  for (int i = 0; i < 50; i++) {
    int temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].godyna[i] = temp;
    temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].minut[i] = temp;
  }

  for (int i = 0; i < 35; i++) {
    int temp = nextElement(stringData);
    if (temp >= 0)dataAndTime[numRele].dey[i] = temp;
  }
  return numRele;
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
unsigned long nextElement(String s) {//пошук наступного елемента в строці якщо кінець повертає -1
  symbolStart = symbolEnd;
  symbolEnd = s.indexOf('-', symbolStart + 1);
  if (!(symbolStart < 0 || symbolEnd < 0)) {
    String  s2 = s.substring(symbolStart + 1, symbolEnd ); //номер реле
    //     Serial.print("SSSS22222 ");
    //    Serial.println(s2);
    unsigned long a = 0;
    for (byte i = 0; i < s2.length(); i++) {
      a = a * 10;
      String s3 = s2.substring(i, i + 1 );
      //   Serial.print("SSSS333 ");
      //    Serial.println(s3);
      int b = s3.toInt();
      a = a + b;
    }
    //    Serial.println(a);
    return a;
  } else return -1;
}
//*************************************************************************************************************************************************
