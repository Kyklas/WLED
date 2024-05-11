#pragma once

/*
 * Welcome!
 * You can use the file "my_config.h" to make changes to the way WLED is compiled!
 * It is possible to enable and disable certain features as well as set defaults for some runtime changeable settings.
 *
 * How to use:
 * PlatformIO: Just compile the unmodified code once! The file "my_config.h" will be generated automatically and now you can make your changes.
 *
 * ArduinoIDE: Make a copy of this file and name it "my_config.h". Go to wled.h and uncomment "#define WLED_USE_MY_CONFIG" in the top of the file.
 *
 * DO NOT make changes to the "my_config_sample.h" file directly! Your changes will not be applied.
 */

// uncomment to force the compiler to show a warning to confirm that this file is included
#warning **** my_config.h: Settings from this file are honored ****

/* Uncomment to use your WIFI settings as defaults
  //WARNING: this will hardcode these as the default even after a factory reset
#define CLIENT_SSID "Your_SSID"
#define CLIENT_PASS "Your_Password"
*/
// Local Config, not committed
#include "my_config_local.h"

//#define LIGHT_PineTree 0
//#define LIGHT_Mountain 1

#define MAX_LEDS 255

// Default
#define LIGHT_RGB_COUNT 5
#define MDNS_NAME "ESP32C3-DEV"
#define SERVERNAME "ESP32C3-DEV"
#define WLED_AP_SSID "ESP32C3-DEV-AP"

// WIP TLC59116
// i2ctransfer -f -y 1 w17@0x60 0x82 10 20 30 40 50 60 70 80 90 100 10 120 130 140 150 160
// device tree : reg = <0x60>

// #define USERMOD_TCL59XXX

#if LIGHT_DomeLight

#define I2CSCLPIN 2
#define I2CSDAPIN 3

#define LIGHT_RGB_COUNT 5
#define MDNS_NAME "DomeLight"
#define SERVERNAME "DomeLight"
#define WLED_AP_SSID "DomeLight-AP"

#define BTNPIN 9,8,-1,-1
#define BTNTYPE BTN_TYPE_PUSH,BTN_TYPE_PUSH,0,0

#define PIXEL_COUNTS 10,1,1,1,16
#define DATA_PINS 10,6,5,4,0x60
#define MULT_PINS 1,1,1,1,1
#define DEFAULT_LED_TYPE  TYPE_WS2812_RGB,TYPE_ANALOG_1CH,TYPE_ANALOG_1CH,TYPE_ANALOG_1CH,TYPE_EXPANDER

#define RLYPIN 7

#endif

#if LIGHT_Bordie
#define LIGHT_RGB_COUNT 5
#define MDNS_NAME "BordieLight"
#define SERVERNAME "BordieLight"
#define WLED_AP_SSID "BordieLight-AP"

#define BTNPIN 9,2,-1,-1
#define BTNTYPE BTN_TYPE_PUSH,BTN_TYPE_PUSH,0,0

#define PIXEL_COUNTS LIGHT_RGB_COUNT, 1, 1,
#define DATA_PINS 10, 4, 6, 3, 7
#define MULT_PINS 1, 1, 3
#define DEFAULT_LED_TYPE TYPE_WS2812_RGB, TYPE_ANALOG_1CH, TYPE_ANALOG_3CH
#endif

#if LIGHT_Mountain
#define LIGHT_RGB_COUNT 5
#define MDNS_NAME "MountainLight"
#define SERVERNAME "MountainLight"
#define WLED_AP_SSID "MountainLight-AP"

#define BTNPIN 9,2,-1,-1
#define BTNTYPE BTN_TYPE_PUSH,BTN_TYPE_PUSH,0,0

#define PIXEL_COUNTS LIGHT_RGB_COUNT, 1, 1,
#define DATA_PINS 10, 4, 6, 3, 7
#define MULT_PINS 1, 1, 3
#define DEFAULT_LED_TYPE TYPE_WS2812_RGB, TYPE_ANALOG_1CH, TYPE_ANALOG_3CH
#endif

#if LIGHT_PineTree
#define LIGHT_RGB_COUNT 11
#define MDNS_NAME "PineTreeLight"   
#define SERVERNAME "PineTreeLight"
#define WLED_AP_SSID "PineTreeLight-AP"

#define BTNPIN 9,-1,-1,-1
#define BTNTYPE BTN_TYPE_PUSH,0,0,0

#define PIXEL_COUNTS LIGHT_RGB_COUNT, 1, 1,
#define DATA_PINS 10, 4, 6
#define MULT_PINS 1, 1, 1
#define DEFAULT_LED_TYPE TYPE_WS2812_RGB, TYPE_ANALOG_1CH, TYPE_ANALOG_1CH
#endif


// Default config ESP32C3
#ifndef BTNPIN
#define BTNPIN 9,-1,-1,-1
#define BTNTYPE BTN_TYPE_PUSH,0,0,0
#endif

// Default config ESP32C3
#ifndef MULT_PINS
#define PIXEL_COUNTS 25
#define DATA_PINS 10
#define MULT_PINS 1
#define DEFAULT_LED_TYPE TYPE_WS2812_RGB
#endif
