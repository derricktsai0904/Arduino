#include "BluetoothSerial.h"
#include "esp_bt_device.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

int cmd=0;

BluetoothSerial SerialBT;

void printDeviceAddress() {
 
  const uint8_t* point = esp_bt_dev_get_address();
 
  for (int i = 0; i < 6; i++) {
 
    char str[3];
 
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
 
    if (i < 5){
      Serial.print(":");
    }
 
  }
}

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
 
  if (event == ESP_SPP_SRV_OPEN_EVT) {
 
    Serial.println("Client Connected has address:");
 
    for (int i = 0; i < 6; i++) {
 
      Serial.printf("%02X", param->srv_open.rem_bda[i]);
 
      if (i < 5) {
        Serial.print(":");
      }
 
    }
  }
}

void setup() {
  Serial.begin(115200);
  SerialBT.register_callback(callback);

  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  Serial.print("BT MAC: ");
  printDeviceAddress();

  pinMode(33, OUTPUT);
  digitalWrite(33,HIGH);
}

void loop() {
  if (Serial.available()) {
    Serial.println(" ");
    Serial.print("Serial=>");
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.println(" ");
    Serial.print("SerialBT=>");

    cmd = SerialBT.read();
    Serial.write(cmd);
  }

  if(cmd=='2'){
     digitalWrite(33,LOW);
  }
  else if(cmd=='4'){
    for(int i=0;i<3;i++){
      digitalWrite(33,HIGH);
      delay(100);
      digitalWrite(33,LOW);
      delay(100);
    }
  }
  else
    digitalWrite(33,HIGH);

  
  delay(20);
}
