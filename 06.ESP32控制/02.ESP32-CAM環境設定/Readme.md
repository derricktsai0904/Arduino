<h1>【題目 : ESP32-CAM 環境設定】</h1>

## 準備材料 : 
>1. ESP32-CAM 板
>2. MicroUSB 連接線 X 1
>3. OV7670攝像頭
>4. 杜邦線數條
>5. 麵包板 X 1
>6. FTDI 232 板 X 1
===

## ESP32-CAM 圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM_pin.PNGraw=true)

## ESP32-CAM Arduino 初始化設定
==>輸入
https://dl.espressif.com/dl/package_esp32_index.json

>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Setting1.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Setting2.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Setting3.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Setting4.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/TTL.JPG?raw=true)

## ESP32-CAM 燒錄說明

>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-FTDI-programmer-5V-supply.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Burn.PNG?raw=true)
燒錄時，IO0 跟 GND 要接起來，如果燒錄不成功，請按RESET 再燒錄一次，燒錄完成要將 IO0與GND 斷開。

選擇開發板為ESP32 Wrover Module
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Setting5.png?raw=true)
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/02.ESP32-CAM%E7%92%B0%E5%A2%83%E8%A8%AD%E5%AE%9A/ESP32-CAM-Sample.png?raw=true)

## ESP32-CAM Arduino 初始化設定

## 程式說明

[以下程式來源 ESP8266-Blink.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/Blink/ESP8266-Blink.ino "ESP8266-Blink.ino"
[以下程式來源 ESP8266-Blink.ino ]
``` arduino
#define D0 16 

void setup() {
  pinMode(D0, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D0, LOW);
  delay(1000);
  digitalWrite(D0, HIGH);
  delay(1000);
}

```
