<h1>【練習題目 : NodeMCU LED 遙控開關】</h1>

## 準備材料 : 
>1. NodeMCU 板(CH340驅動程式.USB:MicroUSB)
>2. MicroUSB 連接線 X 1
>3. LED 一顆
>4. 杜邦線數條
>5. 麵包板 X 1
===

## NodeMCU 腳位圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/Blink/nodemcu_pin.PNG?raw=true)

## LED控制電路圖
LED 正 : D4
LED 負 : GND

## 相關函式 : 無

## 網頁控制畫面

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/LEDControl/LEDControl.PNGraw=true)

## 程式說明

[以下程式來源 ESP8266WIFI_LEDControl.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/LEDControl/ESP8266WIFI_LEDControl.ino "ESP8266WIFI_LEDControl.ino"
[以下程式來源 ESP8266WIFI_LEDControl.ino ]
``` arduino
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "DerrickSamsung"
#define STAPSK  "16099725"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // prepare LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    val = 1;
  } else {
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  // Set LED according to the request
  digitalWrite(LED_BUILTIN, val);

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }

  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n"));
  //client.print(F("<br><br><iframe src='https://youtu.be/jnhfRO0Il0Y' width='1000' height='100' frameborder='1' scrolling='no'></iframe>"));
  client.print(F("<br><br><iframe width='560' height='315' src='https://www.youtube.com/embed/videoseries?list=PLx0sYbCqOb8TBPRdmBHs5Iftvv9TPboYG' frameborder='0' allow='autoplay; encrypted-media' allowfullscreen></iframe>"));
  client.print(F("<br><br> 現在 LED 是"));
  client.print((val) ? F("開") : F("關"));
  client.print(F("<br><br> <input type=button value='LED開' onclick=location.href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1' >"));
  client.print(F(" <input type=button value='LED關' onclick=location.href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0' >"));
  client.print(F("</html>"));

  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));
}
```






