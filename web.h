
const String eyaOpen = "<svg xmlns=\" viewBox=\"0 0 20 20\"><path d=\"M.2 10a11 11 0 0 1 19.6 0A11 11 0 0 1 .2 10zm9.8 4a4 4 0 1 0 0-8 4 4 0 0 0 0 8zm0-2a2 2 0 1 1 0-4 2 2 0 0 1 0 4z\"/></svg>";
const String eyaClose = "<svg xmlns=\" viewBox=\"0 0 20 20\"><path d=\"M12.81 4.36l-1.77 1.78a4 4 0 0 0-4.9 4.9l-2.76 2.75C2.06 12.79.96 11.49.2 10a11 11 0 0 1 12.6-5.64zm3.8 1.85c1.33 1 2.43 2.3 3.2 3.79a11 11 0 0 1-12.62 5.64l1.77-1.78a4 4 0 0 0 4.9-4.9l2.76-2.75zm-.25-3.99l1.42 1.42L3.64 17.78l-1.42-1.42L16.36 2.22z\"/></svg>";
//.password-control {cursor: pointer;position: absolute;top:28px;right: 10px;display: inline-block;width: 20px;height: 20px;background: url(https://snipp.ru/demo/495/view.svg) 0 0 no-repeat;}\
//
//                .password-control.view {background: url(https://snipp.ru/demo/495/no-view.svg) 0 0 no-repeat;}.input-ssid {margin-bottom: 5px;} .ssid-items__active {background-color: brown;}\
//-----------------------------------------------------------------------------
const String head = "<!DOCTYPE html><html><head><meta charset=\"utf-8\" /><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" /><!-- <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\" /> --><title>ESP8266 Web Server POST handling</title>";
//const String pageStyles = "<style>\
//body{background-color: #cccccc;font-family: Arial, Helvetica, Sans-Serif;Color: #000088;position: relative;}\
//.scan-wifi {position: relative;max-width: 400px;margin: 0 auto;padding: 15px;background-color: rgb(32, 223, 223);border: 1px solid #000088;border-radius: 20px;padding: 10px;transition: margin 0.5s ;}\
//.scan__closed {position: absolute;display: none;right: 10px;top: -5px;font-size: 45px;font-weight: 900;cursor: pointer;transition: color 0.3s;}\
//a{text-decoration: none;border: 1px solid ;padding: 5px;background-color: antiquewhite;border-radius: 10px;}\
//.scan-wifi_list {margin: 10px 0;border: 1px solid #000000;background-color:#cccccc;border-radius: 5px;padding: 2px 10px;font-size: 20px;}\
//.scan-wifi__active .scan-wifi_list {background-color:burlywood;cursor: pointer;}\
//.connect p{text-align:center;padding:0;margin:3px;}\
//.scan-wifi__active .scan__closed {display: block;}.container {max-width: 500px;margin: 0 auto;padding:10px 15px;}.main-title {text-align:center;margin: 0 auto;}\
//.input {line-height: 2;}.btn1 {border-radius: 5px;background-color: lightcoral;cursor: pointer;line-height: 2;}.link-box {text-align: center;margin: 30px 0;}\
//.input-pass{padding-right:30px;}.link {color: inherit;padding: 0;text-transform: uppercase;margin: 0 20px;height: auto;width: 150px;}\
//.form-ssid {margin:0 auto;padding: 10px;max-width: 450px;display: grid;grid-template-columns: 1fr;gap: 20px;}.ssid-items {display: flex;background-color: aquamarine;padding: 5px;}\
//.ssid-items__input {min-width: 230px;display: flex;flex-direction: column;margin-right: 20px;position: relative;}\
//.password-control {cursor: pointer;position: absolute;top:40px;right: 10px;display: inline-block;width: 20px;height: 20px;background: url(https://snipp.ru/demo/495/view.svg) 0 0 no-repeat;}\
//.password-control.view {background: url(https://snipp.ru/demo/495/no-view.svg) 0 0 no-repeat;}.input-ssid {margin-bottom: 5px;} .ssid-items__active {background-color: brown;}\
//.add-ssid, .clear-ssid {background-color: coral;line-height: 2;border-radius: 10px;padding: 0 5px;width: 150px;cursor: pointer;text-align: center;margin-bottom: 5px;}\
//.clear-ssid__check {margin-top: 10px;}.add-ssid:active {background-color: blue;}\
//.popap {position: fixed;top: -400px;left: -400px;background-color: chartreuse;width: 300px;padding: 10px 0;transition: top 0.5s, left 0.5s;}\
//.popap-active {top: 20px;left: 20px;}.popap__list {margin: 40px 20px 20px 20px;padding: 0;}\
//.popap__item {list-style: none;padding: 0 10px ;margin:  5px;line-height: 1.5;background-color: crimson;border-radius: 10px;cursor: pointer;}\
//.popap__item:focus {background-color:darkcyan;}.popap__closed {position: absolute;right: 10px;top: -5px;font-size: 45px;font-weight: 900;cursor: pointer;transition: color 0.3s;}\
//.popap__closed:hover {color: red;}\
//.reset {position: absolute;top: 15px;left: 50px;} .connect-server, .connect-router {position: absolute;right: 50px;top: 15px;}.disable {display: none;}\
//.scan-wifi__title {color: red;text-align: center;font-size: 1rem;padding: 0;margin: 0;padding-top: 50px;}\
//</style>";

