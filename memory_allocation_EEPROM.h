
//--------------------------EEPROM---------------------------------
#define NUMBER_RELE 8
#define MAX_NUMBER_SENSOR 8
#define MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR  40

#define TOTAL_LENGTH_SECTION 0

//****************************************************************
//байт в EEPROM де позначається режим client=0 або accees point>0
#define LENGTH_ADRESS_CLIENT_OR_ACCESS_POINT 1
const int EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT =  (TOTAL_LENGTH_SECTION);//байт в EEPROM де позначається режим client=0 або accees point>0


//****************************************************************

#define TOTAL_LENGTH_SECTION_100 (TOTAL_LENGTH_SECTION + LENGTH_ADRESS_CLIENT_OR_ACCESS_POINT)

//****************************************************************
//Строка де зберігаємо імя пристрою
#define LENGTH_STRING_NAME_DEVICE 40
const int EEPROM_ADRESS_STRING_NAME_DEVICE =  (TOTAL_LENGTH_SECTION_100);//байт в EEPROM де позначається режим client=0 або accees point>0

//****************************************************************

#define TOTAL_LENGTH_SECTION_150 (TOTAL_LENGTH_SECTION_100 + LENGTH_STRING_NAME_DEVICE)

//****************************************************************
//логіни і паролі
#define NUMBER_CLIENT_CONNECT 4
#define LENGTH_SSID (10*2)
#define LENGTH_PASSWORD (10*2)
#define LENGTH_SECTION_SSID_ADN_PASSWORD  (LENGTH_SSID * NUMBER_CLIENT_CONNECT + LENGTH_PASSWORD * NUMBER_CLIENT_CONNECT)
const int START_SECTION_EEPROM_SSID_AND_PASSWORD = (TOTAL_LENGTH_SECTION_150);
String arraySsidInput[NUMBER_CLIENT_CONNECT];     //для логінів
String arrayPasswordInput[NUMBER_CLIENT_CONNECT]; //для паролів
String arraySsid[NUMBER_CLIENT_CONNECT];     //для логінів
String arrayPassword[NUMBER_CLIENT_CONNECT]; //для паролів

//****************************************************************

#define TOTAL_LENGTH_SECTION_200 (TOTAL_LENGTH_SECTION_150 + LENGTH_SECTION_SSID_ADN_PASSWORD)

//****************************************************************
//температура включеня Від -50 до 100 зміщаємо діапазон (-50градусів=0), (0градусів=50), (100градусів=150);
#define LENGTH_TEMP_ON_OFF (NUMBER_RELE * 2)
const int START_SECTION_EEPROM_TEMP_ON_OFF = (TOTAL_LENGTH_SECTION_200);//температура включеня Від -50 до 100 зміщаємо діапазон (-50градусів=0), (0градусів=50), (100градусів=150);
//****************************************************************
//****************************************************************

#define TOTAL_LENGTH_SECTION_300 (TOTAL_LENGTH_SECTION_200 + LENGTH_TEMP_ON_OFF)

//****************************************************************
// біт 0-3 номер датчика який управляє даним реле якщо код 15 то реле термодатчиком не керується, якщо інший код то він вказує на номер термодатчика, що керує реле
// біт 4 один або два діапазона контроля температрур
// біт 5 вкл або викл реле при зміні температур або таймера
// біт 6 стан реле при помилці термодатчмка
#define LENGTH_RELE_EEPROM_SENSOR  NUMBER_RELE
const int START_SECTION_RELE_EEPROM_SENSOR = (TOTAL_LENGTH_SECTION_300);

//****************************************************************

#define TOTAL_LENGTH_SECTION_400 (TOTAL_LENGTH_SECTION_300 + LENGTH_RELE_EEPROM_SENSOR)

//****************************************************************
#define LENGTH_RELE_EEPROM_UPR  NUMBER_RELE
const int START_SECTION_RELE_EEPROM_UPR = (TOTAL_LENGTH_SECTION_400);
//const int rele_0_eprom_upr ;
// біт 0 1-ручне або 0-від таймера чи термодатчика  manualAuto
// біт 1 1-Включене реле або 0-Відключене реле onOffManual
// біт 2 rezerva
// біт 3 rezerva
//****************************************************************

#define TOTAL_LENGTH_SECTION_500 (TOTAL_LENGTH_SECTION_400 + LENGTH_RELE_EEPROM_UPR)

//****************************************************************
#define LENGTH_SECTION_EEPROM_SENSOR_ADDRESS  MAX_NUMBER_SENSOR * 8
const int START_SECTION_EEPROM_SENSOR_ADDRESS = (TOTAL_LENGTH_SECTION_500);
//boolean flagRele = true;
//зберігає адреса для 20 датчиків кожен датчик займає 8 байт від 281 до 441
//****************************************************************

#define TOTAL_LENGTH_SECTION_600 (TOTAL_LENGTH_SECTION_500 + LENGTH_SECTION_EEPROM_SENSOR_ADDRESS)

//****************************************************************
#define LENGTH_SECTION_EEPROM_SENSOR_NAME  MAX_NUMBER_SENSOR * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR
const int START_SECTION_EEPROM_SENSOR_NAME = (TOTAL_LENGTH_SECTION_600);
//const int sensorNameEEprom = 442; //442 + 8*40 = 762
//8 imen по 40 байт
//****************************************************************

#define TOTAL_LENGTH_SECTION_700 (TOTAL_LENGTH_SECTION_600 + LENGTH_SECTION_EEPROM_SENSOR_NAME)

//****************************************************************
#define LENGTH_SECTION_EEPROM_RELE_NAME  NUMBER_RELE * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR
const int START_SECTION_EEPROM_RELE_NAME = (TOTAL_LENGTH_SECTION_700);
//const int releNameEEprom = 763; //763 + 8*40 = 1083
//8 imen по 40 байт

//****************************************************************

#define TOTAL_LENGTH_SECTION_800 (TOTAL_LENGTH_SECTION_700 + LENGTH_SECTION_EEPROM_RELE_NAME)

//****************************************************************
#define LENGTH_SECTION_EEPROM_TIMERDATE  NUMBER_RELE * 252
const int START_SECTION_EEPROM_TIMERDATE = (TOTAL_LENGTH_SECTION_800);
//const int timerDateEeprom = 1084;// (1084 + 252*8=3100)    byte  2byte-rik(2022-2099), 1byte-month(0-12), 1byte-day(1-31), 1byte-hour(0-23), 1byte-minute(0-59), 1byte-день тижня
//TimeEeprom =  byte 1byte - hodyna, 1byte - minute
//dayEeprom =  40 byte
//delayStartReleEeprom = 4 byte (0-100000 sekund)
//****************************************************************

#define TOTAL_LENGTH_SECTION_900 (TOTAL_LENGTH_SECTION_800 + LENGTH_SECTION_EEPROM_TIMERDATE)
