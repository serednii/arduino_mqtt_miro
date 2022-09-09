//works
//#define ESP8266
#define ESP32

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;

const byte PIN_DS18B20 = 14;
const byte PIN_RELE_0 = 5;
const byte PIN_RELE_1 = 4;
const byte PIN_RELE_2 = 0;
const byte PIN_RELE_3 = 2;
const byte PIN_RELE_4 = 12;
const byte PIN_RELE_5 = 13;
const byte PIN_RELE_6 = 0;//3
const byte PIN_RELE_7 = 0;//1
const byte PIN_LED_KONTROL = 16;
int oneWireBus = PIN_DS18B20;

//const byte PIN_RELE_IN_0 = 33;//
//const byte PIN_RELE_IN_1 = 34;//
//const byte PIN_RELE_IN_2 = 35;
//const byte PIN_RELE_IN_3 = 39;//svn
//const byte PIN_RELE_IN_4 = 26;//
//const byte PIN_RELE_IN_5 = 27;//
//const byte PIN_RELE_IN_6 = 32;//
//const byte PIN_RELE_IN_7 = 33;//
//const byte PIN_RELE_IN_8 = 5;//
//const byte PIN_RELE_IN_9 = 2;//
//const byte PIN_RELE_IN_10 = 3;
//const byte PIN_RELE_IN_11 = 4;//
//const byte PIN_RELE_IN_12 = 5;//
//const byte PIN_RELE_IN_13 = 12;//
//const byte PIN_RELE_IN_14 = 14;//
//const byte PIN_RELE_IN_15 = 15;//
//test
#else
#include <WiFi.h> //#include <ESP8266WiFi.h>
#include <WebServer.h>     
#include <WiFiMulti.h>   
WiFiMulti wifiMulti;             

const byte PIN_DS18B20 = 4;

const byte PIN_RELE_0 = 23;  
const byte PIN_RELE_1 = 22;
const byte PIN_RELE_2 = 21;
const byte PIN_RELE_3 = 19;
const byte PIN_RELE_4 = 18;
const byte PIN_RELE_5 = 5;
const byte PIN_RELE_6 = 17;
const byte PIN_RELE_7 = 16;

//const byte PIN_RELE_8 = 1;//При відключеному UART
//const byte PIN_RELE_8 = 2;
//const byte PIN_RELE_8 = 3;//При відключеному UART
//const byte PIN_RELE_8 = 18;
//const byte PIN_RELE_8 = 12;
//const byte PIN_RELE_8 = 14;
//const byte PIN_RELE_8 = 26;
//const byte PIN_RELE_8 = 27;
//const byte PIN_RELE_8 = 32;
//const byte PIN_RELE_8 = 33;

const byte PIN_LED_KONTROL = 2;

const byte PIN_RELE_IN_0 = 39;//
const byte PIN_RELE_IN_1 = 34;//
const byte PIN_RELE_IN_2 = 35;//ok
const byte PIN_RELE_IN_3 = 32;//
const byte PIN_RELE_IN_4 = 33;//
const byte PIN_RELE_IN_5 = 25;//
const byte PIN_RELE_IN_6 = 26;//
const byte PIN_RELE_IN_7 = 27;//
//const byte PIN_RELE_IN_8 = 5;//
//const byte PIN_RELE_IN_9 = 2;//
//const byte PIN_RELE_IN_10 = 3;;//При відключеному UART
//const byte PIN_RELE_IN_11 = 4;//
//const byte PIN_RELE_IN_12 = 5;//
//const byte PIN_RELE_IN_13 = 12;//
//const byte PIN_RELE_IN_14 = 14;//
//const byte PIN_RELE_IN_15 = 15;//

byte inputAnalogPortADC1_0 = 36;
//byte inputAnalogPortADC1_3 = 39;
//byte inputAnalogPortADC1_6 = 34;
//byte inputAnalogPortADC1_7 = 35;
//byte inputAnalogPortADC1_4 = 32;
//byte inputAnalogPortADC1_5 = 33;
//byte inputAnalogPortADC2_8 = 25;
//byte inputAnalogPortADC2_9 = 26;
//byte inputAnalogPortADC2_7= 27;
//byte inputAnalogPortADC2_6 = 14;
//byte inputAnalogPortADC2_5 = 12;
//byte inputAnalogPortADC2_4 = 13;

int counterPin_0 = 0;
int counterPin_1 = 0;
int counterPin_2 = 0;
int counterPin_3 = 0;
int counterPin_4 = 0;
int counterPin_5 = 0;
int counterPin_6 = 0;
int counterPin_7 = 0;

int oneWireBus = PIN_DS18B20;
#endif

#include <PubSubClient.h> //mqtt
#include <EEPROM.h>
#include <NTPClient.h>//Годинник
#include <WiFiUdp.h>//Годинник
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200 , 60000);





//*****************************

//  HH:MM:SS
//******************************

const String nameUser = "miro1";
boolean connectedInternet = false;
//#include <ArduinoJson.h>
//DynamicJsonDocument doc(3400);
// WiFi connect timeout per AP. Increase when connecting takes longer.
const uint32_t connectTimeoutMs = 5000;

void (*resetFunc)(void) = 0; // объявляем функцию reset

#include "declaration.h"

void callback(const MQTT::Publish & pub);
void comitEprom();
//*------------------------------
// add OneWire ds18b20 02.09.2019
#include <OneWire.h>
#include <DallasTemperature.h>
// GPIO where the DS18B20 is connected to


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

int sensorPin = A0;    // select the input pin for the potentiometer

//const byte kilkistRele = 8;
const byte numberConnectRouter = 6;
byte releVsTemp = 0;
int scanWifiTimer = 0;
int tm = 300; // пауза між визовами TempSend();

const char *mqtt_server = "broker.hivemq.com"; // Имя сервера MQTT
const int mqtt_port = 1883;                    // Порт для подключения к серверу MQTT
const char *mqtt_user = "";                    // Логин от сервер
const char *mqtt_pass = "";                    // Пароль от сервера

//#define MQTT_MAX_PACKET_SIZE 1024
WiFiClient wclient;
PubSubClient client(wclient, mqtt_server, mqtt_port);

// wifiMulti----
//#ifndef STASSID
//#define STASSID "your-ssid"
//#define STAPSK  "your-password"
//#endif

IPAddress ip(192, 168, 0, 17); //статический IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
const char *ssid1 = "DIR-825-8e26";
const char *password1 = "Mdcvsww0805197922";

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisn"
#endif

#include "memory_allocation_EEPROM.h"

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

#ifdef ESP8266
ESP8266WebServer server(80);
#endif

#ifdef ESP32
WebServer server(80);       // ESP32WebServer server(80);
#endif

// MDNSResponder mdns;        //назначаем экземпляр класса ESP8266mDNS
//////WiFiClient client;
//////HTTPClient http;
byte checkClientAccessPointRom = 255;
int counterAnalogInput = 0;

String form1_2;
//const int led = LED_BUILTIN;


int symbolStart = 0;
int symbolEnd = 0;
#include "classRele.h"
#include "classSensor.h"
#include"classTimerAndDate.h"
#include "classGetDateInternet.h"
#include "web.h"
#include "setup.h"
#include "loop.h"
#include "functionEEPROM.h"
#include "callBack.h"
#include "objectToJson.h"
#include "contrTemp.h"
#include "dateFunctions.h"
#include "other_functions.h"
#include "debugerFunctions.h"
//*****************************************************************************
