ESP32_CAM + Line + 超音波 + Line 推播

## 準備材料 : 
>1. ESP32-CAM 板 X 1
>2. ISD1820 語音播放模組 X 1
>3. PL2303 連接線 X 1
>4. 超音波感測器 SR05 X 1
>5. 杜邦線數條
>6. 麵包板 X 1
===

## ESP32_Cam 腳位圖
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/09.ESP32-CAM%2BUltrasonic_Line/ESP32-Cam.jpg?raw=true)

## ISD1820 語音播放器
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/09.ESP32-CAM+Ultrasonic_Line/ISD1820%E8%85%B3%E4%BD%8D%E5%9C%96.jpg?raw=true?raw=true)

## 完整電路圖
>![](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/09.ESP32-CAM%2BUltrasonic_Line/SendLine.jpg?raw=true)


## 相關函式 : 注意 eps32 開發版 建議安裝 1.0.4 版本

## 程式說明
[以下程式來源 ESP32CAM_Line.ino ]:[https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/04.ESP32-CAM%2BUltrasonic/ESP32-CAM-Ultrasonic-Line_LED.ino](https://github.com/derricktsai0904/Arduino/blob/master/06.ESP32%E6%8E%A7%E5%88%B6/09.ESP32-CAM%2BUltrasonic_Line/ESP32CAM_Line.ino) "ESP32CAM_Line.ino"
[以下程式來源 ESP32CAM_Line.ino ]
``` arduino

//The maximum size image is XGA(1024x768).

// Enter your WiFi ssid and password
const char* ssid     = "XXXXXXXX";   // 網路熱點名稱(請修改) 
const char* password = "XXXXXXXX";   // 網路熱點密碼(請修改)
String myLineNotifyToken = "123456789009876543212azxccvb";  // Line Notify 權杖 請記得修改
int trigPin = 15;           // 請將超音波模組 Trig Pin 接  ESP32 CAM (GPIO15)
int echoPin = 14;           // 請將超音波模組 Echo Pin 接  ESP32 CAM (GPIO14)
int soundPin = 13;          // ESP32 CAM (GPIO13) 接到 ISD1820 P-E 腳位 

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#define CAMERA_MODEL_AI_THINKER
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

String sendImage2LineNotify(String msg) {
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();//取得相機影像放置fb
  if (!fb) {
    delay(100);
    Serial.println("Camera capture failed, Reset");
    ESP.restart();
  }
  WiFiClientSecure client_tcp;//啟動SSL wificlient
  Serial.println("Connect to notify-api.line.me");
  if (client_tcp.connect("notify-api.line.me", 443)) {
    Serial.println("Connection successful");
    String head = "--Taiwan\r\nContent-Disposition: form-data; name=\"message\"; \r\n\r\n" + msg + "\r\n--Taiwan\r\nContent-Disposition: form-data; name=\"imageFile\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--Taiwan--\r\n";
    uint16_t imageLen = fb->len;
    uint16_t extraLen = head.length() + tail.length();
    uint16_t totalLen = imageLen + extraLen;
    //開始POST傳送訊息
    client_tcp.println("POST /api/notify HTTP/1.1");
    client_tcp.println("Connection: close");
    client_tcp.println("Host: notify-api.line.me");
    client_tcp.println("Authorization: Bearer " + myLineNotifyToken);
    client_tcp.println("Content-Length: " + String(totalLen));
    client_tcp.println("Content-Type: multipart/form-data; boundary=Taiwan");
    client_tcp.println();
    client_tcp.print(head);
    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    Serial.println("Data Sending....");
    //照片，分段傳送
    for (size_t n = 0; n < fbLen; n = n + 2048) {
      if (n + 2048 < fbLen) {
        client_tcp.write(fbBuf, 2048);
        fbBuf += 2048;
      } else if (fbLen % 2048 > 0) {
        size_t remainder = fbLen % 2048;
        client_tcp.write(fbBuf, remainder);
      }
    }
    client_tcp.print(tail);
    client_tcp.println();
    String getResponse = "", Feedback = "";
    boolean state = false;
    int waitTime = 3000;   // 依據網路調整等候時間，3000代表，最多等3秒
    long startTime = millis();
    delay(1000);
    Serial.print("Get Response");
    while ((startTime + waitTime) > millis())    {
      Serial.print(".");
      delay(100);
      bool jobdone=false;
      while (client_tcp.available())
      {//當有收到回覆資料時
        jobdone=true;
        char c = client_tcp.read();
        if (c == '\n')
        {
          if (getResponse.length() == 0) state = true;
          getResponse = "";
        }
        else if (c != '\r')
          getResponse += String(c);
        if (state == true) Feedback += String(c);
        startTime = millis();
      }
      if (jobdone) break;
    }
    client_tcp.stop();
    esp_camera_fb_return(fb);//清除緩衝區
    return Feedback;
  }
  else {
    esp_camera_fb_return(fb);
    return "Send failed.";
  }

}

void setup() {
  Serial.begin(115200);
  //初始化相機結束
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
  config.jpeg_quality = 10;  //10-63 lower number means higher quality
  config.fb_count = 2;
  config.frame_size = FRAMESIZE_VGA;// FRAMESIZE_ + UXGA|SXGA|XGA|SVGA|VGA|CIF|QVGA|HQVGA|QQVGA
  //Line notify don't accept bigger than SVGA
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }
  //初始化相機結束，開始網路連線
  WiFi.mode(WIFI_STA);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  long int StartTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if ((StartTime + 10000) < millis()) break;
  }

  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reset");
    delay(1000);
    ESP.restart();//連線不成功，則重新開機
  }
  
  pinMode(trigPin, OUTPUT);        //Define inputs and outputs
  pinMode(echoPin, INPUT);
  pinMode(soundPin, OUTPUT);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long cm = pulseIn(echoPin, HIGH);   // 收到高電位時的時間
  cm = (cm / 2) / 29.1;       // 將時間換算成距離 cm 或 inch
  Serial.println(cm);
  
  if (cm <= 30) {
    digitalWrite(trigPin, HIGH); 
    Serial.println("starting to Line");

    digitalWrite(soundPin, HIGH);  // 觸發語音播放模組
    delayMicroseconds(10);
    digitalWrite(soundPin, LOW); 

    delay(100);

    String payload = sendImage2LineNotify("有人員異常侵入...");  // 觸發 Line 推播影像
    Serial.println(payload);
    delay(5000);
  }
  delay(100);  //You could only send up to 50 images to Line Notify in one hour.
}

```



