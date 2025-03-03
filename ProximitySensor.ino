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

#define R 2
#define O 3
#define V 4

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

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  // set the LEDs pins as outputs
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  // turn all the LEDs off
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  //LEDs
  pinMode(R, OUTPUT);
  pinMode(O, OUTPUT);
  pinMode(V, OUTPUT);
  analogWrite(R, 255);
  analogWrite(O, 255);
  analogWrite(V, 255);
}

void loop() {
  unsigned long currentMillis = millis();
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("At time :");
  //Serial.print(millis);
  Serial.print(", distance is ");
  Serial.println(distance);
  /*if (distance < 30)
  {
    analogWrite(R, 100);
    analogWrite(O, 0);
    analogWrite(V, 0);
  }
  else if (distance < 100)
  {
    analogWrite(R, 0);
    analogWrite(O, 100);
    analogWrite(V, 0);
  }
  else {
    analogWrite(R, 0);
    analogWrite(O, 0);
    analogWrite(V, 100);
  }*/
  // check if a proximity reading is available
  /*if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    int proximity = APDS.readProximity();
    if (proximity > 150) {
      if (currentMillis - previousMillis >= intervalLong) {
        previousMillis = currentMillis;
        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the green LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDG, ledState);
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDB, HIGH);
      }
    }
    else if(proximity > 110 && proximity <= 150){
      if (currentMillis - previousMillis >= intervalMedLo) {
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the blue LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDB, ledState);
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, ledState);
      }
    }
    else if(proximity > 80 && proximity <= 110){
      if (currentMillis - previousMillis >= intervalMed) {
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the blue LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDB, ledState);
        digitalWrite(LEDR, HIGH);
        digitalWrite(LEDG, HIGH);
      }
    }
    else if(proximity > 40 && proximity <= 80){
      if (currentMillis - previousMillis >= intervalMedSho) {
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the blue LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDB, ledState);
        digitalWrite(LEDR, ledState);
        digitalWrite(LEDG, HIGH);
      }
    }
    else {
      if (currentMillis - previousMillis >= intervalShort) {
        previousMillis = currentMillis;

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the blue LED with the ledState of the variable and turn off the rest
        digitalWrite(LEDR, ledState);
        digitalWrite(LEDB, HIGH);
        digitalWrite(LEDG, HIGH);
      }
    }
    // print value to the Serial Monitor
    Serial.println(proximity);
  }*/

  // wait a bit before reading again
  delay(100);
}
