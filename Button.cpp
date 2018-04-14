///////////////////////////////////////////////////////////////////////////////
/// @file Button.cpp
/// This file contains functions for interfacing with the button class.
///
///////////////////////////////////////////////////////////////////////////////

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <iostream>
#include <stdio.h>

/////////////////////////// PROJECT INCLUDES   ////////////////////////////////
#include "Controller.hpp"
#include "Error.hpp"

using namespace std;
/////////////////////////// CLASS DEFINITIONS /////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// The Constructor for Button class.  Each button is constructed with the 
/// behavior set to "Release Forever", the frames set to 0, and the state set
/// to false.
///////////////////////////////////////////////////////////////////////////////
Button::Button()
{
    behavior = release_forever;
    frames = MAX_FRAMES;
    state = false;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows the caller to press a button for a number of frames.
/// The frames counter ticks down on each button each time button_tick() is
/// called.
/// 
/// @param[in]  behavior    The enum corresponding to the type of behavior this
///                         button should have.  This is defined by the
///                         button_behavior_enum.
/// @param[in]  frames  The number of frames that the button will be held for.
///                     Note this is a uint32_t type.
/// @return Returns an error_enum type indicating success or failure.
///////////////////////////////////////////////////////////////////////////////
error_enum Button::set_button(button_behavior_enum input_behavior, uint32_t input_frames)
{

    behavior = input_behavior;
    frames = input_frames;
    
    error_enum error = button_update();
    
    return error;
    
}

///////////////////////////////////////////////////////////////////////////////
/// This function queries the status of a button in the controller state.
/// 
/// @return     A bool is returned indicating true if the button is pressed,
///             or false if the button is not pressed.
///////////////////////////////////////////////////////////////////////////////
bool Button::is_pressed()
{
    return state;
}

///////////////////////////////////////////////////////////////////////////////
/// This function returns the frame counter of the button.
/// 
/// @return     Frame counter for the button.
///////////////////////////////////////////////////////////////////////////////
uint32_t Button::get_frames()
{
    return frames;
}

///////////////////////////////////////////////////////////////////////////////
/// This function returns the behavior of the button.
/// 
/// @return     Behavior of the button.
///////////////////////////////////////////////////////////////////////////////
button_behavior_enum Button::get_behavior()
{
    return behavior;
}

///////////////////////////////////////////////////////////////////////////////
/// This function will tick down the frame counter by one on the button
/// frame counter.  If a frame counter reaches 0, the button is handled based
/// on its behavior.
/// 
/// @return Returns an error_enum type indicating success or failure.
///////////////////////////////////////////////////////////////////////////////
error_enum Button::tick()
{
    error_enum error = ERR_NONE;
    if (--frames == 0)
    {
        error = button_update();
    }
    return error;
}

///////////////////////////////////////////////////////////////////////////////
/// This function updates the status, behavior, and frames.
/// 
/// @return Returns an error_enum type indicating success or failure.
///////////////////////////////////////////////////////////////////////////////
error_enum Button::button_update()
{
    // Check that behavior is defined
    if (behavior < button_behavior_enum_end)
    {   
        // Behavior is defined, proceed
        if (frames == 0)
        {
            switch (behavior)
            {
                case press_forever:
                    state = true;
                    frames = MAX_FRAMES;
                    break;
                case press_after_frames:
                    state = true;
                    frames = MAX_FRAMES;
                    behavior = press_forever;
                    break;
                case release_forever:
                    state = false;
                    frames = MAX_FRAMES;
                    break;
                case release_after_frames:
                    state = false;
                    frames = MAX_FRAMES;
                    behavior = release_forever;
                    break;
                default:
                    break;
            }
        }
        else
        {
            switch (behavior)
            {
                case press_forever:
                    state = true;
                    break;
                case press_after_frames:
                    state = false;
                    break;
                case release_forever:
                    state = false;
                    break;
                case release_after_frames:
                    state = true;
                    break;
                default:
                    break;
            }
        }
        return ERR_NONE;
    }
    else
    {
        // Behavior is undefined, return error
        state = DEFAULT_STATE;
        frames = DEFAULT_FRAMES;
        behavior = DEFAULT_BEHAVIOR;
        return ERR_BUTTON_UNDEFINED_BEHAVIOR;
    }
}