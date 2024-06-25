//File Name    : Elastic_Band_Twisting
//Author       : CaYPT Camp
//Description  : This Arduino code was developed for IYPT 2022 Problem 11 Balls on an Elastic Band. 
// It controls linear rails with a stepper motor mounted on the carriage.
// An elastic band is connected between the stepper motor and a load cell. The code controls the stretching
// and twisting of the rubber band and uses the load cell + HX711 ADC to read the tension force on the rubber band.

#include <HX711.h>

#define DOUT 12
#define CLK 13
#define END_STOP 11

HX711 scale;

// linear rail pins
const int stepPinBig = 3;
const int dirPinBig = 2;
//const int enPinBig = 4;

// twist motor pins
const int stepPinSmall = 9;
const int dirPinSmall = 8;
//const int enPinSmall = 10;

// load cell constants
const float calibration_factor = 1; // set calibration factor to 1 to avoid internal equations
const int num_values_to_wait = 20;
const int num_values_per_datum = 1;
const int num_values_to_average = 20;
float scale_readings[] = {0,0};
float tare_distance = 20;

// motion profiling
float zero_increment = 0.2;

// positioning variables
float current_position = 0;
float current_angle = 0.0;

// positioning scaling constants
const float steps_per_mm = 1301.42037; // verify via calibration
const float steps_per_radian = (float)6400 / ((float)2 * (float)PI);

// comms variables
String temp = "";

int count = 0;

void setup() {
  // set up all pin modes
  pinMode(stepPinBig,OUTPUT);
  pinMode(dirPinBig,OUTPUT);
  pinMode(stepPinSmall,OUTPUT);
  pinMode(dirPinSmall,OUTPUT);
  pinMode(END_STOP, INPUT_PULLUP);

  // set up comms with computer
  Serial.begin(38400);

  zero();
  Serial.println("Z"); // Zeroing complete
  
  // move to a fixed distance to tare scale
  move_steps(tare_distance*steps_per_mm);

  // initialize and tare scale
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  scale.set_scale(calibration_factor);

  // move back to zero position
  move_steps(-tare_distance*steps_per_mm);
  Serial.println("T");
  
//  while(1) {
//    update_scale_values(1, 1);
//    Serial.println(scale_readings[0],4);
////    Serial.print("\t");
////    Serial.println(scale_readings[1],4);
//  }
}

void loop() {

  // send command request to computer
  Serial.println("W");


  // wait for computer to send command
  // Get linear distance
  while (Serial.available() == 0) {}
  temp = Serial.readStringUntil(',');
  temp.trim();
  float extension = temp.toFloat();

  // Get twist
  while (Serial.available() == 0) {}
  temp = Serial.readStringUntil(',');
  temp.trim();
  float twist = temp.toFloat();

  // Get reading request
  while (Serial.available() == 0) {}
  temp = Serial.readStringUntil(',');
  temp.trim();
  int getReading = (int) temp.toFloat();

  // parse the command
  // move to correct length
  float position_change = extension - current_position; // in mm
  long steps_to_move = (float) position_change * steps_per_mm; // in steps
  move_steps(steps_to_move);
  current_position = current_position + (steps_to_move/steps_per_mm); // in mm
    
  // move to correct angle
  float angle_change = twist - (float)current_angle; // in radians
  long steps_to_rotate = (float) angle_change * (float)steps_per_radian; // in steps
  rotate_steps(steps_to_rotate);
  current_angle = (float)current_angle + ((float)steps_to_rotate/(float)steps_per_radian);


  // if a measurement is requested, take measurement and send back to computer
  if (getReading == 1) {
    update_scale_values(num_values_to_wait, num_values_to_average);
    Serial.print(scale_readings[0],4);
    Serial.print("\t");
    Serial.println(scale_readings[1],4);
  }
  else {
    Serial.println("NaN\tNaN");
  }
}

// moves linear rail until metal plates make contact
void zero() {
  while (digitalRead(END_STOP) == 1) {
    move_steps(-zero_increment*steps_per_mm);
  }
}

// move a certain number of steps
// if num_steps < 0, linear rail moves backward
void move_steps(long num_steps) {
  if (num_steps < 0) {
    digitalWrite(dirPinBig, HIGH);
    num_steps = -num_steps;
  }
  else {
    digitalWrite(dirPinBig, LOW);
  }

  for (long i = 0; i < num_steps; i++) {
    digitalWrite(stepPinBig,HIGH);
    delayMicroseconds(50);
    digitalWrite(stepPinBig, LOW);
    delayMicroseconds(50);
  }
}

// rotate twist motor a certain number of steps
// if num_steps < 0, rotates moves backward
void rotate_steps(int num_steps) {
  if (num_steps < 0) {
    digitalWrite(dirPinSmall, HIGH);
    num_steps = -num_steps;
  }
  else {
    digitalWrite(dirPinSmall, LOW);
  }

  for (long i = 0; i < num_steps; i++) {
    digitalWrite(stepPinSmall,HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPinSmall, LOW);
    delayMicroseconds(200);
  }
}

// average a certain number of values from the scale
// returns an array with the mean and standard deviation
void update_scale_values(int num_values_to_wait, int num_values_to_average) {
  float temp_scale_factor = 100000000.0;
  
  float sum = 0;
  float sum_of_squares = 0;
  int count = 0;
  float temp;

  for (int i = 0; i < num_values_to_wait; i++) {
    scale.get_units(num_values_per_datum);
  }
  for (int i = 0; i < num_values_to_average; i++) {
    temp = scale.get_units(num_values_per_datum);
    sum = sum + temp;
    sum_of_squares = sum_of_squares + (temp*temp/temp_scale_factor);
    count = count + 1;
  }

  float avg = sum/((float) count);
  scale_readings[0] = avg;
  scale_readings[1] = sum_of_squares/((float) count);
  scale_readings[1] = scale_readings[1]*temp_scale_factor;
}
