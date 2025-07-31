

<h1>【說明 : 紅外線發射電路 </h1>

## 準備材料 : 
>1. Nano 開發板 X 1
>2. MicroUSB 連接線 X 1
>3. 38kHz 紅外線發射模組 X 1 <br>
===

## 紅外線發射器 腳位圖 
>![](IRTrm.jpg?raw=true)

## 紅外線發射器 電路圖 
>![](IR_Transmitter_Circult.jpg?raw=true)

[以下程式來源 IRTrm.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/08.%20%E7%B4%85%E5%A4%96%E7%B7%9A%E7%99%BC%E9%80%81%E4%BB%A5%E5%8F%8A%E6%8E%A5%E6%94%B6/02%20%E7%B4%85%E5%A4%96%E7%B7%9A%E7%99%BC%E5%B0%84/IRTrm.ino "IRTrm.ino"
[以下程式來源 IRTrm.ino ]
``` arduino

#include <IRremote.h> // Include the IRremote library

#define IR_SEND_PIN 3 // Define the digital pin connected to the IR LED

void setup() {
  IrSender.begin(IR_SEND_PIN); // Initialize the IR sender
}

void loop() {
  // Send an NEC signal with address 0x0102 and command 0x34
  IrSender.sendNEC(0xDB34, 0x1, true); 
  // Parameters: address, command, enable repeat (true/false), number of repeats (if enabled)

  delay(1000); // Wait for one second before sending again
}

```
