#include <Wire.h>

// --------------------------------------
// Master_200B
//    
// This sketch is to be used with the 2018-2019 USR Power Nodes (50 Amp Uni-directional version) as a master for the communicating with the Nodes.
// The protocol the nodes use is to respond with four bytes when a request is made, the first two bytes are an integer value representing the raw ADC
// read from the ATTINY on the node of the voltage value. The next two bytes represent the raw value read from the ATTINY of the current sensor on the node.
// 
// Refer to the below table for value to use for the mVperAmp and ACSoffset variable for the different versions of the power nodes.
//
// Range   Direction Scale Factor          Offset
// 50 Amp  Uni-directional 60 mV per Amp   600 mVolts
// 50 Amp  Bi-directional  40 mV per Amp   2500 mVolts
// 100 Amp Uni-directional 40 mV per Amp   600 mVolts
// 100 Amp Bi-directional  20 mV per Amp   2500 mVolts
// 150 Amp Uni-directional 26.7 mV per Amp 600 mVolts
// 150 Amp Bi-directional  13.3 mV per Amp 2500 mVolts
// 200 Amp Uni-directional 20 mV per Amp   600 mVolts
// 200 Amp Bi-directional  10 mV per Amp   2500 mVolts
//
// This code only requests from one address, it will need to be only slightly modified to accomadate multiple address requests.

int mVperAmp = 60;
int ACSoffset = 600;
 
void setup()
{
 Wire.begin(); // join i2c bus (address optional for master)
 Serial.begin(9600); // start serial for output
}
 
void loop()
{
  Wire.requestFrom(4, 4); // request 4 byte from slave device address 4

  int byteNum = 0;
  while(Wire.available()) // slave may send less than requested
  {
      byte rawH = Wire.read();
      byte rawL = Wire.read();

      byte rawVoltH = Wire.read();
      byte rawVoltL = Wire.read();
 
      int rawT = rawH << 8 | rawL;
      int rawVoltT = rawVoltH << 8 | rawVoltL;
    
      double currentMv = (rawT / 1023.0) * 5000; // Gets you mV
      double Amps = ((currentMv - ACSoffset) / mVperAmp);

      float voltage = (rawVoltT * (5.0 / 1023.0))*5;
 
      Serial.print("Raw Value = " ); // shows pre-scaled value 
      Serial.print(rawT); 
      //Serial.print("\t mV = "); // shows the voltage measured 
      //Serial.print(currentMv, 3); // the '3' after voltage allows you to display 3 digits after decimal point
      Serial.print("\t Amps = "); // shows the voltage measured 
      Serial.println(Amps, 3); // the '3' after voltage allows you to display 3 digits after decimal point

      Serial.print("Raw Value = " ); // shows pre-scaled value 
      Serial.print(rawVoltT);
      Serial.print("\t Volts = "); // shows the voltage measured
      Serial.println(voltage, 3); // the '3' after voltage allows you to display 3 digits after decimal point

      Serial.println();
      Serial.println();
      Serial.println();
  }
 
  delay(1000);
}
