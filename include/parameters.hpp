#pragma once
#include <stdint.h>

//
//// Car info
#define INVERTER_CAN_BAUD_RATE 500000

//
//// Display
#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10

#define DISPLAY_HORIZONTAL 320
#define DISPLAY_VERTICAL 240

//
//// User button pins
#define BUTTON6 2
#define BUTTON5 3
#define BUTTON4 4
#define BUTTON3 5
#define BUTTON2 6
#define BUTTON1 7

//
//// Fault Light pins
#define BMS_LIGHT 21
#define IMD_LIGHT 22
#define BSPD_LIGHT 23

// Initialization arrays
static uint8_t gpio_inputs[] = {BUTTON6, BUTTON5, BUTTON4,
                                BUTTON3, BUTTON2, BUTTON1};

static uint8_t gpio_outputs[] = {TFT_RST,   TFT_DC,    TFT_CS,
                                 BMS_LIGHT, IMD_LIGHT, BSPD_LIGHT};

//
//// GIT status message defs
// These values are provided by the python script ran by the lib_dep
// https://github.com/KSU-MS/pio-git-hash-gen
#ifndef AUTO_VERSION
#warning "AUTO_VERSION was not defined by the generator!"
#define AUTO_VERSION 0xdeadbeef
#endif

#ifndef FW_PROJECT_IS_DIRTY
#warning "FW_PROJECT_IS_DIRTY was not defined by the generator!"
#define FW_PROJECT_IS_DIRTY 1
#endif

#ifndef FW_PROJECT_IS_MAIN_OR_MASTER
#warning "FW_PROJECT_IS_MAIN_OR_MASTER was not defined by the generator!"
#define FW_PROJECT_IS_MAIN_OR_MASTER 0
#endif
