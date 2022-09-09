
class Rele // название класса
{
  public:
    String nameRele; //імя реле
    byte numberPin;           //номер піна до якого підключено реле 1

    //START_SECTION_RELE_EEPROM_UPR
    byte manualAuto;            // вкл або виключено
    byte onOffManual; //при ручному режимі реле включено чи виключено  bit - 0
    //    byte termoControl;     // Буде чи ні реле керуватися термодатчиком
    byte timerControl;        // Якщо 0 то реле не контролюється таймером, якщо 1 то контролюємо


    //   byte temp = EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i);
    //    releControl[i].bit4OneOrTwoRange = (temp & ~0b11101111) >> 4;
    //    releControl[i].bit5OnOffChange = (temp & ~0b11011111) >> 5;
    //    releControl[i].bit6ReleError = (temp & ~0b10111111) >> 6;

    //START_SECTION_RELE_EEPROM_SENSOR
    byte numberSensorControl; // номер датчика який управляє даним реле
    byte bit4OneOrTwoRange;  //1-два діапазона температур включенн і відключеня 0-один діапазон температур  включення або відключення
    byte bit5OnOffChange; //при переключенні реле включається або виключається
    byte bit6ReleError; //при несправності термодатчика або неможливість управляти таймером реле залишаємо вкл 1 або відключеним -0

    boolean errorSensor; //Якщо пропав датчик флаг ставимо в true
    boolean flagsTermo;//  якщо спрацювала умова включення для термодатчика
    boolean flagsTimer;//  якщо спрацювала умова включення для таймера
    boolean flagsDelaystart;// якщо є затримка при включенні



  public:
    //*****************************************************************
    // Setter
    void setManualAutoEEPROM(byte stan, byte numberRele) {
      manualAuto = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      setOrResetBitEEPROM(address, 0, stan);
    }

    void setOnOffManualEEPROM(byte stan, byte numberRele) {
      onOffManual = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      setOrResetBitEEPROM(address, 1, stan);
    }

    //     void setTermoControlEEPROM(byte stan, byte numberRele) {//Не використовується взагалі
    //      termoControl = stan;
    //      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
    //      setOrResetBitEEPROM(address, 2, stan);
    //    }

    //     void setTimerControlEEPROM(byte stan, byte numberRele) {//Не використовується для EEPROM
    //      timerControl = stan;
    //      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
    //      setOrResetBitEEPROM(address, 3, stan);
    //    }


    void setNumberSensorControlEEPROM(byte numSensorControlRele, byte numberRele) {//Не використовується для EEPROM
      numberSensorControl = numSensorControlRele;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      byte temp = EEPROM.read(address);
      temp &= ~0b00001111;//reset bit 0-3
      temp = temp + (numSensorControlRele);
      prin("numberRele", temp);
      prin("numberRele", temp & ~0b11110000);
      EEPROM.write(address, temp);
      comitEprom();
    }


    void setOneOrTwoRangeEEPROM(byte stan, byte numberRele) {
      Serial.print("stan ---------------  ");
      Serial.println(stan);
      Serial.print("numberRele ---------------  ");
      Serial.println(numberRele);
      bit4OneOrTwoRange = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      setOrResetBitEEPROM(address, 4, stan);
    }

    void setOnOffChangeEEPROM(byte stan, byte numberRele) {
      Serial.print("stan ---------------  ");
      Serial.println(stan);
      Serial.print("numberRele ---------------  ");
      Serial.println(numberRele);
      bit5OnOffChange = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      setOrResetBitEEPROM(address, 5, stan);
    }

    void setReleErrorEEPROM(byte stan, byte numberRele) {
      Serial.print("stan ---------------  ");
      Serial.println(stan);
      Serial.print("numberRele ---------------  ");
      Serial.println(numberRele);
      bit6ReleError = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      setOrResetBitEEPROM(address, 6, stan);
    }

    //*****************************************************************
    
    //*****************************************************************
    // Getter
    byte getManualAutoEEPROM(byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      return getBitEEPROM(address, 0);
    }

    byte getOnOffManualEEPROM(byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      return getBitEEPROM(address, 1);
    }

    //       byte getTermoControlEEPROM(byte numberRele) {//Не використовується взагалі
    //      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
    //      return getBitEEPROM(address, 2);
    //    }

    //        byte getTimerControlEEPROM(byte numberRele) {//Не використовується для EEPROM
    //      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
    //      return getBitEEPROM(address, 3);
    //    }


    byte getNumberSensorControlEEPROM(byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      byte temp = EEPROM.read(address);
      prin("numberRele", temp);
      prin("numberRele", temp & ~0b11110000);
      
      return temp & ~0b11110000;
    }

    byte getOneOrTwoRangeEEPROM( byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      return getBitEEPROM(address, 4);
    }

    byte getOnOffChangeEEPROM( byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      return getBitEEPROM(address, 5);
    }

    byte getReleErrorEEPROM( byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      return getBitEEPROM(address, 6);
    }

    //*****************************************************************


    //functions************************************************************
    void setOrResetBitEEPROM(int address, byte numBit, byte setOrReset) {
      byte data = EEPROM.read(address);
      Serial.print("sizeof(LENGTH_SECTION_SSID_ADN_PASSWORD)  ");
      Serial.println(data);

      if (setOrReset == 0) {
        data &= ~(1 << numBit);//reset bit
      } else if (setOrReset == 1) {
        data |= (1 << numBit);//set bit
      }
      EEPROM.write(address, data);
      comitEprom();
      data = EEPROM.read(address);
      Serial.print("sizeof(LENGTH_SECTION_SSID_ADN_PASSWORD)  ");
      Serial.println(data);
    }

    byte getBitEEPROM(int address, byte numBit) {
      byte data = EEPROM.read(address);
      if (data & (1 << numBit)) return 1;
      else return 0;
//      return ((data & ~0b11111101) >> numBit);
    }
    //functions************************************************************

};
