<h1>【練習題目 : NodeMCU LED 控制(Blink)】</h1>

## 準備材料 : 
>1. Arduino Nano 板(CH340驅動程式.USB:MicroUSB) X 1
>2. FTDI232板 X 1
>3. MicroUSB 連接線 X 1
>4. 杜邦線數條
>5. LED 一顆
>6. 麵包板 X 1
===

## Arduino Nano 圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/05.FTDI232_Program_Setting/Arduino_nano.PNG?raw=true)

## FTDI232 圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/05.FTDI232_Program_Setting/FTDI232.PNG?raw=true)


## FTDI232 Update Driver 圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/05.FTDI232_Program_Setting/update_Driver.png?raw=true)


## FTDI232 Update USB Serial Driver 圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/05.FTDI232_Program_Setting/update_usb.png?raw=true)


## 程式說明

[以下程式來源 BlinkTest.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/05.FTDI232_Program_Setting/BlinkTest.ino "BlinkTest.ino"
[以下程式來源 BlinkTest.ino ]
``` arduino
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

```