const String pageStyles = "<style>\
body{background-color: #cccccc;font-family: Arial, Helvetica, Sans-Serif;Color: #000088;position: relative;}\
.scan-wifi {position: relative;max-width: 400px;margin: 0 auto;padding: 15px;background-color: rgb(32, 223, 223);border: 1px solid #000088;border-radius: 20px;padding: 10px;transition: margin 0.5s ;}\
.scan__closed {position: absolute;display: none;right: 10px;top: -5px;font-size: 45px;font-weight: 900;cursor: pointer;transition: color 0.3s;}\
a{text-decoration: none;border: 1px solid ;padding: 5px;background-color: antiquewhite;border-radius: 10px;}\
.scan-wifi_list {margin: 10px 0;border: 1px solid #000000;background-color:#cccccc;border-radius: 5px;padding: 2px 10px;font-size: 20px;}\
.scan-wifi__active .scan-wifi_list {background-color:burlywood;cursor: pointer;}\
.connect p{text-align:center;padding:0;margin:3px;}\
.scan-wifi__active .scan__closed {display: block;}.container {max-width: 500px;margin: 0 auto;padding:10px 15px;}.main-title {text-align:center;margin: 0 auto;}\
.input {line-height: 2;}.btn1 {border-radius: 5px;background-color: lightcoral;cursor: pointer;line-height: 2;}.link-box {text-align: center;margin: 30px 0;}\
.input-pass{padding-right:30px;}.link {color: inherit;padding: 0;text-transform: uppercase;margin: 0 20px;height: auto;width: 150px;}\
.form-ssid {margin:0 auto;padding: 10px;max-width: 450px;display: grid;grid-template-columns: 1fr;gap: 20px;}.ssid-items {display: flex;background-color: aquamarine;padding: 5px;}\
.ssid-items__input {min-width: 230px;display: flex;flex-direction: column;margin-right: 20px;position: relative;}.ssid-items__active {background-color: brown;}\
.add-ssid, .clear-ssid {background-color: coral;line-height: 2;border-radius: 10px;padding: 0 5px;width: 150px;cursor: pointer;text-align: center;margin-bottom: 5px;}\
.clear-ssid__check {margin-top: 10px;}.add-ssid:active {background-color: blue;}\
.popap {position: fixed;top: -400px;left: -400px;background-color: chartreuse;width: 300px;padding: 10px 0;transition: top 0.5s, left 0.5s;}\
.popap-active {top: 20px;left: 20px;}.popap__list {margin: 40px 20px 20px 20px;padding: 0;}\
.popap__item {list-style: none;padding: 0 10px ;margin:  5px;line-height: 1.5;background-color: crimson;border-radius: 10px;cursor: pointer;}\
.popap__item:focus {background-color:darkcyan;}.popap__closed {position: absolute;right: 10px;top: -5px;font-size: 45px;font-weight: 900;cursor: pointer;transition: color 0.3s;}\
.popap__closed:hover {color: red;}\
.reset {position: absolute;top: 15px;left: 50px;} .connect-server, .connect-router {position: absolute;right: 50px;top: 15px;}.disable {display: none;}\
.scan-wifi__title {color: red;text-align: center;font-size: 1rem;padding: 0;margin: 0;padding-top: 50px;}\
</style>";

