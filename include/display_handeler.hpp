#pragma once
#include "parameters.hpp"
#include <ST7789_t3.h>
#include <lvgl.h>

ST7789_t3 tft(TFT_CS, TFT_DC, TFT_RST);

void start_display() { tft.init(240, 320); }

void update_display() {}

#define RGB(r, g, b) (b << 11 | g << 6 | r)

float pi = 3.1415926f;

void testlines(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);

  for (int16_t x = 0; x < tft.width(); x += 6)
    tft.drawLine(0, 0, x, tft.height() - 1, color);

  for (int16_t y = 0; y < tft.height(); y += 6)
    tft.drawLine(0, 0, tft.width() - 1, y, color);

  for (int16_t x = 0; x < tft.width(); x += 6)
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);

  for (int16_t y = 0; y < tft.height(); y += 6)
    tft.drawLine(tft.width() - 1, 0, 0, y, color);

  for (int16_t x = 0; x < tft.width(); x += 6)
    tft.drawLine(0, tft.height() - 1, x, 0, color);

  for (int16_t y = 0; y < tft.height(); y += 6)
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);

  for (int16_t x = 0; x < tft.width(); x += 6)
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);

  for (int16_t y = 0; y < tft.height(); y += 6)
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
}

void testdrawtext(const char *text, uint16_t color, uint16_t bgcolor) {
  tft.setCursor(0, 0);
  tft.setTextColor(color, bgcolor);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);

  for (int16_t y = 0; y < tft.height(); y += 5)
    tft.drawFastHLine(0, y, tft.width(), color1);

  for (int16_t x = 0; x < tft.width(); x += 5)
    tft.drawFastVLine(x, 0, tft.height(), color2);
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);

  for (int16_t x = 0; x < tft.width(); x += 6)
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x,
                 color);
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);

  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x,
                 color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x,
                 color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < tft.width(); x += radius * 2)
    for (int16_t y = radius; y < tft.height(); y += radius * 2)
      tft.fillCircle(x, y, radius, color);
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2)
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2)
      tft.drawCircle(x, y, radius, color);
}

void testtriangles() {
  tft.fillScreen(ST7735_BLACK);

  int color = 0xF800;
  int t;
  int w = 63;
  int x = 159;
  int y = 0;
  int z = 127;

  for (t = 0; t <= 15; t += 1) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  tft.fillScreen(ST7735_BLACK);

  int color = 100;
  int i;
  int t;

  for (t = 0; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = 127;
    int h = 159;
    for (i = 0; i <= 24; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

#define SETCOLOR(c) tft.setTextColor(c, bg ? ST7735_BLACK : c);

void tftPrintTest(bool bg) {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  SETCOLOR(ST7735_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  SETCOLOR(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  SETCOLOR(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  SETCOLOR(ST7735_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);

  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  SETCOLOR(ST7735_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  SETCOLOR(ST7735_GREEN);
  tft.print(pi, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX);
  tft.println(" Print HEX!");
  tft.println(" ");
  SETCOLOR(ST7735_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  SETCOLOR(ST7735_MAGENTA);
  tft.print(millis() / 1000);
  SETCOLOR(ST7735_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);

  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);

  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);

  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
