#pragma once

// External imports
#include <Arduino.h>

// Local
#include "can_handeler.hpp"
#include "display_handeler.hpp"
#include "parameters.hpp"

bool btn_1, btn_2, btn_3, btn_4, btn_5, btn_6;              // OK High
bool BMS_state = true, IMD_state = true, BSPD_state = true; // OK High

// Expects OK High signals
void update_lights() {
  digitalWrite(BMS_LIGHT, !BMS_state);
  digitalWrite(IMD_LIGHT, !IMD_state);
  digitalWrite(BSPD_LIGHT, !BSPD_state);
}

// Outputs HIGH when a pull-down button is pressed
void update_buttons() {
  btn_1 = digitalRead(BUTTON1);
  btn_2 = digitalRead(BUTTON2);
  btn_3 = digitalRead(BUTTON3);
  btn_4 = digitalRead(BUTTON4);
  btn_5 = digitalRead(BUTTON5);
  btn_6 = digitalRead(BUTTON6);
}

//
//// Interval Function stuffs
IntervalTimer timer_1hz;
IntervalTimer timer_10hz;

void timer_1hz_func() { send_firmware_status_message(); }

void timer_10hz_func() {
  send_button_status_message(btn_1, btn_2, btn_3, btn_4, btn_5, btn_6);
}
