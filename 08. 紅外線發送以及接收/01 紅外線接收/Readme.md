

<h1>【說明 : 紅外線接收電路 </h1>

## 準備材料 : 
>1. Nano 開發板 X 1
>2. MicroUSB 連接線 X 1
>3. 38kHz 紅外線接收感測模組 X 1 <br>
===

## 紅外線接收器 腳位圖 
>![](IRRcv.jpg?raw=true)


[以下程式來源 IRRcv.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/08.%20%E7%B4%85%E5%A4%96%E7%B7%9A%E7%99%BC%E9%80%81%E4%BB%A5%E5%8F%8A%E6%8E%A5%E6%94%B6/01%20%E7%B4%85%E5%A4%96%E7%B7%9A%E6%8E%A5%E6%94%B6/IRRcv.ino "IRRcv.ino"
[以下程式來源 IRRcv.ino ]
``` arduino

//Install IRremote Version 4 or later

#include <IRremote.h>   // Ver 4 or later <-------<<<<<<<

#define DECODE_NEC

unsigned long irMillis;

//                                   s e t u p ( )
//******************************************************************************************
void setup()
{
  Serial.begin(9600);

  //**************************************
  const byte IR_RECEIVE_PIN = 7;

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

} //END of   setup()


//                                    l o o p ( )
//******************************************************************************************
void loop()
{
  //*******************************************************
  if (IrReceiver.decode())
  {
    IrReceiver.resume(); // Enable receiving of the next value
  }

  //*******************************************************
  //have we received a new IR code form the remote ?
  if (IrReceiver.decodedIRData.command != 0)
  {
    checkIRcode();
  }

} //END of   loop()


//                                c h e c k I R c o d e ( )
//******************************************************************************************
void checkIRcode()
{
  //RAW code
  Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);
 
  Serial.print("  ");   
  //command
  Serial.println(IrReceiver.decodedIRData.command);

  IrReceiver.printIRResultShort(&Serial); 

  switch (IrReceiver.decodedIRData.command)
  {

   case 1:
      {
        Serial.println("Press ====> 1");
      }
      break;
   case 2:
      {
        Serial.println("Press ====> 2");
      }
      break;
   case 3:
      {
        Serial.println("Press ====> 3");
      }
      break;

  }  //END of   switch...case


  //needed to block repeat codes
  IrReceiver.decodedIRData.command = 0;

} //END of   checkIRcode()


```
