//File Name    : Micro_Servo
//Author       : CaYPT Camp
//Description  : This Arduino code was developed for IYPT 2022 Problem 2. Rayleigh Disk
// It controls the motion of microservo driven by Arduino pins directly.

#include <Servo.h>
Servo servo;
int adcReading;
float angle;


void setup() {
  servo.attach(8);
  servo.write(0);
  Serial.begin(9600);
  Serial.println("running");

}

void loop() {
  adcReading = analogRead(A0);
  angle = (220./1023.)*adcReading;
                          
  servo.write(angle);           
  delay(10);       
  Serial.println(angle);
  

}
