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

## 藍芽HC-05 AT 控制 LED 電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/%E6%89%8B%E6%A9%9F%E6%8E%A7%E5%88%B6%E8%97%8D%E8%8A%BDLED/BT_ACTIVE_C.JPG?raw=true)

## 相關函式 : SoftwareSerial.h


## 程式說明

[以下程式來源 BT_LED__DEMO.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/%E6%89%8B%E6%A9%9F%E6%8E%A7%E5%88%B6%E8%97%8D%E8%8A%BDLED/BT_LED__DEMO.ino "BT_LED__DEMO.ino"
[以下程式來源 BT_LED__DEMO.ino ]
``` arduino
#include <SoftwareSerial.h>
#define RxD 8
#define TxD 9
#define LED 13  // 輸出LED燈

SoftwareSerial blueToothSerial(RxD,TxD); 

// 以下是接收到APP傳送藍芽的代號
const int LED_ON = 0x1;
const int LED_OFF = 0x2;
const int LED_SHIN = 0x3;

const int DELAY = 300;

unsigned char temp_val;
unsigned char Receive_val;
unsigned char len;
unsigned char Buffer_temp[4];
unsigned char i;

void UART_FUN()
{

  for(i=0;i<5;i++)
   Buffer_temp[i]=0x0;
    delay(100);
  while(blueToothSerial.available())            
  {                                                
     Receive_val=blueToothSerial.read();
      Serial.print(Receive_val); 
      Serial.print("\n"); 
     

     if(Receive_val==0xAA)
     {
         len=0;
        Buffer_temp[len++]=Receive_val;
     }
     else if(len < 5)
     {
        Buffer_temp[len++]=Receive_val;
     }
     
  }   
 
  if(Buffer_temp[0]==0xAA && Buffer_temp[1]==0xBB && Buffer_temp[3]==0xF1)
  {
   Serial.print("LED_ON \n"); 
   temp_val=LED_ON;
   }
   else if(Buffer_temp[0]==0xAA && Buffer_temp[1]==0xBB && Buffer_temp[3]==0xF2)
  {
   Serial.print("LED_OFF \n"); 
   temp_val=LED_OFF ;
   }
   else if(Buffer_temp[0]==0xAA && Buffer_temp[1]==0xBB && Buffer_temp[3]==0xF3)
  {
   Serial.print("LED_SHIN \n"); 
   temp_val=LED_SHIN ;
   } 

}


void setup()  
{
  pinMode(LED, OUTPUT);   
  Serial.begin(38400);  
  blueToothSerial.begin(38400);
  temp_val=0;     
  len=0;
}

void loop()
{
  UART_FUN();
  
  if(temp_val==LED_ON)
  {
      digitalWrite(LED, HIGH); 
  }
  else if(temp_val==LED_OFF)
  {
      digitalWrite(LED, LOW); 
  
  }
  else if(temp_val==LED_SHIN)
  {
     for(int i=0;i<5;i++){
       digitalWrite(LED, HIGH);
       delay(100);
       digitalWrite(LED, LOW);
       delay(100);
     }
     temp_val=LED_OFF;
  }
 
}

```

##掃描以下 QRCODE 下載 Android Apk 來安裝
>![](https://github.com/derricktsai0904/Arduino/blob/master/03%20Arduino%20%E9%80%B2%E9%9A%8E%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/01%20%E8%97%8D%E8%8A%BD%E6%87%89%E7%94%A8/%E6%89%8B%E6%A9%9F%E6%8E%A7%E5%88%B6%E8%97%8D%E8%8A%BDLED/BT_APK.JPG?raw=true)
