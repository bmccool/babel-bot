///////////////////////////////////////////////////////////////////////////////
/// @file GPIO.hpp
/// This file contains header information for the file GPIO.cpp.
///
///////////////////////////////////////////////////////////////////////////////
// Make sure this is only included once
#ifndef GPIO_HPP
#define GPIO_HPP

#include "Error.hpp"
/////////////////////////// DEFINITIONS ///////////////////////////////////////
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

enum PIN_DIRECTION{
	INPUT_PIN=0,
	OUTPUT_PIN=1
};

enum PIN_EDGE{
	RISING_EDGE,
	FALLING_EDGE
};

enum PIN_VALUE{
	LOW=0,
	HIGH=1
};

#define P9_11 30 // Data Out
#define P9_12 60 // Clock In, Rising Edge Trigger, Pull Down
#define P9_13 31 // Strobe In Latch, Active Low, Pull Down
#define P9_14 50
#define P9_15 48
#define P9_16 51
#define P9_17 5
#define P9_18 4

#if 0 // CORRECT PINOUT
#define SHIFT_PIN_3  P9_17
#define SHIFT_PIN_4  P9_15
#define SHIFT_PIN_5  P9_13
#define SHIFT_PIN_6  P9_11
#define SHIFT_PIN_11 P9_12
#define SHIFT_PIN_12 P9_14
#define SHIFT_PIN_13 P9_16
#define SHIFT_PIN_14 P9_18
    
#define DOWN_PIN SHIFT_PIN_11
#define UP_PIN SHIFT_PIN_12
#define LEFT_PIN SHIFT_PIN_13
#define RIGHT_PIN SHIFT_PIN_14
#define A_PIN SHIFT_PIN_3
#define B_PIN SHIFT_PIN_4
#define SELECT_PIN SHIFT_PIN_5
#define START_PIN SHIFT_PIN_6
#endif

#if 1 // JUST WORKS
#define LEFT_PIN      P9_11
#define A_PIN  P9_12
#define DOWN_PIN      P9_13
#define RIGHT_PIN   P9_14
#define UP_PIN P9_15
#define SELECT_PIN   P9_16
#define B_PIN  P9_17
#define START_PIN     P9_18
#endif


/////////////////////////// EXPORTED FUNCTIONS ////////////////////////////////
error_enum gpio_export(unsigned int gpio);
error_enum gpio_unexport(unsigned int gpio);
error_enum gpio_set_dir(unsigned int gpio, PIN_DIRECTION out_flag);
int gpio_set_value(unsigned int gpio, PIN_VALUE value);
int gpio_get_value(unsigned int gpio, unsigned int & value);
int gpio_set_edge(unsigned int gpio, PIN_EDGE edge);
int gpio_fd_open(unsigned int gpio);
int gpio_fd_close(int fd);

#endif
