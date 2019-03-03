#include "config.h"
#include "Arduino.h"

#include "IRremoteESP8266.h"

#include <Logging.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <ArduinoJson.h>
#include <BH1750.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

// WiFi
//ESP8266WiFiMulti wifi;
int wifi_status = WL_DISCONNECTED;

// Misc
SensorData data;
SimpleTimer timer;

// Sensor Config
OneWire onewire(TEMPERATURE_PIN);
DallasTemperature temperature_sensor(&onewire);
DHT humidity_sensor(HUMIDITY_PIN, HUMIDITY_SENSOR_TYPE);
BH1750 light_meter;

IRsend ir_blaster(IR_SEND_PIN);
IRrecv ir_receiver(IR_RECEIVE_PIN);

///////////////////////////////////////////////////////////////////////////////
// Main functions

void setup(){
    data.id = UNIT_ID;
    data.version = VERSION;

    Log.Init(SERIAL_BAUD, LOG_LEVEL);
    Log.Info("%s starting. ver %d", data.id, data.version);

    if (WIFI_ENABLED) {
        //start_wifi();
    }

    if (TEMPERATURE_ENABLED) {
        start_temperature();
    }

    if (HUMIDITY_ENABLED) {
        start_humidity();
    }

    if (ILLUMINANCE_ENABLED) {
        start_illuminance();
    }

    if (IR_BLASTER_ENABLED) {
        start_ir_blaster();
    }

    if (IR_RECEIVER_ENABLED) {
        start_ir_receiver();
    }
}


void loop(){
    timer.run();
}


///////////////////////////////////////////////////////////////////////////////
// Wifi
//
// void start_wifi(){
//     // Wait 4 seconds for WiFi to initialise
//     for (size_t i = 4; i > 0; i--) {
//         Log.Info("WiFi starting; wait %d seconds....\n", i);
//         Serial.flush();
//         delay(1000);
//     }
//
//     wifi.addAP(SSID, WIFI_PASS);
//     wifi.run();
// }
//
//
// bool upload_data(){
//     /** Upload the data object to Dweet.io
//     * Dweet uses a HTTP for humans to upload data, so only a GET request is used
//     */
//
//     bool upload_succeeded = false;
//
//     if (wifi.run() == WL_CONNECTED){
//         HTTPClient http;
//
//         // Package and GET the data to Dweet.io
//         http.begin(assemble_dweet_string());
//         int http_code = http.GET();
//
//         // http_code will be negative on an error
//         if (http_code == 200){
//             upload_succeeded = true;
//         }
//
//         http.end();
//     }
//
//     return upload_succeeded;
// }
//
//
// String assemble_dweet_string(){
//     /** Format the sensor/system data into a Dweet string
//     * String follows this format:
//     * https://dweet.io/dweet/for/my-thing-name?hello=world&more=stuff
//     */
//
//     String dweet_string = "http://dweet.io/dweet/for/";
//     dweet_string += data.id;
//     dweet_string += '?';
//
//     // Convert data object into JSON
//     StaticJsonBuffer<200> data_buffer;
//     JsonObject& output_packet = data_buffer.createObject();
//     output_packet["id"] = data.id;
//     output_packet["version"] = data.version;
//     output_packet["air_temperature"] = data.air_temperature;
//     output_packet["humidity"] = data.humidity;
//     output_packet["illuminance"] = data.illuminance;
//
//     // Add the entry data to the upload string
//     // https://github.com/bblanchon/ArduinoJson/wiki/Decoding-JSON
//     for (JsonObject::iterator it=output_packet.begin(); it!=output_packet.end(); ++it){
//         dweet_string += it->key;
//         dweet_string += '=';
//         dweet_string += it->value.asString();
//         dweet_string += '&';
//     }
//
//     // Remove last character
//     int length = strlen(dweet_string.c_str());
//     dweet_string[length-1] = '\0';
//
//     return dweet_string;
// }
//

///////////////////////////////////////////////////////////////////////////////
// Temperature

void start_temperature(){
    Log.Debug("Starting temperature...");
    temperature_sensor.begin();
    temperature_sensor.setResolution(TEMPERATURE_SENSOR_RESOLUTION);

    update_temperature();
    timer.setInterval(SENSOR_CHECK_INTERVAL, update_temperature);
}


void update_temperature(){
    data.air_temperature = get_temperature();
    Log.Verbose("Air temperature: %d.%d", int(data.air_temperature), int(data.air_temperature - int(data.air_temperature))*100);
}


float get_temperature(){
    temperature_sensor.requestTemperatures();
    return temperature_sensor.getTempCByIndex(0);
}


///////////////////////////////////////////////////////////////////////////////
// Humidity

void start_humidity(){
    Log.Debug("Starting humidity...");
    humidity_sensor.begin();

    update_humidity();
    timer.setInterval(SENSOR_CHECK_INTERVAL, update_humidity);
}


void update_humidity(){
    /* Update the humidity data entry    */
    data.humidity = get_humidity();
    Log.Verbose("Humidity: %d", int(data.humidity));
}


float get_humidity(){
    /** Get the humidity value from the sensor
    * returns: Humidity value in %
    */

    return humidity_sensor.readHumidity();
}


///////////////////////////////////////////////////////////////////////////////
// Light

void start_illuminance(){
    Log.Debug("Starting illuminance...");
    light_meter.begin(BH1750_CONTINUOUS_HIGH_RES_MODE);

    timer.setInterval(SENSOR_CHECK_INTERVAL, update_illuminance);
}


void update_illuminance(){
    data.illuminance = get_illuminance();
    Log.Verbose("Illuminance: %d", data.illuminance);
}


int get_illuminance(){
    return light_meter.readLightLevel();
}


///////////////////////////////////////////////////////////////////////////////
// IR

void start_ir_blaster(){
    ir_blaster.begin();
}


void switch_ac(bool state){
}

void set_ac_temperature(int temperature){
}

void start_ir_receiver(){

}
