///////////////////////////////////////////////////////////////////////////////
/// @file Controller.hpp
/// This file contains header information for the file Controller.cpp.
///
///////////////////////////////////////////////////////////////////////////////
// Make sure this is only included once
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <stdint.h>

/////////////////////////// PROJECT INCLUDES //////////////////////////////////
#include "Button.hpp"

/////////////////////////// DEFINITIONS ///////////////////////////////////////
#define MAX_FRAMES 0xFFFFFFFF

/////////////////////////// TYPES  ////////////////////////////////////////////
typedef uint8_t NES_buttons_status_byte;

/// An enum type for calling out the individual buttons in the NES_controller
/// class.
enum NES_buttons_enum
{
    nes_up = 0, 
    nes_down, 
    nes_left, 
    nes_right,
    nes_a,
    nes_b,
    nes_select,
    nes_start,
    nes_buttons_enum_end
};

/// A struct for bit-resolution access of the status of buttons in the
/// NES_controller class
typedef struct
{
    uint8_t up     : 1;
    uint8_t down   : 1;
    uint8_t left   : 1;
    uint8_t right  : 1;
    uint8_t a      : 1;
    uint8_t b      : 1;
    uint8_t select : 1;
    uint8_t start  : 1;
} NES_buttons_status_bits;

/// A union offering the ability to access the status of the buttons on a bit
/// level or a byte level.
typedef union 
{
    NES_buttons_status_bits bits;
    NES_buttons_status_byte byte;
} NES_buttons_status_union;


/// A struct for storing the amount of frames that the particular button is to
/// be continued to be held (pressed).
typedef struct
{
    uint32_t up;
    uint32_t down;
    uint32_t left;
    uint32_t right;
    uint32_t a;
    uint32_t b;
    uint32_t select;
    uint32_t start;
} NES_buttons_frames_t;

/// A struct for storing the behavior of the particular button.
typedef struct
{
    button_behavior_enum up;
    button_behavior_enum down;
    button_behavior_enum left;
    button_behavior_enum right;
    button_behavior_enum a;
    button_behavior_enum b;
    button_behavior_enum select;
    button_behavior_enum start;
} NES_buttons_behavior_t;

/// A struct for storing the status of each individual button, as well as the
/// frames that each button should continue to be pressed.
typedef struct
{
    NES_buttons_status_union status;
    NES_buttons_behavior_t behavior;
    NES_buttons_frames_t frames;
}NES_buttons_t;

////////////////////////////// CLASS DECLARATION ///////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// A class used for storing the internal state of the NES controller as well
/// as interfacing with that state.
////////////////////////////////////////////////////////////////////////////////
class NES_controller
{
    Button up;
    Button down;
    Button left;
    Button right;
    Button a;
    Button b;
    Button select;
    Button start;

  public:
    NES_controller(); 
    error_enum set_button(NES_buttons_enum button,
                          button_behavior_enum behavior,  
                          uint32_t frames);
    bool is_button_pressed(NES_buttons_enum button);
    uint8_t get_buttons();
    uint32_t get_frames(NES_buttons_enum button);
    error_enum button_tick();
    void print_buttons(bool new_line, bool print_time);
    void output_buttons(void);
    void set_all_buttons(uint8_t buttons_byte);
};

#endif