<h1>【練習題目 : 手機控制 藍芽LED 電路】</h1>

## 準備材料 : 
>1. Arduino Nano 板(CH340驅動程式.USB:MicroUSB)
>2. 藍芽模組 HC-05 X 1
>3. MicroUSB 連接線 X 1
>4. LED 一顆
>5. 杜邦線數條
>6. 麵包板 X 1
===
 
>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/Arduino_BT_LED.JPG?raw=true)

## 藍芽HC-05 AT Command 電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/BT_AT_CMD_C.JPG?raw=true)

##特別特別要注意一點，HC-05 Key腳位一定要在高電位才能進入AT Command模式

## 相關函式 : SoftwareSerial.h

[HC-05藍芽元件AT COMMANDS指令參考 hc-05_at_commands.pdf ]:https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/hc-05_at_commands.pdf "hc-05_at_commands.pdf"

[HC-05藍芽元件AT COMMANDS指令參考 hc-05_at_commands.pdf ]

## 程式說明

[以下程式來源 BT_AT_CMD.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/BT_AT_CMD.ino "BT_AT_CMD.ino"
[以下程式來源 BT_AT_CMD.ino ]
``` arduino
#include <SoftwareSerial.h>   // 引用程式庫
 
// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8,9); // 接收腳, 傳送腳
// HC05:TX->8  RX->9
char val;  // 儲存接收資料的變數
 
void setup() {
  Serial.begin(38400);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
 
  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成38400
  BT.begin(38400);
}
 
void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
 
  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
  if (BT.available()) {
    val = BT.read();
    Serial.print(val);
  }
}

```

## 藍芽 HC-05 AT COMMAND 模式執行結果

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/BT_AT_CMD_SAMPLECODE.JPG?raw=true)
