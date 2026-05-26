#pragma once
#include "parameters.hpp"
#include <ST7789_t3.h>
#include <lvgl.h>

ST7789_t3 tft(TFT_CS, TFT_DC, TFT_RST);
static lv_display_t *display;
DMAMEM static lv_color_t buf[DISPLAY_HORIZONTAL * DISPLAY_VERTICAL];

void update_display(lv_display_t *disp, const lv_area_t *area,
                    uint8_t *px_buf) {
  uint16_t width = (area->x2 - area->x1 + 1);
  uint16_t height = (area->y2 - area->y1 + 1);

  tft.writeRect(area->x1, area->y1, width, height, (uint16_t *)px_buf);

  lv_display_flush_ready(disp);
}

void start_display() {
  tft.init(DISPLAY_VERTICAL, DISPLAY_HORIZONTAL); // 240 w x 320 h
  tft.setRotation(3);                             // 320 w x 240 h

  lv_init();
  lv_tick_set_cb(millis);

  display = lv_display_create(DISPLAY_HORIZONTAL, DISPLAY_VERTICAL);

  lv_display_set_buffers(display, buf, NULL, sizeof(buf),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_display_set_flush_cb(display, update_display);

  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello LVGL!");
}
