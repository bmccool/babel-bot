///////////////////////////////////////////////////////////////////////////////
/// @file Button.hpp
/// This file contains header information for the file Button.cpp.
///
///////////////////////////////////////////////////////////////////////////////
// Make sure this is only included once
#ifndef BUTTON_HPP
#define BUTTON_HPP

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <stdint.h>

/////////////////////////// PROJECT INCLUDES //////////////////////////////////
#include "Error.hpp"

/////////////////////////// DEFINITIONS ///////////////////////////////////////
#define DEFAULT_BEHAVIOR release_forever
#define DEFAULT_FRAMES MAX_FRAMES
#define DEFAULT_STATE false
/////////////////////////// TYPES  ////////////////////////////////////////////
enum button_behavior_enum
{
    press_forever = 0,
    release_forever,
    release_after_frames,
    press_after_frames,
    button_behavior_enum_end
};
////////////////////////////// CLASS DECLARATION ///////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// A class used for storing the state of a button and interfacing with the
/// state.
////////////////////////////////////////////////////////////////////////////////
class Button
{
    button_behavior_enum behavior; // The behavior of the button
    uint32_t frames; // The number of frames left in the frame counter
    bool state; // The current state of the button i.e. pressed/not pressed.
    
    error_enum button_update();
  public:
    Button(); 
    error_enum set_button(button_behavior_enum behavior,  
                     uint32_t frames);
    bool is_pressed();
    uint32_t get_frames();
    button_behavior_enum get_behavior();
    error_enum tick();
};

#endif