//File Name    : ADS1x15_ADC_BA1032_Hall
//Author       : CaYPT Camp
//Description  : This Arduino code was developed for IYPT 2023 Problem 11 Ball on Ferrite Rod.
// It reads the voltage output of a BA1032 linear ratiometric hall sensor using a high-precision 
// ADS1x15 ADC (up to 16 bits) and converts the voltage value into magnetic field value.

include "ADS1X15.h"


// choose your sensor
// ADS1013 ADS(0x48);
// ADS1014 ADS(0x48);
// ADS1015 ADS(0x48);
// ADS1113 ADS(0x48);
// ADS1114 ADS(0x48);

ADS1115 ADS(0x48);


void setup() 
{
  Serial.begin(115200);
  ADS.begin();
  ADS.setGain(0);      // 6.144 volt
  ADS.setDataRate(7);  // fast
  ADS.setMode(0);      // continuous mode
}


void loop() 
{
  int16_t raw = ADS.readADC(0);
  float voltage = ADS.toVoltage(raw);
  Serial.println(BA1032(voltage));
  delay(50);
}

float BA1032 (float voltage){
  float B = ((voltage-2.5)*1000/1.34)/10;
  return B;
}
