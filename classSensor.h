int deviceCountSensor; //КІЛЬКІСТЬ ПІДКЛЮЧЕНИХ ДАТЧИКІВ
class Sensor           // название класса
{
  public:
    String nameSensor;
    byte number;
    String strAddress;
    float temp;
    int tempVkl;
    int tempOtkl;







};

Sensor ds18b20[MAX_NUMBER_SENSOR];
Sensor ds18b20EEprom[MAX_NUMBER_SENSOR];
void writeEEPROMNameSensor(Sensor sensor[]);
String objectToJSON(Sensor obj[], int n);
void writeEEPROMDataSensor(Sensor sensor[]);
String sensorDeviceAddress(DeviceAddress deviceAddress);
//=================================================================================

void readSensorsAddressTemp() {
  // read device address and temperature in class Sensors object ds18b20 arrays

  //  oneWireBus = 12;//14
  //  OneWire oneWire(oneWireBus);
  //  DallasTemperature sensors(&oneWire);

  sensors.requestTemperatures(); // от датчика получаем значение температуры
  DeviceAddress Thermometer;
  deviceCountSensor = sensors.getDeviceCount();

  for (byte i = 0; i < deviceCountSensor; i++)
  {
    sensors.getAddress(Thermometer, i);
    ds18b20[i].strAddress = sensorDeviceAddress(Thermometer);

    ds18b20[i].temp = sensors.getTempCByIndex(i);

    ds18b20[i].number = i;
  }
}
//=================================================================================

//=================================================================================
String sensorDeviceAddress(DeviceAddress deviceAddress)
{
  uint64_t address = 0;
  String strAddress = "";
  for (uint8_t i = 0; i < 8; i++)
  {
    address = address + deviceAddress[i];
    if (deviceAddress[i] > 0)
    {
      if (deviceAddress[i] < 8)
        strAddress += "0" + String(deviceAddress[i], HEX);
      else
        strAddress += String(deviceAddress[i], HEX);
    }
    else
      strAddress += "00";
    if (i < 7)
      address = address << 8;
  }
  return strAddress;
}
//=================================================================================

//=================================================================================
//записуємо дані із обєкта Sensor  в EEPROM
void writeEEPROMDataSensor(Sensor sensor[])
{
  String strAddress = "";
  for (int i = 0; i < 8; i++)
  {
    //    strAddress = "";
    strAddress = sensor[i].strAddress;
    for (int k = 7, d = 16; k >= 0; k--, d -= 2)
    {
      int addd = START_SECTION_EEPROM_SENSOR_ADDRESS + k + (i * 8);
      String cc = strAddress.substring(d - 2, d);
      char char_array[3];
      cc.toCharArray(char_array, 3);
      EEPROM.write(addd, (byte)strtol(char_array, NULL, 16));
    }
  }
  comitEprom();


  readEepromAddress(); //читаємо address з памяті ЕЕПРОМ  в обєкт ds18b20EEprom
}
//=================================================================================

//=================================================================================
//Формуємо мас адрес датчика в обєкт із памяті ЕЕПРОМ
void readEepromAddress()
{ //читаємо address з памяті ЕЕПРОМ
  String strAddress = "";
  //Формуємо мас адрес датчика в обєкт із памяті ЕЕПРОM
  for (int i = 0; i < 8; i++)
  {
    strAddress = "";
    for (int k = 0; k < 8; k++)
    {
      byte temp = EEPROM.read(START_SECTION_EEPROM_SENSOR_ADDRESS + k + (i * 8));
      if (temp > 0)
      {
        if (temp < 10)
          strAddress += "0" + String(temp, HEX);
        else
          strAddress += String(temp, HEX);
      }
      else
        strAddress += "00";
    }
    ds18b20EEprom[i].strAddress = strAddress;
    ds18b20EEprom[i].temp = 0;
  }
}
//=================================================================================

//=================================================================================
void readEepromNameSensor()
{ //читаємо address з памяті ЕЕПРОМ
  //  const byte kilkistyBukv = 20;
  //Формуємо мас адрес датчика в обєкт із памяті ЕЕПРОM
  for (int i = 0; i < MAX_NUMBER_SENSOR; i++)
  {
    //    ds18b20EEprom[i].nameSensor = "";
    //    for (int k = 0; k < kilkistyBukv; k++)
    //    {
    //      int addd = START_SECTION_EEPROM_SENSOR_NAME + k + (i * kilkistyBukv);
    //      byte data = EEPROM.read(addd);
    //      if (data > 0 && data < 165)  ds18b20EEprom[i].nameSensor += char(data);
    //    }
    ds18b20EEprom[i].nameSensor = readStringEeprom(START_SECTION_EEPROM_SENSOR_NAME + (i * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR), MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR);
    //    Serial.print("void readEepromNameSensor()    ");
    //    Serial.print(i);
    //    Serial.print("  ds18b20EEprom[i].nameSensor  ");
    //    Serial.println(ds18b20EEprom[i].nameSensor);
  }
}
//=================================================================================

//записуємо дані із обєкта Sensor  в EEPROM
void writeEEPROMNameSensor(Sensor sensor[])
{

  for (int i = 0; i < 8; i++)
  {
    word StartAdress = START_SECTION_EEPROM_SENSOR_NAME  + (i * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR);//Вираховуємо адрес для запису

    writeStringEeprom(StartAdress, MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR, sensor[i].nameSensor, 0);
  }
  //---------------------------------------------------------------------
}
