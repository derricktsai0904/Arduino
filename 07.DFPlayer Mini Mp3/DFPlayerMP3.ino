#include <DFMiniMp3.h>  
//使用軟體Serial
#include <SoftwareSerial.h>  
SoftwareSerial mySerial(11,10); // RX, TX

const int sw = 3000;

// 宣告 notify class
//
class Mp3Notify; 

// 定義類型，其中第一個參數為決定用硬體Serial或軟體Serail
//
typedef DFMiniMp3<SoftwareSerial, Mp3Notify> DfMp3;  //如果用UNO板就用軟體Serail
//typedef DFMiniMp3<HardwareSerial, Mp3Notify> DfMp3;  //如果用Mega板就用硬體Serail

// 建立mp3物件
//
DfMp3 dfmp3(mySerial);

// 實作notification的類別，可以在不同的事件中，寫入想要進行的動作
// 若沒有特別要進行的處理，這裡不用修改
class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
    if (source & DfMp3_PlaySources_Sd) 
    {
        Serial.print("SD Card, ");
    }
    if (source & DfMp3_PlaySources_Usb) 
    {
        Serial.print("USB Disk, ");
    }
    if (source & DfMp3_PlaySources_Flash) 
    {
        Serial.print("Flash, ");
    }
    Serial.println(action);
  }
  static void OnError([[maybe_unused]] DfMp3& mp3, uint16_t errorCode)
  {
    // 錯誤訊息
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished([[maybe_unused]] DfMp3& mp3, [[maybe_unused]] DfMp3_PlaySources source, uint16_t track)
  {
    Serial.print("Play finished for #");
    Serial.println(track);  
  }
  static void OnPlaySourceOnline([[maybe_unused]] DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted([[maybe_unused]] DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved([[maybe_unused]] DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};

void setup() 
{
  Serial.begin(9600); //啟用監控視窗
  Serial.println("initializing...");
  
  dfmp3.begin();  //開始使用DFPlayer模組

  //重置DFPlayer模組，會聽到"波"一聲
  dfmp3.reset();

  //音量控制，0~30
  //uint16_t volume = dfmp3.getVolume();
  //Serial.print("volume ");
  //Serial.println(volume);
  dfmp3.setVolume(28);
  
  //volume = dfmp3.getVolume();
  //Serial.print("volume ");
  //Serial.println(volume);
  
  //取得所有MP3檔的總數
  //uint16_t count = dfmp3.getTotalTrackCount(DfMp3_PlaySource_Sd);
  //Serial.print("files ");
  //Serial.println(count);

  Serial.println("Play Mp3...");

  // 播放MP3，參數就是第N首。如要播第一首MP3，參數就是1，第二首就是2

  dfmp3.playMp3FolderTrack(1);
  delay(sw);
  dfmp3.playMp3FolderTrack(2);
  delay(sw);
  dfmp3.playMp3FolderTrack(3);
  delay(sw);
  dfmp3.playMp3FolderTrack(4);
  delay(sw);
  //dfmp3.playMp3FolderTrack(1);
  //delay(10);
  //dfmp3.playMp3FolderTrack(2);  
  //delay(10);
  //dfmp3.playMp3FolderTrack(3);  
 // dfmp3.playMp3FolderTrack(4);  
}

void waitMilliseconds(uint16_t msWait)
{
  uint32_t start = millis();
  
  while ((millis() - start) < msWait)
  {
    // if you have loops with delays, its important to 
    // call dfmp3.loop() periodically so it allows for notifications 
    // to be handled without interrupts
    dfmp3.loop(); 
    delay(1);
  }
}

void loop() 
{ 
  dfmp3.playMp3FolderTrack(1);
  delay(sw);
  dfmp3.playMp3FolderTrack(2);
  delay(sw);
  dfmp3.playMp3FolderTrack(3);
  delay(sw);
  dfmp3.playMp3FolderTrack(4);
  delay(sw);
}