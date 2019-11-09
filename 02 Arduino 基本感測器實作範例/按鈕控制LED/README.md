<h1>【練習題目 : 按鈕控制LED】</h1>

## 準備材料 : 
>1. Arduino Nano 板(CH340驅動程式.USB:MicroUSB)
>2. MicroUSB 連接線 X 1
>3. LED X 1
>4. 四腳開關 X 1
>5. 杜邦線數條
>6. 麵包板 X 1

===
 
>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/%E6%8C%89%E9%88%95%E6%8E%A7%E5%88%B6LED/Arduino_BUTTON_M.JPG?raw=true)

## 按鈕控制LED 電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/%E6%8C%89%E9%88%95%E6%8E%A7%E5%88%B6LED/Arduino_BUTTON_C.JPG?raw=true)

## 相關函式 : 無

## 程式說明

[以下程式來源 Button_LED.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/%E6%8C%89%E9%88%95%E6%8E%A7%E5%88%B6LED/Button_LED.ino "Button_LED.ino"
[以下程式來源 Button_LED.ino ]
``` arduino

void setup(){
  Serial.begin(115200);
  pinMode(2, INPUT);   // 宣告腳位 2 為輸入
  pinMode(12, OUTPUT); // 宣告腳位 12 為輸出
}

void loop(){
  int switchStatus = digitalRead(2);
  digitalWrite(12, switchStatus);
  Serial.println(switchStatus);
}
```
