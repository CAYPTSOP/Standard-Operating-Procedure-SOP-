//File Name    : IR_Breakbeam_RPM
//Author       : CaYPT Camp
//Description  : This Arduino code uses IR break beam sensors (eg. https://www.adafruit.com/product/2168)
// to measure the angular velocity of a optical chopper with a user-defined number of holes. 
// It also uses PWM to drive an H-bridge (eg. L298N) to achieve speed control of a brushed DC motor.
// Note this code does not perform any active feedback control of the motor speed.

//BTS7960 motor driver sketch 
/*
 IR Breakbeam sensor demo!
*/

#define LEDPIN 13
#define SENSORPIN 10
// variables will change:
int sensorState = 0, lastState=0; // variable for reading the pushbutton status
int count = 0;
int NUM_HOLES_PER_ROTATION = 20;
int NUM_HOLES_TO_AVG = 20;
double angle = 2*PI*NUM_HOLES_TO_AVG/NUM_HOLES_PER_ROTATION;
double angVel = 0;
double lastTime = 0;
double cTime = 0;
double timeElapsed = 0;
int R_IS = 6;
int R_EN = 2;
int R_PWM = 3;
int L_IS = 7;
int L_EN = 4;
int L_PWM = 5;
int LED = 13;
void setup() {
  // put your setup code here, to run once:
 pinMode(R_IS, OUTPUT);
 pinMode(R_EN, OUTPUT);
 pinMode(R_PWM, OUTPUT);
 pinMode(L_IS, OUTPUT);
 pinMode(L_EN, OUTPUT);
 pinMode(L_PWM, OUTPUT);
 digitalWrite(R_IS, LOW);
 digitalWrite(L_IS, LOW);
 digitalWrite(R_EN, HIGH);
 digitalWrite(L_EN, HIGH);
 // initialize the LED pin as an output:
 pinMode(LEDPIN, OUTPUT);
 // initialize the sensor pin as an input:
 pinMode(SENSORPIN, INPUT);
 digitalWrite(SENSORPIN, HIGH); // turn on the pullup

 Serial.begin(9600);
}

void loop() {
  
  for (int i = 0; i<=5; i++){
    analogWrite(LED, 150);
    delay(1000);
    analogWrite(LED, 0);
    delay(1000);  
  }
  int maxSpeed = 50;
  int sampleTime = 100;
  long runTime = 100000;
  
  for(int i = 0; i <= maxSpeed; i= i+5){ //speed up
   analogWrite(R_PWM, i);
   analogWrite(L_PWM, 0);
   
   if (i>50){
    readSpeed();
   }
   delay(200);
  }

  
  for(int i =  0 ; i<= runTime; i=i+sampleTime){
    readSpeed();
    delay(sampleTime);
    }

  
  for(int i =  0 ; i<= runTime; i=i+sampleTime){
    readSpeed();
    delay(sampleTime);
    }
}

void readSpeed (){
  lastTime = micros();
  while (count< NUM_HOLES_TO_AVG){
     sensorState = digitalRead(SENSORPIN);
     //Serial.println(sensorState);
     //Serial.println(lastState);
     if (!sensorState && lastState) {
      count = count + 1;
     }
     lastState = sensorState;
  }
    
   if (count == NUM_HOLES_TO_AVG) {
    cTime = micros();
    timeElapsed = (cTime - lastTime)/1000000.0;
    angVel = angle/timeElapsed;
    Serial.println(angVel);
    }
  count = 0;
 }
