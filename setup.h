//----------------------SETUP---------------------

void setup()
{
  // const char *hexstring = "af";
  // uint8_t number = (uint8_t)strtol(hexstring, NULL, 16);
#ifdef ESP8266
  Serial.begin(1000000);
  timeClient.begin();//Годинник
#else
  Serial.begin(500000);
#endif

  sensors.begin();
  delay(1000);
  EEPROM.begin(4096);

  //  EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0);
  //    for (int i = 1; i < 4096; i++) {
  //        EEPROM.write(i, 0);
  //      }

  releControl[0].numberPin = PIN_RELE_0;
  releControl[1].numberPin = PIN_RELE_1;
  releControl[2].numberPin = PIN_RELE_2;
  releControl[3].numberPin = PIN_RELE_3;
  releControl[4].numberPin = PIN_RELE_4;
  releControl[5].numberPin = PIN_RELE_5;
  releControl[6].numberPin = PIN_RELE_6;
  releControl[7].numberPin = PIN_RELE_7;

  for (int i = 0; i < NUMBER_RELE; i++) {
    pinMode(releControl[i].numberPin, OUTPUT);
    digitalWrite(releControl[i].numberPin, HIGH);
  }


  pinMode(PIN_RELE_IN_0, INPUT);
  pinMode(PIN_RELE_IN_1, INPUT);
  pinMode(PIN_RELE_IN_2, INPUT);
  pinMode(PIN_RELE_IN_3, INPUT);
  pinMode(PIN_RELE_IN_4, INPUT);
  pinMode(PIN_RELE_IN_5, INPUT);
  pinMode(PIN_RELE_IN_6, INPUT);
  pinMode(PIN_RELE_IN_7, INPUT);



  pinMode(PIN_LED_KONTROL, OUTPUT);
  digitalWrite(PIN_LED_KONTROL, HIGH);
  refreshData();


  //  defineDevice();
  //clearEepromDate();

  //Serial.println();
  //  Serial.print("sizeof(LENGTH_SECTION_SSID_ADN_PASSWORD)  ");
  //  Serial.println(LENGTH_SECTION_SSID_ADN_PASSWORD);

  prinEEPROMDebag(EEPROM_ADRESS_STRING_NAME_DEVICE, 1, "EEPROM_ADRESS_STRING_NAME_DEVICE");
  prinEEPROMDebag(START_SECTION_EEPROM_SSID_AND_PASSWORD, LENGTH_SECTION_SSID_ADN_PASSWORD, "START_SECTION_EEPROM_SSID_AND_PASSWORD");
  prinEEPROMDebag(START_SECTION_RELE_EEPROM_SENSOR, LENGTH_RELE_EEPROM_SENSOR, "START_SECTION_RELE_EEPROM_SENSOR");
  prinEEPROMDebag(START_SECTION_RELE_EEPROM_UPR, LENGTH_RELE_EEPROM_UPR, "START_SECTION_RELE_EEPROM_UPR");
  prinEEPROMDebag(START_SECTION_EEPROM_TEMP_ON_OFF, LENGTH_TEMP_ON_OFF, "START_SECTION_EEPROM_TEMP_ON_OFF");


  //  for (int i = 0; i < 240; i++) {
  //    EEPROM.write(i, 0);
  //  }

  //  EEPROM.write(rele_0_eprom_pin, 0b11100000);
  //  EEPROM.write(rele_1_eprom_pin, 0b11100010);
  //  EEPROM.write(rele_2_eprom_pin, 0b11100100);
  //  EEPROM.write(rele_3_eprom_pin, 0b11100101);
  //    EEPROM.write(rele_4_eprom_pin, 0b11110000);
  //    EEPROM.write(rele_5_eprom_upr, 0b11110000);
  //    EEPROM.write(rele_6_eprom_upr, 0b11110000);
  //    EEPROM.write(rele_7_eprom_upr, 0b11110000);

  //  for (int i = 0; i < 8; i++) {
  //    EEPROM.write(START_SECTION_RELE_EEPROM_SENSOR + i, 0b00001111);
  //  }

  //  comitEprom();


  //  Serial.println(strtol(hexstring, NULL, 16));
  //  Serial.println("number   ");
  //  Serial.println(number);
  readEepromAddress(); //читаємо address з памяті ЕЕПРОМ  в обєкт ds18b20EEprom
  refreshData();

  //при старті
  // EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 255);
  // comitEprom();
  // Serial.println("connect to client--");
  Serial.print("EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT: ");
  Serial.println(EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT));
  //  Serial.println(checkClientAccessPointRom);





  //-------------------------------------------------------------------------------
  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) == 0) { //точка доступа
    /* Create a WiFi access point and provide a web server on it. */
    WiFi.softAP(ssid, password);
    Serial.println();
    Serial.print("Configuring access point...");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    Serial.print("-4 ");
    connectedInternet = false;
    digitalWrite(PIN_LED_KONTROL, HIGH);
  }
  else if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0) { // client
    //  if (true) { // client

    //***************************************************
    WiFi.persistent(false); // multi
    Serial.println("\n ESP8266 Multi WiFi example");
    // WiFi.mode(WIFI_OFF);
    //  Set WiFi to station mode
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP("DIR-825-8e26", "Mdcvsww0805197922");
    //    wifiMulti.addAP("Tenda_B4C7B0", "@0805197922@");
    //    wifiMulti.addAP("Tenda_B4C7B0", "0805197922");
    //    wifiMulti.addAP("Wireless 2.4G_SLAVE", "080519792");
    //    wifiMulti.addAP("Wireless 2.4G_MASTER", "080519792");
    //    wifiMulti.addAP("TP-Link_AFC2", "080519792");
    //    wifiMulti.addAP("UKrtelecom_7BE3E4", "080519792");
    //    wifiMulti.addAP("TP-LINK_FE7048", "080519792");
    wifiMulti.addAP("Mira", "8660024230");
    wifiMulti.addAP("Benesovi", "8660024230");
    wifiMulti.addAP("SIAP2", "@rFv753ZhN$159iK@");

    readEeprom();
    char Buf[20];
    char Buf1[20];
    digitalWrite(PIN_LED_KONTROL, LOW);
    // Register multi WiFi networks
    for (int i = 0; i < 6; i++)
    {
      arraySsid[i].toCharArray(Buf, 20);
      arrayPassword[i].toCharArray(Buf1, 20);
      wifiMulti.addAP(Buf, Buf1);

      Serial.print("ssid: ");
      Serial.print(i);
      Serial.print("  ");
      Serial.print(Buf);

      Serial.print("pasword: ");
      Serial.print(i);
      Serial.print("  ");
      Serial.print(Buf1);
    }

    byte counterConnect = 0;
    while (wifiMulti.run(connectTimeoutMs) != WL_CONNECTED)
    {
      Serial.print("-3 ");
      connectedInternet = false;
      ledBlink(5, 250);
      kontr_temp();
      Serial.print(".");
      //      if (counterConnect > 2)
      //      { //Якщо нема підключення переходимо в режим точки доступа
      //        EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0); //переходимо в точку доступа
      //        //        checkClientAccessPointRom = 0;
      //        comitEprom();
      //        Serial.println("connect to acess point");
      //        //        WiFi.disconnect(true);
      //        //        setup();
      //        resetFunc(); //вызываем reset
      //      }
      counterAnalogInput += 650;
      analoReadA0();
    }

    Serial.println("");
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.localIP());
    // WiFi.softAPdisconnect (true);
    Serial.print("-2");
    connectedInternet = true;
  }
  //---------------------------------------------------------------------------------------

  //назначаем символьное имя mDNS нашему серверу опираясь на его динамически полученный IP
  //  if (MDNS.begin("esp8266", WiFi.localIP())) {
  //    Serial.println("MDNS responder started");
  //  }

  //******************************************************

  server.on("/checkedClient", []() {
    EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 255);
    checkClientAccessPointRom = 255;
    comitEprom();
    Serial.println("connect to Client");
    server.send(200, "text/html", pageClient);
    delay(500);
    //    WiFi.disconnect(true);
    //    setup();
    resetFunc(); //вызываем reset });
  });

  server.on("/checkedAccesPoint", []() {
    EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0);
    checkClientAccessPointRom = 0;
    comitEprom();
    Serial.println("connect to Access Point");
    server.send(200, "text/html", pageAccessPoint);
    delay(500);
    //    WiFi.disconnect(true);
    //    setup();
    resetFunc(); //вызываем reset });
  });
  server.on("/", handleRoot);
  server.on("/router/", router);
  server.onNotFound(router);
  server.begin();

  Serial.println("HTTP server started");
  // MDNS.addService("http", "tcp", 80); //ставимо свій IP address
}
