#include <IRremote.h> // Include the IRremote library

#define IR_SEND_PIN 3 // Define the digital pin connected to the IR LED

void setup() {
  IrSender.begin(IR_SEND_PIN); // Initialize the IR sender
}

void loop() {
  // Send an NEC signal with address 0x0102 and command 0x34
  IrSender.sendNEC(0xDB34, 0x1, true); 
  // Parameters: address, command, enable repeat (true/false), number of repeats (if enabled)

  delay(1000); // Wait for one second before sending again
}