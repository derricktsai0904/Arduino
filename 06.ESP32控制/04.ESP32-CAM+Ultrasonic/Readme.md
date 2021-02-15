<h1>【練習題目 : ESP32-CAM + 超音波感測 拍照】</h1>

## 準備材料 : 
>1. ESP32-CAM 板
>2. PL2303 連接線 X 1
>3. 超音波感測器 SR05 X 1
>4. 杜邦線數條
>5. 麵包板 X 1
===

## ESP32-CAM 腳位圖 
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/ESP32-CAM_pin.PNG?raw=true)

## PL2303電路圖
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/PL2303.JPG?raw=true)
紅色:5V
黑色:GND
白色:RXD
綠色:TXD

## 超音波感測器電路圖
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/Ultrasonic.JPG?raw=true)

## ESP32-CAM + 超音波感測器 + LED 實作電路圖
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/ESP32-CAM%2BUltrasonic%2BLED.JPG?raw=true)


## 相關函式 : 無

## 程式說明

[以下程式來源 ESP8266-Blink.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/ESP32-CAM-Ultrasonic-Line_LED.ino "ESP32-CAM-Ultrasonic-Line_LED.ino"
[以下程式來源 ESP32-CAM-Ultrasonic-Line_LED.ino ]
``` arduino
#include <WiFi.h>
#include "esp_camera.h"
#include "esp_system.h"

#include "Arduino.h"
#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <EEPROM.h>            // read and write from flash memory

// define the number of bytes you want to access
#define EEPROM_SIZE 1

hw_timer_t *timer = NULL;
void IRAM_ATTR resetModule(){
    ets_printf("reboot\n");
    esp_restart();
}

#include <TridentTD_LineNotify.h>
#define SSID        "WIFI熱點名稱"   //WiFi name
#define PASSWORD    "WIFI連線密碼"   //PASSWORD
#define LINE_TOKEN  "Line權杖金鑰"   

// Pin definition for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

const int Led_Flash = 4;
const int trigPin = 13;
const int echoPin = 12;

const int LedBPin = 4;
const int LedGPin = 2;
const int LedRPin = 14;

int pictureNumber = 0;

boolean startTimer = false;
unsigned long time_now=0;
int time_capture=0;
long duration;
int distance;
void setup() {

  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  Serial.begin(115200);
   while (!Serial) {  ;  }
   
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
  pinMode(Led_Flash, OUTPUT);

  pinMode(LedRPin,OUTPUT);
  pinMode(LedGPin,OUTPUT);
  pinMode(LedBPin,OUTPUT);

  LedShow(1);
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  LINE.setToken(LINE_TOKEN);

  LedShow(2);

  timer = timerBegin(0, 80, true); //timer 0, div 80Mhz 
  timerAttachInterrupt(timer, &resetModule, true);
  timerAlarmWrite(timer, 20000000, false); //set time in us 15s
  timerAlarmEnable(timer); //enable interrupt

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG; 
  
  if(psramFound()){
    // FRAMESIZE_ +
    //QQVGA/160x120//QQVGA2/128x160//QCIF/176x144//HQVGA/240x176
    //QVGA/320x240//CIF/400x296//VGA/640x480//SVGA/800x600//XGA/1024x768
    //SXGA/1280x1024//UXGA/1600x1200//QXGA/2048*1536
    config.frame_size = FRAMESIZE_SXGA; 
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QQVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  
  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

}
void loop() {
    LedShow(2);
    timerWrite(timer, 0); //reset timer (feed watchdog)
    long tme = millis();
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
    
    if (( distance <= 100) && (distance != 0)) {
           LedShow(3);    
           Camera_capture();
           Serial.println("OK");
           startTimer = true;
           delay(200);    
    }
    if(millis() > time_now + 1000) {
           time_now = millis();
    }
    tme = millis() - tme;
    delay(200);
}

void Camera_capture() {
  digitalWrite(Led_Flash, HIGH);
  delay(100); 
  digitalWrite(Led_Flash, LOW);
  delay(100);
  digitalWrite(Led_Flash, HIGH);

  //Serial.println("Starting SD Card");
  if(!SD_MMC.begin()){
    Serial.println("SD Card Mount Failed");
    return;
  }
  
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD Card attached");
    return;
  }

  delay(100);
  
  camera_fb_t * fb = NULL;
  delay(200); 
  // Take Picture with Camera
  fb = esp_camera_fb_get(); 
  if(!fb) {
    Serial.println("Camera capture failed");
    return;
  }

   EEPROM.begin(EEPROM_SIZE);
   pictureNumber = EEPROM.read(0) + 1;

   // Path where new picture will be saved in SD Card
   String path = "/picture" + String(pictureNumber) +".jpg";

   fs::FS &fs = SD_MMC; 
   Serial.printf("Picture file name: %s\n", path.c_str());

   File file = fs.open(path.c_str(), FILE_WRITE);
   if(!file){
     Serial.println("Failed to open file in writing mode");
   } 
   else {
     file.write(fb->buf, fb->len); // payload (image), payload length
     Serial.printf("Saved file to path: %s\n", path.c_str());
     EEPROM.write(0, pictureNumber);
     EEPROM.commit();
   }
   
   digitalWrite(Led_Flash, LOW);
   Send_line(fb->buf,fb->len);

   file.close();
   esp_camera_fb_return(fb); 
  // Serial.println("Going to sleep now");
  // esp_deep_sleep_start();
  // Serial.println("This will never be printed");
}

void Send_line(uint8_t *image_data,size_t   image_size){
   LINE.notifyPicture("DETECT!!",image_data, image_size);
}

void LedShow(int pin){

    switch(pin){
      case 1:  //LED Blue
          digitalWrite(LedRPin,0);
          digitalWrite(LedGPin,0);
          digitalWrite(LedBPin,1);
          break;
      case 2:  //LED Green
          digitalWrite(LedRPin,0);
          digitalWrite(LedGPin,1);
          digitalWrite(LedBPin,0);
          break;
      case 3:  //LED Red
          digitalWrite(LedRPin,1);
          digitalWrite(LedGPin,0);
          digitalWrite(LedBPin,0);
          break;
      default:
          digitalWrite(LedRPin,0);
          digitalWrite(LedGPin,0);
          digitalWrite(LedBPin,0);
    }
}

```

