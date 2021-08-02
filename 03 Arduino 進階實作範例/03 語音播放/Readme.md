<h1>【練習題目 : 聲音感測 + 語音播放】</h1>

## 準備材料 : 
>1. Arduino Nano板(CH340驅動程式.USB:MicroUSB)
>2. MicroUSB 連接線 X 1
>3. KY-037 聲音感測器 X 1
>4. DFPlayer Mini 播放器 X 1
>5. 8Ω 0.5W 喇叭 X 1
>6. 1k ohm 電阻 X 2
>7. 麵包板 X 1
===

## Arduino Nano 腳位圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/Blink/nodemcu_pin.PNG?raw=true)

## DFPlayer Mini 腳位圖 

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






