#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <dht.h>
#include <TridentTD_LineNotify.h>

#define dht_dpin 5 //定義訊號要從Pin 2 進來  
dht DHT;  

float humidity, temp_f;   // 從 DHT-11 讀取的值

// 修改成上述寄到登入郵箱的 Token號碼
//#define LINE_TOKEN "nQBxLWUcNhGK5rfW1SbvYTgdANJqMX0V255XLyHA1Q4"
#define LINE_TOKEN "T71LTd9xIrXTMFuZ75mE4WUxuwEIFgkOtkpjm481JiB"  // 可修改 Token 號碼

// 設定無線基地台SSID跟密碼
const char* ssid     = "DerrickSamsung";   // 修改手機熱點名稱
const char* password = "16099725";         // 修改WIFI連線密碼

unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor

// 用不到以下兩個變數
// const char* host = "notify-api.line.me";
// const int httpsPort = 443;
 
void setup(void)
{
  Serial.begin(9600);  // 設定速率 感測器
  //dht.begin();           // 初始化

  WiFi.mode(WIFI_STA);
  // 連接無線基地台
  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rWorking to connect");

  // 等待連線，並從 Console顯示 IP
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop(void)
{
  // 量測間等待至少 2 秒
  unsigned long currentMillis = millis();
  
  DHT.read11(dht_dpin);
 
  if(currentMillis - previousMillis >= interval) {
    // 將最後讀取感測值的時間紀錄下來 
    previousMillis = currentMillis;   

    // 讀取溫度大約 250 微秒!

    humidity = DHT.humidity;
    temp_f = (DHT.temperature * 9 / 5)+32 ;
    
    //humidity = dht.readHumidity();          // 讀取濕度(百分比)
    //temp_f = dht.readTemperature(true);     // 讀取溫度(華氏)
    
 
    // 檢查兩個值是否為空值
    if (isnan(humidity) || isnan(temp_f)) {
       Serial.println("Failed to read from DHT sensor!");
       return;
    }
  }

  String tempe="溫度:"+String((int)(temp_f-32)*5/9)+"℃";   
  String humid="濕度:"+String((int)humidity)+"％";

  // 顯示 Line版本
  Serial.println(LINE.getVersion());
 
  LINE.setToken(LINE_TOKEN);

  // 先換行再顯示
  LINE.notify("\n" + tempe + " ；" + humid);
  /*
  LINE.notify("\n 這是第一次測試 \n http://tw.yahoo.com  \n https://www.csccss.com.tw");
  //LINE.notify(2342); 
  //LINE.notify(212.43434,5); 
  LINE.notifySticker(3,240); 
  //LINE.notifyPicture("https://www.csccss.com.tw/images/logo.png");
  */
  // 每2分鐘發送一次
  delay(120000);
}
