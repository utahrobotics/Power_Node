#include <TinyWireS.h>

// --------------------------------------
// Slave
//    
// This sketch is for the ATTINY on-board a USR 2018-2019 Power Node. Upon request from a master device the ATTINY will take readings from the voltage divider
// and ASC758 current sensor and send a total of four bytes (two for each integer reading) to the master device.
//
// By: Alex Charters
// Last Updated: 2/23/2019 

#define I2C_SLAVE_ADDRESS 0x5 // Address of the slave
 
int i=0;
 
void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS); // join i2c network
    //TinyWireS.onReceive(receiveEvent); // not using this
    TinyWireS.onRequest(requestEvent);
 
    // Turn on LED when program starts
    pinMode(A2, INPUT); //current
    pinMode(A3, INPUT); //voltage
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
    //current
    int val=analogRead(A2);
    byte valLow = val & 0xff;
    byte valHigh = (val >> 8);

    //voltage
    int volt_val = analogRead(A3);
    
    byte voltLow = volt_val & 0xff;
    byte voltHigh = (volt_val >> 8);

    //sending
    TinyWireS.send(valHigh);
    TinyWireS.send(valLow);
    TinyWireS.send(voltHigh);
    TinyWireS.send(voltLow);
}
