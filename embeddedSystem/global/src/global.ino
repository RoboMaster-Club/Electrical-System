// Debug setting
#define DEBUG 

// I2C
#include <Wire.h>

// WIFI libraries
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

// Async library
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <AsyncWebSocket.h>

// FS
#include <FS.h>
#include <SPIFFS.h>
#include <SPIFFSEditor.h>

//Include Libraries
#include "Wire.h"
#include "Adafruit_MCP9808.h"
#include "RTClib.h"
#include <math.h>

//Defining Pins
# define VBATPIN A0
# define VCAPIN  A1
# define IBATTPIN  A2
# define VRATIO 30.0//votage ratio: max voltage displayed
# define VMIN 1
# define VBOOST A3
# define TX 10
# define RX 11
# define RX2 16
# define TX2 17
# define BUZZ_PIN 0
# define CHIP_SELECT 33

// Debugging
#define LED_BUILTIN 2

// Define data structure
struct DataPacket
{
  unsigned long timestamp;
  float vbatt;
  float vcap;
  float ibatt;
  float tempC;
  bool ableBoost;
  float vertiDist;
  float leftDist;
  float rightDist;
  float rearDist;
  float leftGrabDist;
  float rightGrabDist;
  bool isLeftClaw;
  bool isRightClaw;
};

union SerializedDataPacket
{
  struct DataPacket rawData;
  byte serialized[42];
};

const struct DataPacket DefaultValue = {
  0, 0, 0, 1, 3, true, 0, 0, 0, 0, 0, 0, false, false
};

struct DataPacket currentMeasurement;
bool isAccessMeasurement = false;

// Sensors initialization
// Adafruit_LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
// SoftwareSerial esp32(RX, TX);

// RTC sensor
RTC_PCF8523 rtc;

// Web server
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Replace with your network credentials
const char* SSID     = "BoilerBot_Standard_1";
const char* PASSWORD = "TESTIRES";
const char* HOSTNAME = "boiler.bot";

// Websocket connection tracker
uint32_t broadcast_id = -1;

void notFound(AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "Not found");
}

// Register a timer event function for instance
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
  // Serial.println(type);
  if(type == WS_EVT_CONNECT){
    //client connected
    Serial.printf("ws[%s][%u] connect: %u\n", server->url(), client->id());
  } else if(type == WS_EVT_DISCONNECT) {
    //client disconnected
    Serial.printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    if (broadcast_id == client->id()) {
      broadcast_id = -1;
    }
  } else if(type == WS_EVT_ERROR) {
    //error was received from the other end
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if(type == WS_EVT_PONG) {
    //pong message was received (in response to a ping request maybe)
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len)?(char*)data:"");
  } else if(type == WS_EVT_DATA) {
    Serial.printf("Broadcast id: %d\n", broadcast_id);
    Serial.printf("Client id: %d\n", client->id());
    if (broadcast_id != -1 && broadcast_id != client->id()) {
      return;
    } else {
      broadcast_id = client->id();
      union SerializedDataPacket data;
      data.rawData = currentMeasurement;
      server->binaryAll(data.serialized, sizeof(data));
      Serial.printf("ws[%s][%u] sent response: %u\n", server->url(), client->id());
    }
  }
}

//Function Protoypes
void setup() {
  // setup_temp();
  // setup_reg();
  // currentMeasurement = DefaultValue
    pinMode(LED_BUILTIN, OUTPUT);

    // Serial
    Serial.begin(115200);
    Serial.println();
    Serial.println("Configuring access point...");

    // AP setup
    WiFi.softAPsetHostname(HOSTNAME);
    WiFi.softAP(SSID);

    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("Hostname: ");

    // Initialize measurement
    currentMeasurement = DefaultValue;

    // RTC setup
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }

    // FS
    SPIFFS.begin();
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");

    // Server Handlers
    // WS Handlers
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //     request->send(200, "text/plain", "Hello, world");
    // });

    server.onNotFound(notFound);

    server.begin();

}

void loop() {
  // loop_AP();
  // while (isAccessMeasurement);
  // isAccessMeasurement = true;
  DateTime now = rtc.now();
  currentMeasurement.timestamp = now.unixtime();
  currentMeasurement.ableBoost = !currentMeasurement.ableBoost;
  currentMeasurement.ibatt = cos(millis() / 1000.0);
  currentMeasurement.vbatt = sin(millis() / 1000.0);
  currentMeasurement.vcap  = log10(millis() / 1000.0);
}
