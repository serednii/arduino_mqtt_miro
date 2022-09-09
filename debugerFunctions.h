

//*************************************************************************************************************************************************
const boolean FLAGPRINT = false;
void printObjectTime() {
  if(FLAGPRINT){
  for (int i = 0; i < 8; i++) {

    Serial.print("NUMBER RELE  ");
    Serial.println(i);
    Serial.print("DElay rele start  ");
    Serial.println(dataAndTime[i].delaySecondStart);

    for (int k = 0; k < 10; k++) {
      Serial.print(dataAndTime[i].data_datamiliseconds[k]);
      Serial.print("  ");
      Serial.print(dataAndTime[i].data_rik[k]);
      Serial.print("  ");
      Serial.print(dataAndTime[i].data_months[k]);
      Serial.print("  ");
      Serial.print(dataAndTime[i].data_dey[k]);
      Serial.print("  ");
      Serial.print(dataAndTime[i].data_godyna[k]);
      Serial.print("  ");
      Serial.print(dataAndTime[i].data_minut[k]);
      Serial.print("  ");
      Serial.println(dataAndTime[i].data_daywikend[k]);
    }

    Serial.println("*****************************");

    for (int k = 0; k < 50; k++) {
      Serial.print(dataAndTime[i].godyna[k]);
      Serial.print(":");
      Serial.print(dataAndTime[i].minut[k]);
      Serial.print(" ");
    }

    Serial.println("*****************************");

    for (int k = 0; k < 35; k++) {
      Serial.print(dataAndTime[i].dey[k]);
    }
    Serial.println("*****************************");
    Serial.println("*****************************");
    Serial.println("*****************************");
  }
  }
}


void prin(String s, byte a) {
  if(FLAGPRINT){prinString(s);
  Serial.println(a);
  prinString(s);
  Serial.println(a, BIN);
  }
}

void prin(String s, int a) {
  if(FLAGPRINT){prinString(s);
  Serial.println(a);
  }
}

void prin(String s, word a) {
  prinString(s);
  Serial.println(a);
}

void prin(String s, double a) {
  prinString(s);
  Serial.println(a);
}

void prin(String s, char a) {
  if(FLAGPRINT){prinString(s);
  Serial.println(a);
  }
}

void prin(String s, String a) {
  if(FLAGPRINT){prinString(s);
  Serial.println(a);
  }
}

void prinString(String s) {
  if(FLAGPRINT){Serial.print(s);
  Serial.print("  ----  ");
  }
}
void prin(String s) {
  if(FLAGPRINT)Serial.println(s);

}

//**********************************************************************************************

void prinEEPROMDebag(int starting, int lengthSection, String nameSection) {
  if(FLAGPRINT){Serial.println();
  Serial.println("*************************************************************************************************************");
  Serial.println(nameSection);
  for (int i = starting, ii = 0, iii = 0; i < starting + lengthSection; i++, ii++, iii++) {

    if (ii == LENGTH_SSID) {
      ii = 0;
      Serial.println("   ");
    }

    if (iii == 256) {
      iii = 0;
      Serial.println();
      Serial.println();
    }
    byte dataByte = EEPROM.read(i);
    Serial.print(i);
    Serial.print("--");
    Serial.print(dataByte);
    Serial.print("--");
    Serial.print(dataByte, BIN);
    Serial.print("--");
    Serial.print((char)dataByte);
    Serial.print("   ");
  }
  Serial.println();
  Serial.println("*************************************************************************************************************");
  Serial.println();
  }
}
