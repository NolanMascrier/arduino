/*
  APDS-9960 - Proximity Sensor

  This example reads proximity data from the on-board APDS-9960 sensor of the
  Nano 33 BLE Sense and prints the proximity value to the Serial Monitor
  every 100 ms.

  The circuit:
  - Arduino Nano 33 BLE Sense

  This example code is in the public domain.
*/

#include <Arduino_APDS9960.h>
#include <ArduinoBLE.h>

#define R 2
#define O 3
#define V 4

#define STATUS_SAFE 0
#define STATUS_CLOSE 1
#define STATUS_DANGER 2

#define DISTANCE_DANGER 40
#define DISTANCE_SAFE 120 

int status = STATUS_SAFE;

int ledState = LOW;

unsigned long previousMillis = 0;

const long intervalLong = 750;
const long intervalMedLo = 250;
const long intervalMed = 150;
const long intervalMedSho = 80;
const long intervalShort = 20;

const int trigger = 12;
const int echo = 11;

long duration = 0;
int distance = 0;

BLEService ledService("180A");
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
    while (1);
  }
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy failed!");
    while (1);
  }

  BLE.setLocalName("Nano 33 BLE Sense");
  BLE.setAdvertisedService(ledService);
  ledService.addCharacteristic(switchCharacteristic);
  BLE.addService(ledService);
  switchCharacteristic.writeValue(0);
  BLE.advertise();

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  //LEDs
  pinMode(R, OUTPUT);
  pinMode(O, OUTPUT);
  pinMode(V, OUTPUT);
  analogWrite(R, 0);
  analogWrite(O, 0);
  analogWrite(V, 0);
}


/**
 * Update the status of processor according to the
 * read distance.
 *
 * @arg distance : read distance from the sensor.
*/
void update_status(int distance)
{
  if (distance <= DISTANCE_DANGER && status != STATUS_DANGER)
  {
      status = STATUS_DANGER;
      Serial.print("DANGER ! Obstacle found at distance ");
      Serial.print(distance);
      Serial.println("cm");

      analogWrite(R, 255);
      analogWrite(O, 0);
      analogWrite(V, 0);
  }
  else if (distance > DISTANCE_DANGER &&
      distance <= DISTANCE_SAFE && status != STATUS_CLOSE)
  {
      status = STATUS_CLOSE;
      Serial.print("WARNING ! Obstacle closing on at distance ");
      Serial.print(distance);
      Serial.println("cm");

      analogWrite(R, 0);
      analogWrite(O, 255);
      analogWrite(V, 0);
  }
  else if (distance > DISTANCE_SAFE && status != STATUS_SAFE)
  {
      status = STATUS_SAFE;
      Serial.println("All is good :)");

      analogWrite(R, 0);
      analogWrite(O, 0);
      analogWrite(V, 255);
  }
}

/**
 * Reads the data from the sensor and calculates the distance.
 * 
 * @return calculated distance.
*/
int read_sensor()
{
  int dist;
  long dur;

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  return (dist);
}

void loop() {
  BLEDevice central = BLE.central();
  unsigned long currentMillis = millis();
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  update_status(distance);

  // wait a bit before reading again
  delay(350);
}
