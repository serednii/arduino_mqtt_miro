void loop(void)
{
  controlPins();

  server.handleClient();
  analoReadA0();
prin("counterPin_0  ", counterPin_0);
prin("counterPin_1  ", counterPin_1);
prin("counterPin_2  ", counterPin_2);
prin("counterPin_3  ", counterPin_3);
prin("counterPin_4  ", counterPin_4);
prin("counterPin_5  ", counterPin_5);
prin("counterPin_6  ", counterPin_6);
prin("counterPin_7  ", counterPin_7);


  //************************************



  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  // client
    if (WiFi.status() != WL_CONNECTED)
    {

      if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED)
      {
        String ssid = WiFi.SSID();
        String localip = WiFi.localIP().toString();
        Serial.print("WiFi connected: ");
        Serial.print(ssid);
        Serial.print(" ");
        Serial.println(localip);
        Serial.print("-1 ");
        connectedInternet = true;
      }
      else
      {
        Serial.println("WiFi not connected!");
        Serial.print("0 ");
        connectedInternet = false;
        ledBlink(8, 250);
        kontr_temp();
        counterAnalogInput += 650;
        analoReadA0();
      }
    }
  //    else {


  String ssid;
  String localip;
  if (tm == 0)
  {
    Serial.print("Configuring access point...");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  // client
      if (WiFi.status() == WL_CONNECTED)
      {
        ssid = WiFi.SSID();
        localip = WiFi.localIP().toString();
        Serial.print("WiFi CONNECTED: ");
        Serial.print(ssid);
        Serial.print(" ");
        Serial.println(localip);
        Serial.print("1 ");
        connectedInternet = true;
        if (client.connect(MQTT::Connect(nameUser + "_ceske-budejovice")
                           .set_auth(mqtt_user, mqtt_pass)))
        {
          Serial.println("2powerx/Connected to MQTT server");
          client.set_callback(callback);
          //          client.subscribe(nameUser + "_rele-0");
          //          client.subscribe(nameUser + "_rele-1");
          //          client.subscribe(nameUser + "_rele-2");
          //          client.subscribe(nameUser + "_rele-3");
          //          client.subscribe(nameUser + "_rele-4");
          //          client.subscribe(nameUser + "_rele-5");
          //          client.subscribe(nameUser + "_rele-6");
          client.subscribe(nameUser + "_rele-temp");
          client.subscribe(nameUser + "_rele-all");
          client.subscribe(nameUser + "_start-data-sensor-eepromAndDevice");
          client.subscribe(nameUser + "_deviceSensorData");
          client.subscribe(nameUser + "_eepromSensorData");
          client.subscribe(nameUser + "_save-data-sensor-eeprom");
          client.subscribe(nameUser + "_flagRele");
          client.subscribe(nameUser + "_rele_eprom_upr-set_number_sensor");
          client.subscribe(nameUser + "_rele_eprom_upr-set_erorr_rele_vkl_vukl");
          client.subscribe(nameUser + "_rele_eprom_upr-set_one_or_two_range_temp");
          client.subscribe(nameUser + "_rele_eprom_upr-set_change_on_or_off");
          client.subscribe(nameUser + "_save-name-sensor-eeprom");
          client.subscribe(nameUser + "_save-rele-name");
          client.subscribe(nameUser + "_rele-get-eprom_upr-manual");
          client.subscribe(nameUser + "_set-rele-vkl-otkl");
          client.subscribe(nameUser + "_set-rele-data-time");
          client.subscribe(nameUser + "_save-data-sensor-temp");
          client.subscribe(nameUser + "_define_device");
          client.subscribe(nameUser + "_resetFunction");
          client.subscribe(nameUser + "_get_name_device");
          client.subscribe(nameUser + "_cleareEPROM");
          //          client.subscribe(nameUser + "_define_device");
          //          client.subscribe(nameUser + "_define_device");
          //          client.subscribe(nameUser + "_define_device");
          //          client.subscribe(nameUser + "_define_device");


          client.publish(nameUser + "_ssid", ssid); // отправляем в топик для термодатчика значение температуры
          client.publish(nameUser + "_ip", localip); // отправляем в топик для термодатчика значение температуры
        }
        else
        {
          Serial.println("2powerx/Could not connect to MQTT server");
        }
      }
    tm = 500; // пауза між визовами TempSend();
    Serial.println("Miro Benech");
    client.publish(nameUser + "_ssid", ssid); // отправляем в топик для термодатчика значение температуры
    client.publish(nameUser + "_ip", localip); // отправляем в топик для термодатчика значение температуры

    kontr_temp();
  prinEEPROMDebag(START_SECTION_RELE_EEPROM_SENSOR, LENGTH_RELE_EEPROM_SENSOR, "START_SECTION_RELE_EEPROM_SENSOR");
  prinEEPROMDebag(START_SECTION_RELE_EEPROM_UPR, LENGTH_RELE_EEPROM_UPR, "START_SECTION_RELE_EEPROM_UPR");

  }

  tm--;
  delay(10);

  if (WiFi.status() == WL_CONNECTED)
  {
    // Serial.println("client.loop");
    client.loop();
  }
  //    }
}




