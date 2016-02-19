#include "Arduino.h"

// Wifi Config
const char SSID[] = "....";
const char WIFI_PASS[] = "password";

const char UNIT_ID[] = "Tengu01"; 

const long SERIAL_BAUD = 57600;

// Pin assignments
const byte MOTION_PIN = D0;
const byte HUMIDITY_PIN = D3;
const byte IR_RECEIVE_PIN = D5;
const byte IR_SEND_PIN = D6;
const byte TEMPERATURE_PIN = D8;

// Spare
const byte SWITCH_1_PIN = D7;
const byte SWITCH_2_PIN = D4;
const byte ANALOG_IN = A0;

// Timer variables
const long SENSOR_CHECK_INTERVAL = 5000; // Time between sensor reads

// JSON string tags
const char ID[] = "id";
const char VERSION[] = "version";
const char AIR_TEMP[] = "air_temp";
const char HUMIDITY[] = "humidity";
const char ILLUMINANCE[] = "illuminance";
