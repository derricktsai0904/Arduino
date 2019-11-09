void setup(){
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(12, OUTPUT);
}

void loop(){
  int switchStatus = digitalRead(2);
  digitalWrite(12, switchStatus);
  Serial.println(switchStatus);
}
