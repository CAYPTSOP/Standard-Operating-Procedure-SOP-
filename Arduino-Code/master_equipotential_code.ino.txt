// constants
int x_pull = 5;
int x_dir = 6;
int y_pull = 2;
int y_dir = 3;
int z_pull = 9;
int z_dir = 10;

long motor_delay_x = 50;
long motor_delay_y = 50;
long motor_delay_z = 50;

// positioning variables
float current_x = 0;
float current_y = 0;
float current_z = 0;

// calibration constants
float x_steps_per_mm = 1;
float y_steps_per_mm = 1;
float z_steps_per_mm = 1;

// input variable
String temp = "";

void setup() {
  // set up pin modes
  pinMode(x_pull, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_pull, OUTPUT);
  pinMode(y_dir, OUTPUT);
  pinMode(z_pull, OUTPUT);
  pinMode(z_dir, OUTPUT);
  
  // set up comms
  Serial.begin(38400);
}

void loop() {
  // send wait command
  Serial.println("W");

  // parse input
  while (Serial.available() == 0) {}
  temp = Serial.readStringUntil(',');
  temp.trim();
  float desired_x = temp.toFloat();

  while (Serial.available() == 0) {}
  temp = Serial.readStringUntil(',');
  temp.trim();
  float desired_y = temp.toFloat();

  while (Serial.available() == 0) {};
  temp = Serial.readStringUntil(',');
  temp.trim();
  float desired_z = temp.toFloat();

  // process x movement
  move_x(desired_x);

  // process y movement
  move_y(desired_y);

  // process z movement
  move_z(desired_z);
}

// move x
void move_x(float desired_x) {
  float dist = desired_x - current_x;
  int num_steps = round(dist*x_steps_per_mm);
  if (num_steps < 0) {
    digitalWrite(x_dir, HIGH);
    num_steps = -num_steps;
  }
  else {
    digitalWrite(x_dir, LOW);
  }

  for (long i = 0; i < num_steps; i++) {
    digitalWrite(x_pull,HIGH);
    delayMicroseconds(motor_delay_x);
    digitalWrite(x_pull, LOW);
    delayMicroseconds(motor_delay_x);
  }
}

// move y
void move_y(float desired_y) {
  float dist = desired_y - current_y;
  int num_steps = round(dist*y_steps_per_mm);
  if (num_steps < 0) {
    digitalWrite(y_dir, HIGH);
    num_steps = -num_steps;
  }
  else {
    digitalWrite(y_dir, LOW);
  }

  for (long i = 0; i < num_steps; i++) {
    digitalWrite(y_pull,HIGH);
    delayMicroseconds(motor_delay_y);
    digitalWrite(y_pull, LOW);
    delayMicroseconds(motor_delay_y);
  }
}

// move z
void move_z(float desired_z) {
  float dist = desired_z - current_z;
  int num_steps = round(dist*z_steps_per_mm);
  if (num_steps < 0) {
    digitalWrite(z_dir, HIGH);
    num_steps = -num_steps;
  }
  else {
    digitalWrite(z_dir, LOW);
  }

  for (long i = 0; i < num_steps; i++) {
    digitalWrite(z_pull,HIGH);
    delayMicroseconds(motor_delay_z);
    digitalWrite(z_pull, LOW);
    delayMicroseconds(motor_delay_z);
  }
}
