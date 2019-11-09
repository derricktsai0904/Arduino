<h1>【練習題目 : 霹靂燈控制】</h1>

## 準備材料 : 
>1. Arduino Nano 板(CH340驅動程式.USB:MicroUSB)
>2. MicroUSB 連接線 X 1
>3. 七段顯示器(共陰極) X 1
>4. 4X4 鍵盤 X 1
>5. 杜邦線數條
>6. 麵包板 X 1
===
 
>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/A.LED%E6%8E%A7%E5%88%B6/Arduino_LED.PNG?raw=true)

## 霹靂燈控制電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/B.%E9%9C%B9%E9%9D%82%E7%87%88%E6%8E%A7%E5%88%B6/Arduino_PiliLED.PNG?raw=true)

## 相關函式 : 無

## 程式說明

[以下程式來源 PiliLED.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/B.%E9%9C%B9%E9%9D%82%E7%87%88%E6%8E%A7%E5%88%B6/PiliLED.ino "PiliLED.ino"
[以下程式來源 PiliLED.ino ]
``` arduino

int ledPins[] = {2, 3, 4, 5, 6};  // 宣告 Arduino 連結 LED 腳位

// Arduino 啟始函式，只會執行一次
void setup() {
  // 設定腳位為輸出訊號
  for(int i=0;i<5;i++){ // for 迴圈 執行五次
    pinMode(ledPins[i], OUTPUT);
  }
}

// Arduino 主要迴圈，執行無窮多次，直到關機為主
void loop() {
  // 霹靂燈由 2->6
  for(int i=0;i<5;i++){ // 燈號由小到大
      for(int j=0;j<5;j++){
         if(i==j){
            digitalWrite(ledPins[j], HIGH);   // 設定 LED 亮
         }
         else
         {
            digitalWrite(ledPins[j], LOW);   // 設定 LED 關
         }
      }  // for j 迴圈
      delay(100);
  } // for i 迴圈
  
  // 霹靂燈由 6->2
  for(int i=4;i>=0;i--){ // 燈號由小到大
      for(int j=0;j<5;j++){
         if(i==j){
            digitalWrite(ledPins[j], HIGH);   // 設定 LED 亮
         }
         else
         {
            digitalWrite(ledPins[j], LOW);   // 設定 LED 關
         }
      }  // for j 迴圈
      delay(100);
  } // for i 迴圈

}
```
