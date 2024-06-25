//File Name    : Triple_Load_Cell
//Author       : CaYPT Camp
//Description  : This Arduino code was developed for IYPT 2022 Problem 4 Unsinkable Disk
// It reads the force signal from 3 load cells each connected to a HX711 ADC.

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

//pins:
const int HX711_dout_1 = 9; //mcu > HX711 no 1 dout pin
const int HX711_sck_1 = 10; //mcu > HX711 no 1 sck pin
const int HX711_dout_2 = 6; //mcu > HX711 no 2 dout pin
const int HX711_sck_2 = 7; //mcu > HX711 no 2 sck pin
const int HX711_sck_3 = 4; //mcu > HX711 no 2 sck pin
const int HX711_dout_3 = 5; //mcu > HX711 no 2 dout pin
int num_values_per_datum = 1000; 

HX711_ADC LoadCell_1(HX711_dout_1, HX711_sck_1); //HX711 1
HX711_ADC LoadCell_2(HX711_dout_2, HX711_sck_2); //HX711 2
HX711_ADC LoadCell_3(HX711_dout_3, HX711_sck_3); //HX711 3
`

void setup() {
  Serial.begin(57600);
  delay(10);
  float calibration_value = 1;

  pinMode(8, OUTPUT);
  digitalWrite(8,HIGH);

    pinMode(3, OUTPUT);
  digitalWrite(3,HIGH);
  

  LoadCell_1.begin();
  LoadCell_2.begin();
  LoadCell_3.begin();

  unsigned long stabilizingtime = 3000; // tare preciscion can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  byte loadcell_1_rdy = 0;
  byte loadcell_2_rdy = 0;
  byte loadcell_3_rdy = 0;

   while ((loadcell_1_rdy + loadcell_2_rdy + loadcell_3_rdy) < 3) { //run startup, stabilization and tare, both modules simultaniously
    if (!loadcell_1_rdy) loadcell_1_rdy = LoadCell_1.startMultiple(stabilizingtime, _tare);
    if (!loadcell_2_rdy) loadcell_2_rdy = LoadCell_2.startMultiple(stabilizingtime, _tare);
    if (!loadcell_3_rdy) loadcell_3_rdy = LoadCell_3.startMultiple(stabilizingtime, _tare);
  }

  LoadCell_1.setCalFactor(calibration_value); // user set calibration value (float)
  LoadCell_2.setCalFactor(calibration_value); // user set calibration value (float)
  LoadCell_3.setCalFactor(calibration_value); // user set calibration value (float)
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell_1.update()) newDataReady = true;
  LoadCell_2.update();  
  LoadCell_3.update();
  
  //get smoothed value from data set
     float a = LoadCell_1.getData();
     float b = LoadCell_2.getData();
     float c = LoadCell_3.getData();

      Serial.print('\t');
      Serial.print(a);
      Serial.print('\t');
      Serial.print(b);
      Serial.print('\t');
      Serial.print(c);
      Serial.print('\t');
      Serial.println();
      delay(20);
    }
