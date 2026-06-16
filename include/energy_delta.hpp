#pragma once

#include <stdint.h>

constexpr double EXPECTED_WH_PER_KM = 80.0;

struct energy_delta_t {
  bool started = false;
  bool start_pending = false;
  bool last_rtd_button = false;
  uint8_t rtd_press_count = 0;

  double start_distance_m = 0.0;
  double start_consumed_wh = 0.0;
  double current_distance_m = 0.0;
  double current_consumed_wh = 0.0;

  double delta_wh = 0.0;
};

extern energy_delta_t energy_delta;

void energy_delta_update_rtd_button(bool rtd_button_pressed);
void energy_delta_update_power_tracking(double distance_m, double consumed_wh);
