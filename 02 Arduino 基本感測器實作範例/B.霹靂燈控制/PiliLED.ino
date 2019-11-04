
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
  } // for i 迴圈

}