const String pageBody_1 = "</head><body>";
const String pageBody_2 = "<div class=\"container\"><div class=\"scan-wifi\">\
 <div class=\"scan__closed\">X</div>\
<p class=\"scan-wifi__title\">Доступні мережі-Available networks-Dostupné sítě</p>\
<div class=\"scan-wifi__inner\">\
<a class=\"reset\" href=\"/\">Update</a>";
const String form1_3 = "</div>";
const String pageForm_1 = "</div></div><div class=\"container\"><div class=\"connect\">\
<p>Список зарегістрованих роутерів</p>\
<p>List of registered routers</p>\
<p>Seznam registrovaných routerů</p>\
<form class=\"form-ssid\" method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"router\">";
//
//const String items1_1 = "<div class=\"ssid-items\">\
//<div class=\"ssid-items__input\">\
//<input class=\"input input-ssid\" type=\"text\" name=\"SSID-";
//const String items1_2 = "\" maxlength=\"";
//const String items1_3 = "\" value=\"";
//const String items1_4 = "\"  placeholder=\"Enter your SSID\">\
//<input class=\"input input-pass\" type=\"text\" name=\"Passowrd-";
//const String items1_5 = "\" maxlength=\"";
//const String items1_6 = "\" value=\"";
//const String items1_7 = "\" placeholder=\"Enter your PASSWORD\">\
//<p class=\"password-control\"></p>\
//</div>\
//<div class=\"ssid-items__btn\">\
//<div class=\"add-ssid\">Add a router</div>\
//<div class=\"clear-ssid\"> Clear data</div>\
//</div>\
//</div>";
//
//


const String end_form = "<input class=\"btn1\" type=\"submit\" value=\"Save\">\
</form></div></div>";



const String pageScript_1 = "<script>{\
document.querySelectorAll('.password-control').forEach(function(e){\
e.addEventListener('click',function(){\
const typePass = e.closest('.ssid-items__input').querySelector('.input-pass');\
if(typePass.getAttribute('type') == 'password'){\
typePass.setAttribute('type', 'text');\
e.classList.add('view');\
}else{\
typePass.setAttribute('type', 'password');\
e.classList.remove('view');\
}\
});\
});\
}</script>";

//const String pageScript_1 = "";

const String pageScript_2 = "<script>let ssidd;\
let passs;\
let activSSid;\
document.querySelectorAll('.clear-ssid').forEach(function (e) {\
e.addEventListener('click', function() {\
e.closest('.ssid-items').querySelector('.input-pass').value = '';\
e.closest('.ssid-items').querySelector('.input-ssid').value = '';\
});\
});\
document.querySelectorAll('.scan-wifi_list').forEach(function(e){\
e.addEventListener('click', function() {\
ssidd.value = e.innerHTML;\
passs.value = '';\
e.focus();\
});\
});\
document.querySelectorAll('.add-ssid').forEach(function (e) {\
e.addEventListener('click', function () {\
ssidd=  e.closest('.ssid-items').querySelector('.input-ssid');\
passs = e.closest('.ssid-items').querySelector('.input-pass');\
activSSid = e.closest('.ssid-items');\
e.closest('.ssid-items').classList.add('ssid-items__active');\
document.querySelector('.scan-wifi').classList.add('scan-wifi__active');\
});\
}); \
document.querySelector('.scan__closed').addEventListener('click', function(){\
activSSid.classList.remove('ssid-items__active');\
activSSid = null;\
ssidd=null;\
passs=null;\
document.querySelector('.scan-wifi').classList.remove('scan-wifi__active');\
});</script>";

const String endBody = "</body></html>";

const String pageClient = "<!DOCTYPE html><html><head> <meta charset=\"utf-8\" /><title>ESP8266 Web Server POST handling</title>\
<style>\
body{background-color: #cccccc;font-family: Arial, Helvetica, Sans-Serif;Color: #000088;position: relative;}\
</style>\
</head><body>\
  <p class=\"main-title\">Пристрій перейшов в режим клієнта.</p>\
<p class=\"main-title\">Він автоматично підключеться до найкращого по сигналу роутера</p>\
<p class=\"main-title\">Якщо підключення буде неуспішне повторіть процедуру</p>\
<p class=\"main-title\">The device has entered client mode..</p>\
<p class=\"main-title\">It will automatically connect to the router with the best signal</p>\
<p class=\"main-title\">if the connection is unsuccessful, repeat the procedure</p>\
<p class=\"main-title\">Zařízení vstoupilo do klientského režimu.</p>\
<p class=\"main-title\">Automaticky se připojí k routeru s nejlepším signálem</p>\
<p class=\"main-title\">pokud je připojení neúspěšné, opakujte postup</p>\
</body></html>";

