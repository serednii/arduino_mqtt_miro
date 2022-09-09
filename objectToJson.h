
//*************************************************************************************************************************************************
String objectToJSONRele(Rele obj[], int n, String pole)
{
  String s = "{\"obj\":[";
  for (int i = 0; i < n; i++)
  {

    if (pole == "manualAuto" ) {
      s += "{\"namberRele\": ";
      s += String(obj[i].manualAuto);
    }
    else if (pole == "nameRele") {
      s += "{\"nameRele\": ";
      s +=  "\"";
      s +=  releControl[i].nameRele;
       s +=  "\"";
    }
    s += "}";
    s += (i < n - 1 ? "," : "");
  }
  s += "]}";
  return s;
}

//      String s = "{\"obj\":[";
//            for (int i = 0; i < 8; i++)
//            {
//              s += "{\"nameRele\": ";
//              s +=  "\"";
//              s +=  releControl[i].nameRele;
//              s +=  "\"";
//              s +=  "}";
//              s +=  (i < 8 - 1 ? "," : "");
//            }
//            s += "]}";
      
//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
String EEPROMDataToJSONOnOff() {
  String s = "{\"obj\":[";
  for (int i = 0; i < 8; i++)
  {
    s += "{\"vkl\": ";
    s += String(EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2) - 50);
    s += ",";
    s += "\"otkl\": ";
    s += String(EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2 + 1) - 50);
    s += "}";
    s += (i < 8 - 1 ? "," : "");
  }
  s += "]}";
  return s;
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
void refreshobjectToJsonDate() {
  readEEPROMTimerToObjeckt();
  for (int i = 0; i < 8; i++) {
    //    Serial.println(objectToJsonDate(dataAndTime[i], i));
    for (byte numPak = 1; numPak < 5; numPak++)
      client.publish(nameUser + "_out-web-rele-data-time", objectToJsonDate(dataAndTime[i], i, numPak));
  }
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
String objectToJsonDate(TimerDate obj, byte num, byte numberPackege) {
  String output;


  output = "{";
  output += "\"NUMPACKAGE\":";
  output += String(numberPackege);
  output +=  ", ";
  const word NumberElementDate = 10;

  if (numberPackege == 1) {
    output += "\"NUM\":";
    output += String(num);
    output +=  ", ";
    output +=   "\"DELAYSECONDSTART\":";
    output += String(dataAndTime[num].delaySecondStart);
    output +=  ", ";
    output +=   "\"DATATIME\":";
    output +=  "[";
    for (int k = 0; k < NumberElementDate; k++) {
      output += "\"";
      output += String(dataAndTime[num].data_rik[k]);
      output += "-";
      if (dataAndTime[num].data_months[k] > 9)output += String(dataAndTime[num].data_months[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].data_months[k]);
      }
      output += "-";
      if (dataAndTime[num].data_dey[k] > 9)output += String(dataAndTime[num].data_dey[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].data_dey[k]);
      }
      output += "T";
      if (dataAndTime[num].data_godyna[k] > 9)output += String(dataAndTime[num].data_godyna[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].data_godyna[k]);
      }
      output += ":";
      if (dataAndTime[num].data_minut[k] > 9)output += String(dataAndTime[num].data_minut[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].data_minut[k]);
      }
      output += "\"";
      if (k < NumberElementDate - 1)output +=  ", ";
    }
    output +=  "]";
    //"data_":"2022-5-16 12:30",

    //  output +=  ", ";
  }

  if (numberPackege == 2) {
    output +=   "\"TIME\":";
    output +=  "[";
    const word NumberElementTime = 25;
    for (int k = 0; k < NumberElementTime; k++) {
      output += "\"";
      if (dataAndTime[num].godyna[k] > 9)output += String(dataAndTime[num].godyna[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].godyna[k]);
      }
      output += ":";
      if (dataAndTime[num].minut[k] > 9)output += String(dataAndTime[num].minut[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].minut[k]);
      }
      output += "\"";
      if (k < NumberElementTime - 1)output +=  ", ";
    }
    output +=  "]";
    //  output +=  ", ";
  }

  if (numberPackege == 3) {
    output +=   "\"TIME\":";
    output +=  "[";
    const word NumberElementTime = 50;
    for (int k = 25; k < NumberElementTime; k++) {
      output += "\"";
      if (dataAndTime[num].godyna[k] > 9)output += String(dataAndTime[num].godyna[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].godyna[k]);
      }
      output += ":";
      if (dataAndTime[num].minut[k] > 9)output += String(dataAndTime[num].minut[k]);
      else {
        output += "0";
        output += String(dataAndTime[num].minut[k]);
      }
      output += "\"";
      if (k < NumberElementTime - 1)output +=  ", ";
    }
    output +=  "]";
    //  output +=  ", ";
  }

  if (numberPackege == 4) {
    output +=   "\"DEY\":";
    output +=  "[";
    const word NumberElementDay = 35;
    for (int k = 0; k < NumberElementDay; k++) {
      output += String(dataAndTime[num].dey[k]);
      if (k < NumberElementDay - 1)output +=  ", ";
    }
    output +=  "]";
  }

  output += "}";
  Serial.print("OUTPUT LENGTH  ");
  Serial.println(output.length());
  return output;
}

//*************************************************************************************************************************************************
String EEPROMDataToJSONSensor() {
  String s = "{\"obj\":[";
  for (int i = 0; i < 8; i++)
  {
    s += "{\"number\": ";
    s += String(EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i));
    s += "}";
    s += (i < 8 - 1 ? "," : "");
  }
  s += "]}";
  return s;
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
String ds18b20EEpromToJSONnameSensor() {
  String s = "{\"obj\":[";
  for (int i = 0; i < 8; i++)
  {
    s +=  "{\"nameSensor\": ";
    s +=  "\"";
    s +=  ds18b20EEprom[i].nameSensor;
    s +=  "\"";
    s +=  "}";
    s +=  (i < 8 - 1 ? "," : "");
  }
  s += "]}";
  return s;
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
String objectToJSON(Sensor obj[], int n)
{
  String s = "{\"obj\":[";
  for (int i = 0; i < n; i++)
  {
    s += "{\"number\": ";
    s += String(String(i) + ", \"address\": " + "\"" + obj[i].strAddress);
    s += "\"";
    s += ", \"temp\": ";
    s += String(obj[i].temp);
    s += "}";
    s += (i < n - 1 ? "," : "");
  }
  s += "]}";
  return s;
}
//*************************************************************************************************************************************************
