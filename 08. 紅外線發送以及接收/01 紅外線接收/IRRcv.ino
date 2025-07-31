//Install IRremote Version 4 or later

#include <IRremote.h>   // Ver 4 or later <-------<<<<<<<

#define DECODE_NEC

unsigned long irMillis;

//                                   s e t u p ( )
//******************************************************************************************
void setup()
{
  Serial.begin(9600);

  //**************************************
  const byte IR_RECEIVE_PIN = 7;

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

} //END of   setup()


//                                    l o o p ( )
//******************************************************************************************
void loop()
{
  //*******************************************************
  if (IrReceiver.decode())
  {
    IrReceiver.resume(); // Enable receiving of the next value
  }

  //*******************************************************
  //have we received a new IR code form the remote ?
  if (IrReceiver.decodedIRData.command != 0)
  {
    checkIRcode();
  }

} //END of   loop()


//                                c h e c k I R c o d e ( )
//******************************************************************************************
void checkIRcode()
{
  //RAW code
  Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);
 
  Serial.print("  ");   
  //command
  Serial.println(IrReceiver.decodedIRData.command);

  IrReceiver.printIRResultShort(&Serial); 

  switch (IrReceiver.decodedIRData.command)
  {

   case 1:
      {
        Serial.println("Press ====> 1");
      }
      break;
   case 2:
      {
        Serial.println("Press ====> 2");
      }
      break;
   case 3:
      {
        Serial.println("Press ====> 3");
      }
      break;

  }  //END of   switch...case


  //needed to block repeat codes
  IrReceiver.decodedIRData.command = 0;

} //END of   checkIRcode()