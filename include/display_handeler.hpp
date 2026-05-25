#pragma once
#include "parameters.hpp"
#include <ST7789_t3.h>

ST7789_t3 tft(TFT_CS, TFT_DC, TFT_RST);

void start_display() {}

void update_display() {}
