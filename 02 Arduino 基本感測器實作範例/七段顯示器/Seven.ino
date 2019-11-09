int i;
int j;

// 設定一個 matrix，B0111111 最前面的 B 代表資料型態為 byte
// 後面跟的 0111111 則是上面對照表的 gfedcba 
const byte num[10]={
    B0111111,  //0
    B0000110,  //1
    B1011011,  //2
    B1001111,  //3
    B1100110,  //4
    B1101101,  //5
    B1111101,  //6
    B0000111,  //7    
    B1111111,  //8
    B1101111   //9    
};

// 設定顯示器各段對應的 pin
const int seg[]={2,3,4,5,6,7,8};  //ABCDEFG

// 設定各段 pin 為 output
void setup() 
{ 
  for(i=0;i<7;i++)
    pinMode(seg[i],OUTPUT);
}
void loop() 
{
  for(i=0;i<10;i++)
  {
    for(j=0;j<7;j++)
    {
  // 讀取 0~9 matrix 裡的數字，ex: B0111111 的第0~6個位元
  // 並由對應的 pin 腳輸出高電壓，使 7 段 LED 發出對應的明亮
      if(bitRead(num[i],j))
        digitalWrite(seg[j],HIGH);
      else
        digitalWrite(seg[j],LOW);        
    }
  delay(1000);    
  } 
}
