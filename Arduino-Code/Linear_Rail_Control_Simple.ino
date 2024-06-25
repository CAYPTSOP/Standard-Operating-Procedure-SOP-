//File Name    : Linear_Rail_Control_Simple
//Author       : CaYPT Camp
//Description  : This Arduino code was developed for IYPT 2023 Problem 7 Faraday Waves to measure liquid-air surface tension. 
// It controls linear rails (a stepper motor). It takes a user input from serial and moves a linear rail by a set distance.

const int stepPin = 12; 
const int dirPin = 11; 
const int enPin = 10;

void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW); 
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()==0){}
    int c = Serial.parseInt();
  if (c>=0) digitalWrite(dirPin,LOW);
  else digitalWrite(dirPin, HIGH);
  for(long x = 0; x < abs(c)*160; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(100);
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(100); 
  }
  delay(20);
}
