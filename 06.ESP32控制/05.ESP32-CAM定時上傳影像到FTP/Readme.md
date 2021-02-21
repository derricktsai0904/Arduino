<h1>【練習題目 : ESP32-CAM 定時上傳影像到 FTP】</h1>

## 準備材料 : 
>1. ESP32-CAM 板(CH340驅動程式)
>2. PL2303
>3. 杜邦線數條
>4. 麵包板 X 1
===
## ESP32-CAM 腳位圖 
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/ESP32-CAM_pin.PNG?raw=true)

## PL2303電路圖
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/PL2303.JPG?raw=true)
紅色:5V
黑色:GND
白色:RXD
綠色:TXD

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






