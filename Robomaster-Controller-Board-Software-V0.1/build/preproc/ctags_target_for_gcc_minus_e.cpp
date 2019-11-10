# 1 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino"
# 1 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino"
// Debug setting
#define DEBUG 

// I2C
# 6 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2

// WIFI libraries
# 9 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 10 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2

// mDNS for local domain name resolution
# 13 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
// Async library
# 15 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 16 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 17 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2

// FS
# 20 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 21 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 22 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 23 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2

//Include Libraries
# 26 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 27 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 28 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 29 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2
# 30 "/Users/ChengMing/Documents/Robomaster/Power-System/BoilerBotElectricalSystemMonitor/global.ino" 2

//Defining Pins
#define VBATPIN 13
#define VCAPIN 32
#define IBATTPIN A2
#define VRATIO 30.0
#define VMIN 1
#define TX 10
#define RX 11
#define RX2 16
#define TX2 17
#define BUZZ_PIN 25

// SD card
#define CHIP_SELECT 33

// Oled
// HUD
#define HUD_OLED_WIDTH 128
#define HUD_OLEDHEIGHT 64
#define HUD_OLED_ADDR 0X3D


// Debug oled
#define DEBUG_OLED_WIDTH 128 /* OLED display width, in pixels*/
#define DEBUG_OLED_HEIGHT 32 /* OLED display height, in pixels*/
#define DEBUG_OLED_ADDR 0x3C
#define DEBUG_OLED_RESET -1 /* Reset pin # (or -1 if sharing Arduino reset pin)*/

// Debugging
#define LED_BUILTIN 2

// Define data structure
struct Measurement
{
  uint32_t timestamp;
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

union DataPacket
{
  struct Measurement rawData;
  byte serialized[50];
};

const struct Measurement DefaultValue = {
  0, 0, 0, 1, 3, true, 0, 0, 0, 0, 0, 0, false, false
};

struct Measurement currentMeasurement;
union DataPacket packet;
bool isAccessMeasurement = false;

// Sensors initialization
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

// Oled
Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 32 /* OLED display height, in pixels*/, &Wire, -1 /* Reset pin # (or -1 if sharing Arduino reset pin)*/);
OledMonitor monitor(&display, 0x3C);

// RTC sensor
RTC_PCF8523 rtc;

// Power distribution board
PDP pdp(13, 32, A2);

// SD logger
SDloggerFactory SDlogger = SDloggerFactory();

// Web server
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Replace with your network credentials
const char* SSID = "BoilerBot_Standard_1";
const char* PASSWORD = "TESTIRES";
const char* DOMAIN_NAME = "boilerbot";

// Websocket connection tracker
uint32_t broadcast_id = -1;

void readFile(fs::FS &fs, const char * path);

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
      server->binaryAll(packet.serialized, sizeof(packet.serialized));
      Serial.printf("ws[%s][%u] sent response\n", server->url(), client->id());
    }
  }
}

//Function Protoypes
void setup() {
  // setup_temp();
  // setup_reg();
  // currentMeasurement = DefaultValue
    pinMode(2, 0x02);

    ledcAttachPin(25,0);
    ledcSetup(0, 1000, 8);

    // Serial & Monitor initialization
    Serial.begin(115200);
    Serial.println();
    monitor.init(&Serial);

    // AP setup
    Serial.println("Configuring access point...");
    WiFi.softAP(SSID);

    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("Hostname: ");
    Serial.println(WiFi.softAPgetHostname());
    Serial.print("Domain name: ");
    Serial.printf("%s.local\n", DOMAIN_NAME);

    // mDNS setup
    if (!MDNS.begin(DOMAIN_NAME)) {
        Serial.println("Error setting up MDNS responder!");
    }
    MDNS.addService("http", "tcp", 80);

    // Logger setup
    Serial.println("SD logger test");
    SDlogger.init(33);
    SDlogger.info(&Serial);
    DateTime now = rtc.now();
    char logfile[40];
    sprintf(logfile, "/log-%d-%d-%d-%d-%d-%d.boiler", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
    SDlogger.setFp(logfile, "w");

    // Initialize measurement
    currentMeasurement = DefaultValue;

    // RTC setup
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }

    // Temperature sensor init
    // if (! tempsensor.begin(0x18)) {
    //   Serial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
    //   while (1);
    // }
    // Mode Resolution SampleTime
    //  0    0.5°C       30 ms
    //  1    0.25°C      65 ms
    //  2    0.125°C     130 ms
    //  3    0.0625°C    250 ms
    // tempsensor.setResolution(1);

    // FS
    SPIFFS.begin();
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.htm");
    // server.serveStatic("/log", SD, "/")

    // Server Handlers
    // WS Handlers
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    //     request->send(200, "text/plain", "Hello, world");
    // });

    server.onNotFound(notFound);

    server.begin();
    ledcWriteTone(0, 1000);
    delay(1000);
    ledcWriteTone(0, 0);
    delay(1000);
    ledcWriteTone(0, 2000);
    delay(1000);
    ledcWriteTone(0, 4000);
    delay(1000);
    ledcWriteTone(0, 3000);
    delay(1000);
    ledcWriteTone(0, 0);
    sdCardInfoDisplay();
}

void loop() {
  // loop_AP();
  // while (isAccessMeasurement);
  // isAccessMeasurement = true;
  DateTime now = rtc.now();
  currentMeasurement.timestamp = now.unixtime();
  currentMeasurement.ableBoost = pdp.canBoost();
  currentMeasurement.ibatt = pdp.getBatteryCurrent();
  currentMeasurement.vbatt = pdp.getBatteryVoltage();
  currentMeasurement.vcap = pdp.getCapacitorVoltage();
  // currentMeasurement.tempC = tempsensor.readTempC();
  packet.rawData = currentMeasurement;
  SDlogger.logByte(packet.serialized, sizeof(packet.serialized));
  delay(250);

}

void sdCardInfoDisplay(){
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
      Serial.println("No SD card attached");
      return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
      Serial.println("MMC");
  } else if(cardType == CARD_SD){
      Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
      Serial.println("SDHC");
  } else {
      Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  readFile(SD, "/as.txt");
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}
