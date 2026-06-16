#pragma once
#include "display/lv_display.h"
#include "parameters.hpp"
#include <ST7789_t3.h>
#include <lvgl.h>

ST7789_t3 tft(TFT_CS, TFT_DC, TFT_RST);
static lv_display_t *display;

// NOTE: The DMAMEM prefix here puts this into the teensy's ram2
DMAMEM static lv_color_t buf[DISPLAY_HORIZONTAL * DISPLAY_VERTICAL];

LV_FONT_DECLARE(comic_70)
LV_FONT_DECLARE(comic_32)
LV_FONT_DECLARE(comic_22)

struct joe_dash_t {
  // Critical
  lv_obj_t *TS_voltage;
  lv_obj_t *GLV_voltage;

  // Very important
  lv_obj_t *Screenshot_fault;
  lv_obj_t *BSE_fault;
  lv_obj_t *APPS_fault;
  lv_obj_t *Inverter_fault;
  lv_obj_t *Inverter_fault_text;

  // Still important
  lv_obj_t *Pack_temps_c;
  lv_obj_t *Low_cell_voltage;
  lv_obj_t *Inverter_temps_c;

  // Helpful
  lv_obj_t *Torque_limit_nm;
  lv_obj_t *VCU_state;

  // Gizmo
  lv_obj_t *Time_delta;
  lv_obj_t *Energy_delta;
} joe_dash;

void update_display(lv_display_t *disp, const lv_area_t *area,
                    uint8_t *px_buf) {
  uint16_t width = (area->x2 - area->x1 + 1);
  uint16_t height = (area->y2 - area->y1 + 1);

  tft.writeRect(area->x1, area->y1, width, height, (uint16_t *)px_buf);

  lv_display_flush_ready(disp);
}

