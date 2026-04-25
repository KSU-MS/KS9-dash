#include <Arduino.h>
#include <SPI.h>
#include <ST7789_t3.h>

#define TFT_SCLK 13 // SCLK can also use pin 14
#define TFT_MOSI 11 // MOSI can also use pin 7
#define TFT_CS 9    // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define TFT_DC 10 //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define TFT_RST 5 // RST can use any pin
#define SD_CS 20  // CS for SD card, can use any pin

// trying to use hardware spi on teensy 4.0
ST7789_t3 tft(TFT_CS, TFT_DC, TFT_RST);

// display driver chip ST7789V
// using the crystalfontz CFAF240320A0-024SN 2.4in 240x320

void setup() {
  tft.init(240, 320);

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("Hello World");
}

void loop() {}
