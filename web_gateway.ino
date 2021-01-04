#include "config.h"                     // Needed for Adafruit IO
#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
// Don't change the names of these #define's! they match the variant ones
#define SPIWIFI SPI
#define SPIWIFI_SS 10  // Chip select pin
#define SPIWIFI_ACK 9  // a.k.a BUSY or READY pin
#define ESP32_RESETN 6 // Reset pin
#define ESP32_GPIO0 -1 // Not connected
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   SPIWIFI_ACK, ESP32_RESETN, ESP32_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif

//For Adafruit IO
AdafruitIO_Time *seconds = io.time(AIO_TIME_SECONDS);
AdafruitIO_Feed *nightmodeButtonFeed = io.feed("alarm.nightmode");
AdafruitIO_Feed *debugButtonFeed = io.feed("alarm.debug-button");

//AdafruitIO_Feed *currentTempFeed = io.feed("air-particulate-sensor.currenttemp");
//AdafruitIO_Feed *currentHumiFeed = io.feed("air-particulate-sensor.currenthumi");
//AdafruitIO_Feed *currentSmokeFeed = io.feed("air-particulate-sensor.currentsmoke");
//AdafruitIO_Feed *pm25CurrentFeed = io.feed("air-particulate-sensor.currentpm25");
AdafruitIO_Feed *pm10CurrentFeed = io.feed("air-particulate-sensor.currentpm10");
AdafruitIO_Feed *pm25AQIFeed = io.feed("air-particulate-sensor.aqipm25");

AdafruitIO_Feed *pm10AQIFeed = io.feed("air-particulate-sensor.aqipm10");

//AdafruitIO_Feed *light = io.feed("light");
//AdafruitIO_Feed *counter = io.feed("counter");
AdafruitIO_Feed *pm25nowCastFeed = io.feed("air-particulate-sensor.nowcastpm25");
AdafruitIO_Feed *pm10nowCastFeed = io.feed("air-particulate-sensor.nowcastpm10");

AdafruitIO_Feed *NH3Feed = io.feed("kencana-air-sensor.nh3");
AdafruitIO_Feed *COFeed = io.feed("kencana-air-sensor.co");
AdafruitIO_Feed *NO2Feed = io.feed("kencana-air-sensor.no2");
AdafruitIO_Feed *NO2ppbvFeed = io.feed("kencana-air-sensor.no2-ppbv");
AdafruitIO_Feed *NO2HourlyAvgFeed = io.feed("kencana-air-sensor.no2-hrly-avg");
AdafruitIO_Feed *NO2HourlyMinFeed = io.feed("kencana-air-sensor.no2-hrly-min");
AdafruitIO_Feed *NO2HourlyMaxFeed = io.feed("kencana-air-sensor.no2-hrly-max");

AdafruitIO_Feed *C3H8Feed = io.feed("kencana-air-sensor.c3h8");
AdafruitIO_Feed *C4H10Feed = io.feed("kencana-air-sensor.c4h10");
AdafruitIO_Feed *CH4Feed = io.feed("kencana-air-sensor.ch4");
AdafruitIO_Feed *H2Feed = io.feed("kencana-air-sensor.h2");
AdafruitIO_Feed *C2H5OHFeed = io.feed("kencana-air-sensor.c2h5oh");

void setup() 
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  
  io.connect();
  
  //subscribe to AIO feeds from which we want input
  //iso->onMessage(handleISO);
  seconds->onMessage(handleSecs);
  nightmodeButtonFeed->onMessage(handlenightmodeButtonFeed);
  debugButtonFeed->onMessage(handledebugButtonFeed);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
}

void loop() {
  io.run();
  // put your main code here, to run repeatedly:
}
void handlenightmodeButtonFeed(AdafruitIO_Data *data) 
{
}
void handledebugButtonFeed(AdafruitIO_Data *data) 
{
}
void handlepingButtonFeed(AdafruitIO_Data *data) 
{
}
void handleSecs(char *data, uint16_t len) 
{
  Serial.println(data);
}
