#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 10; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 9; // Connects to module's TX 
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
const int flexPin0 = A0;
const int flexPin1 = A1;
const int flexPin2 = A2;
const float VCC = 5;
// voltage at Ardunio 5V line

const float R_DIV = 47000.0;
// resistor used to create a voltage divider

const float flatResistance = 30000.0;

const float bendResistance = 163000.0; // resistance at 90 deg
// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
  pinMode(flexPin0, INPUT);
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);
    // Play the first MP3 file on the SD card
    //player.play(1);
    
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
}

void loop() {
int ADCflex0 = analogRead(flexPin0);

float Vflex0 = ADCflex0 * VCC / 1023.0;

float Rflex0 = R_DIV * (VCC / Vflex0 - 1.0);

Serial.println("Resistance: " + String(Rflex0) + " ohms"); // Use the calculated resistance to estimate the
//sensor's bend angle:

float angle0 = map(Rflex0, flatResistance, bendResistance, 0, 180.0);

Serial.println("Bend: " + String(angle0) + " degrees");

Serial.println(); delay(500);

if(angle0 > 80)
{
  player.play(1);
  player.play(1);
}  
int ADCflex1 = analogRead(flexPin1);

float Vflex1 = ADCflex1 * VCC / 1023.0;

float Rflex1 = R_DIV * (VCC / Vflex1 - 1.0);

Serial.println("Resistance: " + String(Rflex1) + " ohms"); // Use the calculated resistance to estimate the
//sensor's bend angle:

float angle1 = map(Rflex1, flatResistance, bendResistance, 0, 180.0);

Serial.println("Bend: " + String(angle1) + " degrees");

Serial.println(); delay(500);

if(angle1 > 80)
{
  player.play(2);
  player.play(2);
}  

//3 rd flex sensor
int ADCflex2 = analogRead(flexPin2);

float Vflex2 = ADCflex2 * VCC / 1023.0;

float Rflex2 = R_DIV * (VCC / Vflex2 - 1.0);

Serial.println("Resistance: " + String(Rflex2) + " ohms"); // Use the calculated resistance to estimate the
//sensor's bend angle:

float angle2 = map(Rflex2, flatResistance, bendResistance, 0, 180.0);

Serial.println("Bend: " + String(angle2) + " degrees");

Serial.println(); delay(500);

if(angle2 > 80)
{
  player.play(3);
  player.play(3);
}  
}
