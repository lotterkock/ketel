#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  12;      // the number of the LED pin
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

double temp = 0;


int sensorPin = A0;    // select the input pin for the potentiometer
double sensorValue = 0;  // variable to store the value coming from the sensor
double sensorValue1 = 0;  // variable to store the value coming from the sensor
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // Start up the library
  sensors.begin();
}
 
 
void loop(void)
{
  
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  sensorValue1 = (sensorValue*100)/678;
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {   
    sensors.requestTemperatures(); // Send the command to get temperatures
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus 
    Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?
    Serial.println();
    
    while (sensors.getTempCByIndex(0) < sensorValue1) {    
      // turn LED on:    
      digitalWrite(ledPin, HIGH); 
      sensors.requestTemperatures(); // Send the command to get temperatures
    // call sensors.requestTemperatures() to issue a global temperature
    // request to all devices on the bus 
    Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"?
    Serial.println();
    }
    digitalWrite(ledPin, LOW); 
  } 

  
  
  Serial.print(sensorValue1);
  Serial.println();
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
 
}
