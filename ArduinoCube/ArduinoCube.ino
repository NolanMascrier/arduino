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
#include <Arduino_LSM9DS1.h>
#include <Arduino.h>
#include "arduino_secrets.h"

#define TRIGG_BOTTOM D12
#define TRIGG_TOP D10
#define TRIGG_1 D8
#define TRIGG_2 A0
#define TRIGG_3 A2
#define TRIGG_4 A4

#define ECHO_BOTTOM D11
#define ECHO_TOP D9
#define ECHO_1 D7
#define ECHO_2 A1
#define ECHO_3 A3
#define ECHO_4 A5

float x = 0;
float y = 0;
float z = 0;

int plusThreshold = 30;
int minusThreshold = -30;

std::string sides[6] = {"Bottom", "Top", "Right", "Front", "Left", "Back"};
long durations[6];
long distances[6];

/**
 * Sets up the Arduino.
*/
void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up");

  while (!Serial);
  Serial.println("Serial connected.");
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
    while (1);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  //Init the sensors
  pinMode(TRIGG_BOTTOM, OUTPUT);
  pinMode(TRIGG_TOP, OUTPUT);
  pinMode(TRIGG_1, OUTPUT);
  pinMode(TRIGG_2, OUTPUT);
  pinMode(TRIGG_3, OUTPUT);
  pinMode(TRIGG_4, OUTPUT);

  pinMode(ECHO_BOTTOM, INPUT);
  pinMode(ECHO_TOP, INPUT);
  pinMode(ECHO_1, INPUT);
  pinMode(ECHO_2, INPUT);
  pinMode(ECHO_3, INPUT);
  pinMode(ECHO_4, INPUT);
}

/**
 * Reads the data from the sensor and calculates the distance.
 * /home/devel/arduino/.env
 * 
 * @arg trigger Pin number for the trigger.
 * @arg echo Pin number for the echo.
 * @return calculated distance.
*/
int fire_sensor(int trigger, int echo)
{
  int dist;
  long dur;

  digitalWrite(trigger, LOW);
  delayMicroseconds(100);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigger, LOW);
  dur = pulseIn(echo, HIGH);
  dist = dur * 0.034 / 2;
  delay(100);
  return (dist);
}

/**
 * Sends the data to the server. Writes it as a JSON parsable string
 * and sends it to the Serial Monitor.
*/
void send_JSON()
{
  std::string json = "{";
  json += "\"" + sides[0] + "\":" + std::to_string(distances[0]) + ",";
  json += "\"" + sides[1] + "\":" + std::to_string(distances[1]) + ",";
  json += "\"" + sides[2] + "\":" + std::to_string(distances[2]) + ",";
  json += "\"" + sides[3] + "\":" + std::to_string(distances[3]) + ",";
  json += "\"" + sides[4] + "\":" + std::to_string(distances[4]) + ",";
  json += "\"" + sides[5] + "\":" + std::to_string(distances[5]) + ",";
  json += "\"X\":" + std::to_string(x) + ",";
  json += "\"Y\":" + std::to_string(y) + ",";
  json += "\"Z\":" + std::to_string(z) + "";
  json += "}";

  Serial.println(json.c_str());
}

/**
 * Main loop running inside the Arduino. Calls the sensors 
 * and the gyroscope, and sends the results to the Python server
 * through the Serial as JSON.
*/
void loop() 
{
  distances[0] = fire_sensor(TRIGG_BOTTOM, ECHO_BOTTOM);
  distances[1] = fire_sensor(TRIGG_TOP, ECHO_TOP);
  distances[2] = fire_sensor(TRIGG_1, ECHO_1);
  distances[3] = fire_sensor(TRIGG_2, ECHO_2);
  distances[4] = fire_sensor(TRIGG_3, ECHO_3);
  distances[5] = fire_sensor(TRIGG_4, ECHO_4);
  send_JSON();
  delayMicroseconds(10000);
}
