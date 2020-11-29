<h1>【說明 : ESP32基本環境設定</h1>

## 準備材料 : 
>1. ESP32 開發板 X 1
>2. MicroUSB 連接線 X 1
===

## ESP32 腳位圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/Blink/nodemcu_pin.PNG?raw=true)

## LED控制電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/Blink/NodeMCU_circuit.PNG?raw=true)

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






