#include "main.hpp"
#include "can_handeler.hpp"

void setup() {
  for (int i = 0; i < sizeof(gpio_inputs); i++)
    pinMode(gpio_inputs[i], INPUT);

  for (int i = 0; i < sizeof(gpio_outputs); i++) {
    pinMode(gpio_outputs[i], OUTPUT);
    digitalWrite(gpio_outputs[i], LOW);
  }

  timer_1hz.begin(timer_1hz_func, 1000000);
  timer_10hz.begin(timer_10hz_func, 100000);
}

void loop() {
  //
  //// CAN Stage
  check_messages();

  //
  //// GPIO Stage
  update_buttons();
  update_lights();
}
