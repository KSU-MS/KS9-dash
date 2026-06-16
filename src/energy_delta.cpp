#include "energy_delta.hpp"

energy_delta_t energy_delta;

void energy_delta_update_rtd_button(bool rtd_button_pressed) {
  bool rising_edge = rtd_button_pressed && !energy_delta.last_rtd_button;

  if (rising_edge) {
    energy_delta.rtd_press_count++;

    if (energy_delta.rtd_press_count == 2 && !energy_delta.started) {
      energy_delta.start_pending = true;
    }
  }

  energy_delta.last_rtd_button = rtd_button_pressed;
}

void energy_delta_update_power_tracking(double distance_m, double consumed_wh) {
  energy_delta.current_distance_m = distance_m;
  energy_delta.current_consumed_wh = consumed_wh;

  if (energy_delta.start_pending && !energy_delta.started) {
    energy_delta.started = true;
    energy_delta.start_pending = false;
    energy_delta.start_distance_m = distance_m;
    energy_delta.start_consumed_wh = consumed_wh;
    energy_delta.delta_wh = 0.0;
    return;
  }

  if (!energy_delta.started)
    return;

  double distance_used_m = distance_m - energy_delta.start_distance_m;
  double consumed_used_wh = consumed_wh - energy_delta.start_consumed_wh;

  if (distance_used_m < 0.0 || consumed_used_wh < 0.0)
    return;

  double expected_wh = EXPECTED_WH_PER_KM * (distance_used_m / 1000.0);

  energy_delta.delta_wh = expected_wh - consumed_used_wh;
}