void start_display() {
  // NOTE: I know this looks awful, just don't worry about it
  tft.init(DISPLAY_VERTICAL, DISPLAY_HORIZONTAL); // 240 w x 320 h
  tft.setRotation(1);                             // 320 w x 240 h
  tft.fillScreen(0);

  lv_init();
  lv_tick_set_cb(millis);

  display = lv_display_create(DISPLAY_HORIZONTAL, DISPLAY_VERTICAL);

  lv_display_set_buffers(display, buf, NULL, sizeof(buf),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_display_set_flush_cb(display, update_display);

  // Labels
  joe_dash.TS_voltage = lv_label_create(lv_screen_active());
  joe_dash.GLV_voltage = lv_label_create(lv_screen_active());
  joe_dash.Screenshot_fault = lv_label_create(lv_screen_active());
  joe_dash.BSE_fault = lv_label_create(lv_screen_active());
  joe_dash.APPS_fault = lv_label_create(lv_screen_active());
  joe_dash.Inverter_fault = lv_obj_create(lv_screen_active());
  joe_dash.Inverter_fault_text = lv_label_create(joe_dash.Inverter_fault);
  joe_dash.Inverter_temps_c = lv_label_create(lv_screen_active());
  joe_dash.Pack_temps_c = lv_label_create(lv_screen_active());
  joe_dash.Low_cell_voltage = lv_label_create(lv_screen_active());
  joe_dash.Torque_limit_nm = lv_label_create(lv_screen_active());
  joe_dash.VCU_state = lv_label_create(lv_screen_active());
  joe_dash.Energy_delta = lv_label_create(lv_screen_active());

  // TODO: Finish this
  // Bars
  // joe_dash.Time_delta =

  //
  //// CENTER
  // Voltage labels
  lv_label_set_text(joe_dash.TS_voltage, "000v");
  lv_obj_align(joe_dash.TS_voltage, LV_ALIGN_CENTER, 20, -10);
  lv_obj_set_style_text_font(joe_dash.TS_voltage, &comic_70, 0);
  lv_obj_set_style_text_letter_space(joe_dash.TS_voltage, 7, 0);

  lv_label_set_text(joe_dash.GLV_voltage, "00.0v");
  lv_obj_align(joe_dash.GLV_voltage, LV_ALIGN_CENTER, 10, 45);
  lv_obj_set_style_text_font(joe_dash.GLV_voltage, &comic_32, 0);
  lv_obj_set_style_text_letter_space(joe_dash.GLV_voltage, 3, 0);

  // TODO : Make this real
  // lv_label_set_text_fmt(joe_dash.GLV_voltage, "%.1fv",
  //                       joe_dash.GLV_voltage_value);

  //
  //// BOTTOM RIGHT
  // APPS lables
  lv_obj_set_size(joe_dash.Inverter_fault, 55, 30);
  lv_obj_align(joe_dash.Inverter_fault, LV_ALIGN_BOTTOM_RIGHT, 0, -118);
  lv_obj_set_style_bg_color(joe_dash.Inverter_fault, lv_color_hex(0x808080), 0);
  lv_obj_set_style_bg_opa(joe_dash.Inverter_fault, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(joe_dash.Inverter_fault, 0, 0);
  lv_obj_set_style_radius(joe_dash.Inverter_fault, 0, 0);
  lv_obj_set_style_pad_all(joe_dash.Inverter_fault, 0, 0);

  lv_label_set_text(joe_dash.Inverter_fault_text, "INV");
  lv_obj_center(joe_dash.Inverter_fault_text);
  lv_obj_set_style_text_font(joe_dash.Inverter_fault_text, &comic_32, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Inverter_fault_text, 3, 0);
  lv_obj_set_style_text_color(joe_dash.Inverter_fault_text,
                              lv_color_hex(0xFFFFFF), 0);

  lv_label_set_text(joe_dash.Screenshot_fault, "SS");
  lv_obj_align(joe_dash.Screenshot_fault, LV_ALIGN_BOTTOM_RIGHT, -5, -75);
  lv_obj_set_style_text_font(joe_dash.Screenshot_fault, &comic_32, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Screenshot_fault, 3, 0);

  lv_label_set_text(joe_dash.BSE_fault, "BSE");
  lv_obj_align(joe_dash.BSE_fault, LV_ALIGN_BOTTOM_RIGHT, -5, -40);
  lv_obj_set_style_text_font(joe_dash.BSE_fault, &comic_32, 0);
  lv_obj_set_style_text_letter_space(joe_dash.BSE_fault, 3, 0);

  lv_label_set_text(joe_dash.APPS_fault, "APPS");
  lv_obj_align(joe_dash.APPS_fault, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
  lv_obj_set_style_text_font(joe_dash.APPS_fault, &comic_32, 0);
  lv_obj_set_style_text_letter_space(joe_dash.APPS_fault, 3, 0);

  //
  //// BOTTOM LEFT
  // Temp labels
  lv_label_set_text(joe_dash.Pack_temps_c, "00/00");
  lv_obj_align(joe_dash.Pack_temps_c, LV_ALIGN_BOTTOM_LEFT, 5, -95);
  lv_obj_set_style_text_font(joe_dash.Pack_temps_c, &comic_22, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Pack_temps_c, 2, 0);

  lv_label_set_text(joe_dash.Low_cell_voltage, "-.---V");
  lv_obj_align(joe_dash.Low_cell_voltage, LV_ALIGN_BOTTOM_LEFT, 95, -95);
  lv_obj_set_style_text_font(joe_dash.Low_cell_voltage, &comic_22, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Low_cell_voltage, 2, 0);

  lv_label_set_text(joe_dash.Inverter_temps_c, "00/00/00");
  lv_obj_align(joe_dash.Inverter_temps_c, LV_ALIGN_BOTTOM_LEFT, 5, -65);
  lv_obj_set_style_text_font(joe_dash.Inverter_temps_c, &comic_22, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Inverter_temps_c, 2, 0);

  // VCU info labels
  lv_label_set_text(joe_dash.Torque_limit_nm, "000NM");
  lv_obj_align(joe_dash.Torque_limit_nm, LV_ALIGN_BOTTOM_LEFT, 5, -35);
  lv_obj_set_style_text_font(joe_dash.Torque_limit_nm, &comic_22, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Torque_limit_nm, 2, 0);

  lv_label_set_text(joe_dash.VCU_state, "UNKNOWN");
  lv_obj_align(joe_dash.VCU_state, LV_ALIGN_BOTTOM_LEFT, 5, -5);
  lv_obj_set_style_text_font(joe_dash.VCU_state, &comic_22, 0);
  lv_obj_set_style_text_letter_space(joe_dash.VCU_state, 2, 0);

  lv_label_set_text(joe_dash.Energy_delta, "--Wh");
  lv_obj_align(joe_dash.Energy_delta, LV_ALIGN_CENTER, 20, -85);
  lv_obj_set_style_text_font(joe_dash.Energy_delta, &comic_70, 0);
  lv_obj_set_style_text_letter_space(joe_dash.Energy_delta, 7, 0);

  lv_obj_t *colon_3 = lv_label_create(lv_screen_active());
  lv_label_set_text(colon_3, ":3");
  lv_obj_align(colon_3, LV_ALIGN_BOTTOM_MID, 15, -10);
  lv_obj_set_style_text_font(colon_3, &comic_32, 0);
  lv_obj_set_style_text_letter_space(colon_3, 10, 0);
}
