#include "OledMonitor.h"


OledMonitor::OledMonitor(Adafruit_SSD1306* oled, uint8_t addr) {
    this->oled = oled;
    this->height = oled->height();
    this->width = oled->width();
    this->addr = addr;
}

void OledMonitor::init() {
  if(!oled->begin(SSD1306_SWITCHCAPVCC, addr=0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  oled->clearDisplay();
  oled->setTextWrap(false);

  // Draw logo
  oled->drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled->setCursor(LOGO_WIDTH + 4, 0);
  oled->setTextColor(WHITE);
  oled->setTextSize(1);
  oled->print("BoilerBot");
  oled->setCursor(LOGO_WIDTH + 4, 8);
  oled->print("Electrical");
  oled->setCursor(LOGO_WIDTH + 4, 16);
  oled->print("System Monitor");
  oled->setCursor(LOGO_WIDTH + 4, 24);
  oled->print("v1.0");
  oled->display();
  oled->setTextWrap(true);
}

void OledMonitor::print(char* text, uint8_t size) {
  // TODO able to print text with indent
  // and scroll through the whole char sequence like a banner

  // Erase current screen and write new text
  oled->clearDisplay();
  oled->drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled->setCursor(LOGO_WIDTH + 2, 0);
  oled->setTextSize(size);
  oled->print(text);
  oled->display();
  oled->startscrollright(0x00, 0x0F);
}

Adafruit_SSD1306 OledMonitor::getOled(void) {
    // Return oled instance used
    return *oled;
}