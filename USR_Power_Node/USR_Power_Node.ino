const int analogIn = A0;

// Set your scale factor
int mVperAmp = 10; // See Scale Factors Below

/* Scale Factors
200A bi-directional = 10 mV/Amp
*/

// Set you Offset
int ACSoffset = 2500; // See offsets below

int RawValue= 0;
double Voltage = 0;
double Amps = 0;

void setup(){ 
 Serial.begin(9600);
}

void loop(){
 
 RawValue = analogRead(analogIn);

 
}
