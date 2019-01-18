#include <Wire.h>

byte byteArray[2];
int mVperAmp = 10;
int ACSoffset = 2500;
 
void setup()
{
 Wire.begin(); // join i2c bus (address optional for master)
 Serial.begin(9600); // start serial for output
}
 
void loop()
{
  Wire.requestFrom(5, 4); // request 1 byte from slave device address 4

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
      Serial.print("\t mV = "); // shows the voltage measured 
      Serial.print(currentMv, 3); // the '3' after voltage allows you to display 3 digits after decimal point
      Serial.print("\t Amps = "); // shows the voltage measured 
      Serial.println(Amps, 3); // the '3' after voltage allows you to display 3 digits after decimal point

      Serial.print("Raw Value = " ); // shows pre-scaled value 
      Serial.print(rawVoltT);
      Serial.print("\t Volts = "); // shows the voltage measured
      Serial.println(voltage, 3); // the '3' after voltage allows you to display 3 digits after decimal point
  }
 
  delay(500);
}
