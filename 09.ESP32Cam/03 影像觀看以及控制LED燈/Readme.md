### ESP32 Cam 觀看影像，並且在網頁上控制 LED 燈開啟以及關閉。<br>

### 電路圖 <br>

<img src="103.jpg" width=400 height=400 /><br>

### 接腳說明 <br>
使用腳位，如果不需要監看序列埠，可以省略 TX RX 腳位。 <br>

| USB TTL | ESP32 Cam |    LED   |
|---------|-----------|----------|
|  5V     |    5V     |          |
|  TX     |   UOR     |          |
|  RX     |   UOT     |          |
|  GND    |   GND     |   短腳   |
|         |   IO13    |   長腳   |



### Arduino 程式碼<br>
```
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid = "WIFI NAME";         // 請改為WIFI 熱點名稱
const char* password = "WIFI PASSWORD"; // 請改為WIFI 熱點密碼

// LED 控制腳位
#define LED_PIN 13

// AI Thinker ESP32-CAM
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

WiFiServer server(80);

// =========================
// HTML（加入開燈/關燈按鈕）
// =========================
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32-CAM</title>

<style>
html,body{
    margin:0;
    padding:0;
    width:100%;
    height:100%;
    background:black;
    text-align:center;
}

img{
    width:80vw;
    max-width:400px;
    height:auto;
    object-fit:contain;
    margin-top:10px;
}

button{
    width:120px;
    height:45px;
    margin:10px;
    font-size:16px;
    border-radius:8px;
    border:none;
    cursor:pointer;
}

#on{
    background:green;
    color:white;
}

#off{
    background:red;
    color:white;
}
</style>

</head>

<body>

<img id="cam">

<br>

<button id="on" onclick="ledOn()">開燈</button>
<button id="off" onclick="ledOff()">關燈</button>

<script>

let img = document.getElementById("cam");

function refreshImage()
{
    img.src = "/capture?t=" + new Date().getTime();
}

img.onload = function()
{
    setTimeout(refreshImage,100);
};

window.onload = function()
{
    refreshImage();
};

// ===== LED 控制 =====
function ledOn()
{
    fetch("/led?state=on");
}

function ledOff()
{
    fetch("/led?state=off");
}

</script>

</body>
</html>
)rawliteral";

// =========================
// Camera 初始化
// =========================
void startCamera()
{
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

    if(psramFound())
    {
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    }
    else
    {
        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);

    if(err != ESP_OK)
    {
        Serial.printf("Camera init failed: 0x%x\n", err);
        ESP.restart();
    }

    sensor_t *s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA);
}

// =========================
// JPEG 傳輸
// =========================
void sendJpg(WiFiClient &client)
{
    camera_fb_t *fb = esp_camera_fb_get();

    if(!fb)
    {
        client.println("HTTP/1.1 500");
        client.println();
        return;
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: image/jpeg");
    client.println("Content-Length: " + String(fb->len));
    client.println();

    client.write(fb->buf, fb->len);

    esp_camera_fb_return(fb);
}

// =========================
// HTML 頁面
// =========================
void sendPage(WiFiClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.print(index_html);
}

// =========================
// LED 控制 API
// =========================
void handleLed(String request)
{
    if(request.indexOf("state=on") >= 0)
    {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
    }
    else if(request.indexOf("state=off") >= 0)
    {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED OFF");
    }
}

// =========================
// setup
// =========================
void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    startCamera();

    WiFi.begin(ssid,password);

    Serial.print("Connecting");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.println(WiFi.localIP());

    server.begin();
}

// =========================
// loop
// =========================
void loop()
{
    WiFiClient client = server.available();

    if(!client)
        return;

    String request = client.readStringUntil('\r');

    // ===== LED 控制 =====
    if(request.indexOf("/led") >= 0)
    {
        handleLed(request);

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/plain");
        client.println();
        client.println("OK");

        client.stop();
        return;
    }

    // ===== 影像 =====
    if(request.indexOf("/capture") >= 0)
    {
        sendJpg(client);
    }
    else
    {
        sendPage(client);
    }

    delay(1);
    client.stop();
}
```
