
int LED = 13; // 宣告 Arduino 連結 LED 腳位

// Arduino 啟始函式，只會執行一次
void setup() {
  // 設定腳位為輸出訊號
  pinMode(LED, OUTPUT);
}

// Arduino 主要迴圈，執行無窮多次，直到關機為主
void loop() {
  digitalWrite(LED, HIGH);   // 設定 LED 亮
  delay(1000);               // 延遲一秒
  digitalWrite(LED, LOW);    // 設定 LED 關
  delay(1000);               // 延遲一秒
}
