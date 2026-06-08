### 使用USB TTL 接上 ESP32 Cam ，就可以直接觀看，燒錄方式請參閱 09.ESP32Cam 說明。<br><br>


### 使用腳位，如果不需要監看序列埠，可以省略 TX RX 腳位。
| USB TTL | ESP32 Cam |
|---------|-----------|
|  5V     |    5V     |
|  TX     |   UOR     |
|  RX     |   UOT     |
|  GND    |   GND     |


### Arduino 程式碼 <br>

```
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const char* ssid = "WIFI NAME"; // 請改為您的 WIFI 熱點名稱
const char* password = "WIFI PASSWORD";   // 請改為您的 WIFI 熱點a密碼

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
}

img{
    width:25vw;        // 調整影像寬度
    height:25vh;       // 整整影像高度
    object-fit:contain;
}
</style>

</head>

<body>
<center>
<img id="cam">
</center>

<script>

let img = document.getElementById("cam");

function refreshImage()
{
    img.src = "/capture?t=" + new Date().getTime();
}

img.onload = function()
{
    setTimeout(refreshImage,50);
};

window.onload = function()
{
    refreshImage();
};

</script>

</body>
</html>
)rawliteral";

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

void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    Serial.begin(115200);

    startCamera();

    WiFi.begin(ssid,password);

    Serial.println();
    Serial.print("Connecting");

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi Connected");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void sendJpg(WiFiClient &client)
{
    camera_fb_t *fb = esp_camera_fb_get();

    if(!fb)
    {
        client.println("HTTP/1.1 500 Internal Server Error");
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

void sendPage(WiFiClient &client)
{
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();

    client.print(index_html);
}

void loop()
{
    WiFiClient client = server.available();

    if(!client)
        return;

    String request = client.readStringUntil('\r');

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

