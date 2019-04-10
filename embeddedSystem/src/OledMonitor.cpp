#include "OledMonitor.h"

OledMonitor::OledMonitor(Adafruit_SSD1306 oled, uint8_t addr) {
    this.oled = oled;
    this.height = oled.height();
    this.width = oled.width();
    this.addr = addr;
}

OledMonitor::init(void) {
  if(!oled.begin(SSD1306_SWITCHCAPVCC, addr=0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  oled.clearDisplay();

  // Draw logo
  oled.drawBitmap(0, 0, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  oled.setCursor(LOGO_WIDTH + 2, 0);
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.print("BoilerBot Electrical System Monitor");
}

OledMonitor::print(String text, uint8_t size=1) {
    // Erase current screen and write new text
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(size);
    oled.print(text);
    oled.display();
}

OledMonitor::getOled(void) {
    // Return oled instance used
    return oled;
}