#include "Arduino.h"
#include "Logging.h"

// Wifi Config
const char SSID[] = "....";
const char WIFI_PASS[] = "password";

const char UNIT_ID[] = "Tengu01";
const int VERSION = 1;

const long SERIAL_BAUD = 57600;
const long LOG_LEVEL = LOG_LEVEL_VERBOSE;

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

struct SensorData{
    const char* id;
    int version;
    float air_temperature;
    float humidity;
    int illuminance;
};

// Function headers...
void start_wifi();
bool upload_data();
String assemble_dweet_string();
void start_temperature();
void update_temperature();
float get_temperature();
void start_humidity();
void update_humidity();
float get_humidity();
void start_illuminance();
void update_illuminance();
int get_illuminance();
void start_ir_blaster();
void switch_ac(bool state);
void set_ac_temperature(int temperature);
