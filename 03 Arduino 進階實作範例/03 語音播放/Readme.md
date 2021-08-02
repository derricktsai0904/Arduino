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

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/03%20%E8%AA%9E%E9%9F%B3%E6%92%AD%E6%94%BE/Arduino_NANO.jpg?raw=true)

## DFPlayer Mini 腳位圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/03%20%E8%AA%9E%E9%9F%B3%E6%92%AD%E6%94%BE/DFPlayer_Mini.JPG?raw=true)

## KY-037 聲音感測器腳位圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/03%20%E8%AA%9E%E9%9F%B3%E6%92%AD%E6%94%BE/md-ky-037.jpg?raw=true)

## 聲音感測+語音播放控制電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/03%20%E8%AA%9E%E9%9F%B3%E6%92%AD%E6%94%BE/Sound_Sensor.JPG?raw=true)


## 相關函式 : 無
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

## 程式說明

[以下程式來源 Speak_20210706.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/03%20%E8%AA%9E%E9%9F%B3%E6%92%AD%E6%94%BE/Speak_20210706.ino "Speak_20210706.ino"
[以下程式來源 Speak_20210706.ino ]
``` arduino
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(2,3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int playSeq = 1;
int lastv;
int sensorValue;

void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  delay(1000);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
  //myDFPlayer.start();

  lastv=0;
}

void loop()
{
  static unsigned long timer = millis();
    if (millis() - timer > 100) {
      timer = millis();
      //myDFPlayer.next();
      //delay(1000);
      //myDFPlayer.next();   //Play next mp3 every 3 second. 
      //myDFPlayer.enableLoopAll();
      //myDFPlayer.playLargeFolder(1,1);
       //myDFPlayer.loopFolder(1);
      //myDFPlayer.randomAll();

      sensorValue = analogRead(A0);  //讀取A0的值
      if( abs(sensorValue - lastv) >5 ){
          int v = (sensorValue - lastv);
          Serial.println(sensorValue);       //在監控視窗顯示讀取的值
          lastv = sensorValue;
          if (v > 0){
             Serial.println("play");
             play(1);
             delay(5000);
          }
      }
    }
    
    if (myDFPlayer.available()) {
      printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }
}

void play(int s){
  myDFPlayer.start();
  for(int i=1;i<=s-1;i++){
       myDFPlayer.next();
       if(s>=3){
         delay(80);
       }
      // Serial.print(" next");
  }
   Serial.println(s);
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    //case DFPlayerUSBInserted:
      //Serial.println("USB Inserted!");
      //break;
//    case DFPlayerUSBRemoved:
  //    Serial.println("USB Removed!");
    //  break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}

```






