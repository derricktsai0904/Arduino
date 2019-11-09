<h1>【練習題目 : 七段顯示器】</h1>

## 準備材料 : 
>1. Arduino Nano 板(CH340驅動程式.USB:MicroUSB)
>2. MicroUSB 連接線 X 1
>3. 七段顯示器(共陰極) X 1
>4. 杜邦線數條
>5. 麵包板 X 1
===
 
>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/C.4X4%E9%8D%B5%E7%9B%A4%E6%8E%A7%E5%88%B6%E4%B8%83%E6%AE%B5%E9%A1%AF%E7%A4%BA%E5%99%A8/Arduino_Keypad_Seven.JPG?raw=true)

## 七段顯示器電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/C.4X4%E9%8D%B5%E7%9B%A4%E6%8E%A7%E5%88%B6%E4%B8%83%E6%AE%B5%E9%A1%AF%E7%A4%BA%E5%99%A8/Arduino_Keypad_7_circuit.JPG?raw=true)

## 相關函式 : 無

## 程式說明

[以下程式來源 PiliLED.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/B.%E9%9C%B9%E9%9D%82%E7%87%88%E6%8E%A7%E5%88%B6/PiliLED.ino "PiliLED.ino"
[以下程式來源 PiliLED.ino ]
``` arduino

#include <Keypad.h>

int i;
int j;

// 設定一個 matrix，B0111111 最前面的 B 代表資料型態為 byte
// 後面跟的 0111111 則是上面對照表的 gfedcba 
const byte num[10]={
    B0111111,  //0
    B0000110,  //1
    B1011011,  //2
    B1001111,  //3
    B1100110,  //4
    B1101101,  //5
    B1111101,  //6
    B0000111,  //7    
    B1111111,  //8
    B1101111   //9    
};

// 設定顯示器各段對應的 pin
const int seg[]={2,3,4,5,6,7,8,9};  //ABCDEFG

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'F','E','D','C'},
  {'B','3','6','9'},
  {'A','2','5','8'},
  {'0','1','4','7'}
};
byte rowPins[ROWS] = {A3, A2, A1, A0}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 11, 10}; //connect to the column pinouts of the keypad


//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
    for(i=0;i<8;i++)
       pinMode(seg[i],OUTPUT);
       
    Serial.begin(9600);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.print("key-");
    Serial.println(customKey);

    i = customKey - '0';
    Serial.println(i);

   if(i==17){
     Serial.println(17);
     for(i=0;i<10;i++)
      {
       for(j=0;j<8;j++)
        {
         if(bitRead(num[i],j))
         digitalWrite(seg[j],HIGH);
         else
         digitalWrite(seg[j],LOW);        
        }
         delay(500);    
       } 
    } 
    Serial.println("end17");
   }
    else if(i==18){
      Serial.println(18);
      for(i=9;i>0;i--)
      {
        for(j=0;j<7;j++)
        {
         if(bitRead(num[i],j))
         digitalWrite(seg[j],HIGH);
         else
         digitalWrite(seg[j],LOW);        
        }
          delay(500);    
       } 
    }
    else{
      Serial.print(19);
      Serial.print("-");
      Serial.println(i);
      if( i<=9){
      for(j=0;j<8;j++)
      {
          // 讀取 0~9 matrix 裡的數字，ex: B0111111 的第0~6個位元
          // 並由對應的 pin 腳輸出高電壓，使 7 段 LED 發出對應的明亮
          if(bitRead(num[i],j))
              digitalWrite(seg[j],HIGH);
          else
              digitalWrite(seg[j],LOW);        
       }
        delay(100);    
    }//if( i<=9){
   } 
  }//if (customKey){
```
