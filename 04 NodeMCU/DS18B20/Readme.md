<h1>【練習題目 : NodeMCU DS18B20 溫度感測器】</h1>

## 準備材料 : 
>1. NodeMCU 板(CH340驅動程式.USB:MicroUSB)
>2. MicroUSB 連接線 X 1
>3. DS18B20 溫度感測器 X 1
>4. 4.7K電阻 X 1
>5. 杜邦線數條
>6. 麵包板 X 1
===

## NodeMCU 腳位圖 

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/Blink/nodemcu_pin.PNG?raw=true)

## DS18B20溫度偵測控制電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/DS18B20/DS18.png?raw=true)

## 相關函式 : 
#include <DallasTemperature.h>
>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/DS18B20/DallasTemperature.PNG?raw=true)

#include <OneWire.h>
>![](https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/DS18B20/OneWire.PNG?raw=true)


## 程式說明

[以下程式來源 DallasTemp.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/04%20NodeMCU/DS18B20/DallasTemp.ino "DallasTemp.ino"
[以下程式來源 DallasTemp.ino ]
``` arduino
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 4                          //D2 pin of nodemcu

OneWire oneWire(ONE_WIRE_BUS);
 
DallasTemperature sensors(&oneWire);            // Pass the oneWire reference to Dallas Temperature.

void setup(void)
{
  Serial.begin(9600); 
  sensors.begin();
}

void loop(void)
{
  sensors.requestTemperatures();                // Send the command to get temperatures  
  Serial.println("Temperature is: ");
  Serial.println(sensors.getTempCByIndex(0));   // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  delay(500);
}

```