const String pageAccessPoint = "<!DOCTYPE html><html><head> <meta charset=\"utf-8\" /><title>ESP8266 Web Server POST handling</title>\
<style>\
body{background-color: #cccccc;font-family: Arial, Helvetica, Sans-Serif;Color: #000088;position: relative;}\
</style>\
</head><body>\
<p class=\"main-title\">Пристрій перейшов в режим точки доступа. Access Point</p>\
<p class=\"main-title\">Підключіться до роутера з іменем ESPap</p>\
<p class=\"main-title\">Введіть ip address http://192.168.4.1/</p>\
<p class=\"main-title\">Виберіть доступні роутери, введіть пароль і збережіть його</p>\
<p class=\"main-title\">Після цього натисніть кнопку Переходимо в режим клієнт</p>\
<p class=\"main-title\">The device has entered access point mode. Access Point</p>\
<p class=\"main-title\">Connect to the router with the name ESPap</p>\
<p class=\"main-title\">Input ip address http://192.168.4.1/</p>\
<p class=\"main-title\">Select the available routers, enter the password and save it</p>\
<p class=\"main-title\">After that, click the Let's switch to client mode button</p>\
<p class=\"main-title\">Zařízení vstoupilo do režimu přístupového bodu.. Access Point</p>\
<p class=\"main-title\">Připojte se k routeru se jménem ESPap</p>\
<p class=\"main-title\">Vstupte ip address http://192.168.4.1/</p>\
<p class=\"main-title\">Vyberte dostupné routery, zadejte heslo a uložte jej</p>\
<p class=\"main-title\">Poté klikněte na tlačítko Přepněte do klientského režimu</p>\
</body></html>";



void homePage()
{
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html", head);
  server.sendContent(pageStyles);
  server.sendContent(pageBody_1);

  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)
  { // client
    server.sendContent("<div class=\"container\"><h1 class=\"main-title\">Виберіть роутери для підключення</h1><br></div>");
  }
  else
  {
    server.sendContent("\
<p class=\"main-title\">Пристрій в режимі точки доступа. ACCESS POINT</p>\
<p class=\"main-title\">Виберіть доступні роутери, введіть пароль і збережіть</p>\
<p class=\"main-title\">Після цього натисніть кнопку Переходимо в режим клієнт</p>\
<p class=\"main-title\">The device is in access point mode ACCESS POINT</p>\
<p class=\"main-title\">Select the available routers, enter the password and save</p>\
<p class=\"main-title\">After that, click the Let's switch to client mode button</p>\
<p class=\"main-title\">Zařízení je v režimu přístupového bodu. ACCESS POINT</p>\
<p class=\"main-title\">Vyberte dostupné routery, zadejte heslo a uložte</p>\
<p class=\"main-title\">Poté klikněte na tlačítko Přepněte do klientského režimu</p>\
<br>");
  }

  server.sendContent(pageBody_2);

  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)
  { // client
    //  if (checkClientAccessPointRom > 0) { //client
    server.sendContent("<a href=\"checkedAccesPoint\" class=\"connect-server\">Switch to server mode</a>");
  }
  else
  {
    server.sendContent("<a href =\"checkedClient\" class=\"connect-router\">Switch to client mode</a>");
  }
  server.sendContent(form1_3);
  server.sendContent(form1_2);
  server.sendContent(pageForm_1);





  for (byte i = 1; i <= NUMBER_CLIENT_CONNECT; i++ ) {
    String newSsidString = "<div class=\"ssid-items\"><div class=\"ssid-items__input\"><input class=\"input input-ssid\" type=\"text\" name=\"SSID-";
    newSsidString += String(i);
    newSsidString += "\" maxlength=\"";
    newSsidString += String(LENGTH_SSID);
    newSsidString += "\" value=\"";
    newSsidString += arraySsid[i - 1];
    newSsidString += "\"  placeholder=\"Enter your SSID\"><input class=\"input input-pass\" type=\"text\" name=\"Passowrd-";
    newSsidString += String(i);
    newSsidString += "\" maxlength=\"";
    newSsidString += String(LENGTH_PASSWORD);
    newSsidString += "\" value=\"";
    newSsidString += arrayPassword[i - 1];
    newSsidString += "\" placeholder=\"Enter your PASSWORD\">\
<p class=\"password-control\"></p>\
</div>\
<div class=\"ssid-items__btn\">\
<div class=\"add-ssid\">Add a router</div>\
<div class=\"clear-ssid\"> Clear data</div>\
</div>\
</div>";

    server.sendContent(newSsidString);
  }

  server.sendContent(end_form);

  server.sendContent(pageScript_1);
  server.sendContent(pageScript_2);
  //server.sendContent(pageScript_3);
  server.sendContent(endBody);
}