void controlPins() {
counterPin_0 = controlPin( 0,  counterPin_0,  PIN_RELE_IN_0);
counterPin_1 = controlPin( 1,  counterPin_1,  PIN_RELE_IN_1);
counterPin_2 = controlPin( 2,  counterPin_2,  PIN_RELE_IN_2);
counterPin_3 = controlPin( 3,  counterPin_3,  PIN_RELE_IN_3);
counterPin_4 = controlPin( 4,  counterPin_4,  PIN_RELE_IN_4);
counterPin_5 = controlPin( 5,  counterPin_5,  PIN_RELE_IN_5);
counterPin_6 = controlPin( 6,  counterPin_6,  PIN_RELE_IN_6);
counterPin_7 = controlPin( 7,  counterPin_7,  PIN_RELE_IN_7);
}


 int controlPin(byte numberRele, int counterPin, byte pinConected){
  
  if (digitalRead(pinConected) == 1) {
//        Serial.print("counterPin  ------------------------------------- ");
//        Serial.println(counterPin);
    if (counterPin == 50) {
//      Serial.print("PIN_RELE_IN_2 ******************************************************************************  ");
//      Serial.println(digitalRead(counterPin));
      releControl[numberRele].setManualAutoEEPROM(1, numberRele); //переводимо в ручний режим реле

      if (digitalRead(releControl[numberRele].numberPin) == 0) { //Інвертуємо стан реле
        releControl[numberRele].setOnOffManualEEPROM(0, numberRele);
        manual_vklOtkl(0, numberRele);
      } else {
        releControl[numberRele].setOnOffManualEEPROM(1, numberRele);
        manual_vklOtkl(1, numberRele);
      }

      byte stanRele = 0;
      for (int i = 0; i < NUMBER_RELE; i++) {
        digitalRead(releControl[i].numberPin) == 0 ?  stanRele &= ~(1 << i) : stanRele |= (1 << i);//Формуємо маску бітів про стан кожного реле і відправляємо
      }
      client.publish(nameUser + "_stanRele", String(stanRele));
      client.publish(nameUser + "_rele-out-eprom_upr-manual", objectToJSONRele(releControl, NUMBER_RELE, "manualAuto"));

      counterPin++;
    } else if (counterPin == 250) {
      releControl[numberRele].setManualAutoEEPROM(0, numberRele); //переводимо в автоматичний режим реле
       client.publish(nameUser + "_rele-out-eprom_upr-manual", objectToJSONRele(releControl, NUMBER_RELE, "manualAuto"));
      counterPin++;
    } else {
      counterPin++;
    }

  } else if (digitalRead(pinConected) == 0 && counterPin > 0) {
    counterPin = 0;
  }
  return counterPin;
}
