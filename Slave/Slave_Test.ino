#include <TinyWireS.h>


#define I2C_SLAVE_ADDRESS 0x4 // Address of the slave
 
int i=0;
 
void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS); // join i2c network
    //TinyWireS.onReceive(receiveEvent); // not using this
    TinyWireS.onRequest(requestEvent);
 
    // Turn on LED when program starts
    pinMode(A3, INPUT);
    digitalWrite(1, HIGH);
}
 
void loop()
{
    // This needs to be here
    TinyWireS_stop_check();
}
 
// Gets called when the ATtiny receives an i2c request
void requestEvent()
{
    int val=analogRead(A3);
    byte valLow = val & 0xff;
    byte valHigh = (val >> 8);
    TinyWireS.send(valHigh);
    TinyWireS.send(valLow);
}