//--------------------------------------------------

void handleRoot()
{
  readEeprom();
  scanWifi();
  homePage();
}

//--------------------------------------------------

void router()
{
  if (server.method() != HTTP_POST)
  {
    // digitalWrite(led, 1);
    server.send(405, "text/plain", "Method Not Allowed");
    // digitalWrite(led, 0);
  }
  else
  {
    // digitalWrite(led, 1);
    String message = "POST form was:\n";
    String message1;
    for (uint8_t i = 0; i < server.args(); i++)
    {
      message1 += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.println(message1);
    //    Serial.println();
    //    Serial.println();
    int xx = message1.indexOf(" plain: SSID-1") - 1;
    // Serial.println("------------------------------------------------------------------------------");
    // Serial.println(message1);
    // Serial.println("------------------------------------------------------------------------------");
    message1 = message1.substring(0, xx); //Відкидаємо першу половину строки
    Serial.println(message1);
    Serial.println("------------------------------------------------------------------------------");

    for (int i = 1; i <= NUMBER_CLIENT_CONNECT; i++)
    { //Розбираємо строку на пароль і логін
      int n1 = message1.indexOf("SSID-" + String(i));
      int n2 = message1.indexOf("Passowrd-" + String(i));

      arraySsidInput[i - 1] = message1.substring(n1 + 8, n2 - 2); //Записуємо SSID
      n1 = message1.indexOf("SSID-" + String(i + 1));

      if (i == NUMBER_CLIENT_CONNECT) { //Записуємо паролі
        Serial.println(message1.substring(n2 + 12));
        arrayPasswordInput[i - 1] = message1.substring(n2 + 12);
      } else {
        Serial.println(message1.substring(n2 + 12, n1 - 2));
        arrayPasswordInput[i - 1] = message1.substring(n2 + 12, n1 - 2);
      }
    }

    writeEeprom();
    readEeprom();
    scanWifi();
    homePage();
  }
}

void router_two()
{
  if (server.method() != HTTP_POST)
  {
//    digitalWrite(led, 1);
    server.send(405, "text/plain", "Method Not Allowed");
//    digitalWrite(led, 0);
  }
  else
  {
//    digitalWrite(led, 1);
    String message = "POST form was:\n";
    String message1;
    for (uint8_t i = 0; i < server.args(); i++)
    {
      message1 += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    Serial.print("messageTest -- ");
    Serial.println(message1);
    message += message1;
    server.send(200, "text/plain", message);
//    digitalWrite(led, 0);
  }
}

void handleNotFound()
{
//  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  String message2;
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message2 += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  // Serial.print("message2 -- ");
  // Serial.println(message2);
  message += message2;
  server.send(404, "text/plain", message);
//  digitalWrite(led, 0);
}














#ifdef ESP8266
void scanWifi()
{
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0)
  {
    Serial.println(F("No networks found"));
  }
  else if (scanResult > 0)
  {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);
    // <p class=\"scan-wifi_list\">rbsrt</p>\

    // Print unsorted scan results
    form1_2 = "";
    for (int8_t i = 0; i < scanResult; i++)
    {
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
      form1_2 += "<p class=\"scan-wifi_list\">";

      form1_2 += ssid.c_str();
      form1_2 += "</p>";
      Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                    i,
                    channel,
                    bssid[0], bssid[1], bssid[2],
                    bssid[3], bssid[4], bssid[5],
                    rssi,
                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
                    hidden ? 'H' : 'V',
                    ssid.c_str());
      delay(0);
    }
  }
  else
  {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
}
#endif

#ifdef ESP32
void scanWifi()
{
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  Serial.println(F("Starting WiFi scan..."));
  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);
  if (scanResult == 0)
  {
    Serial.println(F("No networks found"));
  }
  else if (scanResult > 0)
  {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);


    form1_2 = "";
    for (int8_t i = 0; i < scanResult; i++)
    {
      //      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
      form1_2 += "<p class=\"scan-wifi_list\">";

      form1_2 += WiFi.SSID(i);
      form1_2 += "</p>";
      //      Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
      //                    i,
      //                    channel,
      //                    bssid[0], bssid[1], bssid[2],
      //                    bssid[3], bssid[4], bssid[5],
      //                    rssi,
      //                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
      //                    hidden ? 'H' : 'V',
      //                    ssid.c_str());
      //      delay(0);
    }
  }
  else
  {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
}
#endif
