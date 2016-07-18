#include <math.h>

#include <Servo.h>
                
#define ThermistorPIN 0                 // Analog Pin 0
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int lightPin = 0; //analog pin--soil ldr //define a pin for Photo resistor
const int VAL_PROBE = 1; //Analog pin--soil sensor

int ledPin=9;  //ldr dig o/p
int piezoBuzzerPin = 8;     // Pin Piezo Buzzer is connected to
int pirSensorPin = 2; 
int pos = 0;    // variable to store the servo position
float vcc = 4.91;                       // only used for display purposes, if used
                                        // set to the measured Vcc.
float pad = 9850;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 10000;                   // thermistor nominal resistance

float Thermistor(int RawADC) {
  long Resistance;  
  float Temp;  // Dual-Purpose variable to save space.

  Resistance=pad*((1024.0 / RawADC) - 1);
  Temp = log(Resistance); // Saving the Log(resistance) so not to calculate  it 4 times later
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius                      

  // BEGIN- Remove these lines for the function not to display anything
  //Serial.print("ADC: ");
  //Serial.print(RawADC);
  //Serial.print("/1024");                           // Print out RAW ADC Number
  //Serial.print(", vcc: ");
  //Serial.print(vcc,2);
  //Serial.print(", pad: ");
  //Serial.print(pad/1000,3);
  //Serial.print(" Kohms, Volts: ");
  //Serial.print(((RawADC*vcc)/1024.0),3);  
  //Serial.print(", Resistance: ");
  //Serial.print(Resistance);
  //Serial.print(" ohms, ");
  // END- Remove these lines for the function not to display anything

  // Uncomment this line for the function to return Fahrenheit instead.
  //temp = (Temp * 9.0)/ 5.0 + 32.0;                  // Convert to Fahrenheit
  return Temp;                                      // Return the Temperature
}

void setup() {
  Serial.begin(115200);
  
   pinMode( ledPin, OUTPUT );//ldr led
     pinMode(pirSensorPin, INPUT);     // declare the PIR sensor as input
  pinMode(piezoBuzzerPin, OUTPUT);
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  delay(5000);
}

void loop() {
  float temp,hum,fah,dewpt;
  temp=Thermistor(analogRead(ThermistorPIN));  
  temp=temp+16.5;
  fah=temp*1.8+32;
  hum=temp+57; 
  dewpt=temp-((100-hum)/5));
       Serial.println("******************SOIL MOISTURE SENSOR**********************");

 int moisture = analogRead(VAL_PROBE);
     moisture=moisture/10;       
     Serial.println("analog value:" );
     Serial.println( moisture );
        
        if(moisture>90) {
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

Serial.println("Dry soil");

}

else
if((moisture>65)&&(moisture<90)) {

Serial.println("Humid soil");

}
else

if(moisture<65){

Serial.println("water");
}
 analogWrite(ledPin, analogRead(lightPin)/4);//ldr code
 delay(l0);//ldr delay
//nvert it to Celsius
Serial.println("Weather Readings");
  Serial.print("Celsius: ");
  Serial.print(temp,1);                             // display Celsius
                   // converts to  Fahrenheit
  Serial.print(", Fahrenheit: ");
  Serial.print(fah,1);
                    // display  Fahrenheit
   Serial.print(", Humidity: %");
  Serial.print(hum,1);
  Serial.print(", Dew Point in c :");
  Serial.print(dewpt,1);
  Serial.println("");    
  /*  Pir sensor code*/ 
  val = digitalRead(inputPin); // read input value
if (val == HIGH) { // check if the input is HIGH
digitalWrite(ledPin, HIGH); // turn LED ON
if (pirState == LOW) {
// we have just turned on
Serial.println("Motion detected!");
// We only want to print on the output change, not state
pirState = HIGH;
}
} else {
digitalWrite(ledPin, LOW); // turn LED OFF
if (pirState == HIGH){
// we have just turned of
Serial.println("Motion ended!");
// We only want to print on the output change, not state
pirState = LOW;
}
}                           
  delay(10000);                                      // Delay a bit...
}
