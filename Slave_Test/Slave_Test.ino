#include <TinyWireS.h>

byte own_adress = 10;
byte characters[5] = {'h', 'e', 'l', 'l', 'o'};
int idx = 0;

void setup() {
  // put your setup code here, to run once:
  TinyWireS.begin(own_adress);

  TinyWireS.onRequest(onI2CRequest);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void onI2CRequest() {
  
  TinyWireS.send(characters[idx]);
  idx = idx+1%5;
}
