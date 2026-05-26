#include "main.hpp"
#include "can_handeler.hpp"
#include "display_handeler.hpp"

int t[20];
int n = 0;

uint16_t normalize[] = {129, 216, 348, 955, 630, 1658, 185, 168,
                        955, 129, 195, 163, 604, 362,  253, 6950};

void setup() {
  for (int i = 0; i < sizeof(gpio_inputs); i++)
    pinMode(gpio_inputs[i], INPUT);

  for (int i = 0; i < sizeof(gpio_outputs); i++) {
    pinMode(gpio_outputs[i], OUTPUT);
    digitalWrite(gpio_outputs[i], LOW);
  }

  timer_1hz.begin(timer_1hz_func, 1000000);
  timer_10hz.begin(timer_10hz_func, 100000);

  start_display();

  tft.setRotation(0);
  tft.setTextWrap(true);
  tft.setTextColor(RGB(31, 31, 31), RGB(0, 0, 0));
  tft.setCursor(0, 0);

  tft.fillScreen(RGB(0, 0, 0));

  t[n++] = millis();
  tft.fillScreen(ST7735_BLACK);
  t[n++] = millis();
  testdrawtext(
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur "
      "adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, "
      "fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor "
      "neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet "
      "ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a "
      "tortor imperdiet posuere. ",
      ST7735_WHITE, ST7735_WHITE);
  t[n++] = millis();
  tftPrintTest(false);
  t[n++] = millis();
  testdrawtext(
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur "
      "adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, "
      "fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor "
      "neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet "
      "ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a "
      "tortor imperdiet posuere. ",
      ST7735_WHITE, ST7735_BLACK);
  t[n++] = millis();
  tftPrintTest(true);
  t[n++] = millis();
  testlines(ST7735_YELLOW);
  t[n++] = millis();
  testfastlines(ST7735_RED, ST7735_BLUE);
  t[n++] = millis();
  testdrawrects(ST7735_GREEN);
  t[n++] = millis();
  testfillrects(ST7735_YELLOW, ST7735_MAGENTA);
  t[n++] = millis();
  tft.fillScreen(ST7735_BLACK);
  t[n++] = millis();
  testfillcircles(10, ST7735_BLUE);
  t[n++] = millis();
  testdrawcircles(10, ST7735_WHITE);
  t[n++] = millis();
  testroundrects();
  t[n++] = millis();
  testtriangles();
  t[n++] = millis();
  mediabuttons();
  t[n++] = millis();
  tft.fillScreen(RGB(0, 0, 0));
}

void loop() {
  //
  //// CAN Stage
  check_messages();

  //
  //// GPIO Stage
  update_buttons();
  update_lights();

  //
  //// tftlay Stage
  static float fps = 0.0;
  static int h = 0;

  uint8_t r, g, b;
  if (h < 32) {
    r = 31;
    g = h;
    b = 0;
  } else if (h < 64) {
    r = 63 - h;
    g = 31;
    b = 0;
  } else if (h < 96) {
    r = 0;
    g = 31;
    b = h - 64;
  } else if (h < 128) {
    r = 0;
    g = 127 - h;
    b = 31;
  } else if (h < 160) {
    r = h - 128;
    g = 0;
    b = 31;
  } else if (h < 192) {
    r = 31;
    g = 0;
    b = 191 - h;
  } else {
    r = 31;
    g = 0;
    b = 0;
    h = 0;
  }

  h++;

  int start = micros();
  tft.fillRect(120, 0, 8, 160, RGB(r, g, b));

  tft.setTextWrap(false);
  tft.setTextColor(RGB(31, 31, 31), RGB(0, 0, 0));
  tft.setCursor(0, 0);

  for (int i = 1; i < n; i++) {
    tft.print(i < 10 ? "Test  " : "Test ");
    tft.print(i, DEC);
    tft.print(": ");
    tft.println(float(normalize[i - 1]) / float(t[i] - t[i - 1]), 2);
  }

  tft.println("");
  tft.print("Total  : ");
  tft.println(float(normalize[n - 1]) / float(t[n - 1] - t[0]), 2);

  tft.println("");
  tft.print("FPS    : ");
  tft.println(fps, 2);

  int end = micros();

  fps = 1000000.0f / float(end - start);
}
