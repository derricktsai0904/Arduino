<h1>【練習題目 : 額溫測量電路】</h1>
## 準備材料 : 
>1. Arduino Nano 板(CH340驅動程式.USB:MicroUSB) <br>
>2. MicroUSB 連接線 X 1 <br>
>3. MLX90614 X 1 <br>
>4. 杜邦線數條 <br>
>5. 麵包板 X 1 <br>
>6. 10K(棕黑橙)電阻 X 2 <br>

匯入程式庫

[以下程式庫來源 Adafruit-MLX90614-Library-master.zip ]:https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/D.MLX90614%E9%A1%8D%E6%BA%AB%E6%84%9F%E6%B8%AC%E5%99%A8/Adafruit-MLX90614-Library-master.zip "Adafruit-MLX90614-Library-master.zip"
[以下程式庫來源 Adafruit-MLX90614-Library-master.zip ]

===

## 額溫測量電路圖

>![](https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/D.MLX90614%E9%A1%8D%E6%BA%AB%E6%84%9F%E6%B8%AC%E5%99%A8/%E6%8E%A5%E7%B7%9A%E5%9C%96.jpg?raw=true)

[以下程式來源 MLX90614.ino ]:https://github.com/derricktsai0904/Arduino/blob/master/02%20Arduino%20%E5%9F%BA%E6%9C%AC%E6%84%9F%E6%B8%AC%E5%99%A8%E5%AF%A6%E4%BD%9C%E7%AF%84%E4%BE%8B/D.MLX90614%E9%A1%8D%E6%BA%AB%E6%84%9F%E6%B8%AC%E5%99%A8/MLX90614.ino "MLX90614.ino"
[以下程式來源 MLX90614.ino ]
``` arduino
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test");  

  mlx.begin();  
}

void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");

  Serial.println();
  delay(500);
}
```
