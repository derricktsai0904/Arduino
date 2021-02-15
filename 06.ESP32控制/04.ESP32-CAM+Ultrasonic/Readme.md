<h1>【練習題目 : ESP32-CAM + 超音波感測 拍照】</h1>

## 準備材料 : 
>1. ESP32-CAM 板
>2. PL2303 連接線 X 1
>3. 超音波感測器 SR05 X 1
>4. 杜邦線數條
>5. 麵包板 X 1
===

## ESP32-CAM 腳位圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/ESP32-CAM_pin.PNG?raw=true)

## PL2303電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/PL2303.JPG?raw=true)

## 超音波感測器電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/Ultrasonic.JPG?raw=true)

## 相關函式 : 無

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








