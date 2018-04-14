///////////////////////////////////////////////////////////////////////////////
/// @file Controller.hpp
/// This file contains functions for interfacing with the controller state and
/// controller hardware.
///
///////////////////////////////////////////////////////////////////////////////

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <iostream>
#include <stdio.h>

/////////////////////////// PROJECT INCLUDES   ////////////////////////////////
#include "GPIO.hpp"
#include "Controller.hpp"

using namespace std;
/////////////////////////// CLASS DEFINITIONS /////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// The Constructor for NES_controller class.  Status and frame count of each
/// button is automatically set to 0.
///////////////////////////////////////////////////////////////////////////////
NES_controller::NES_controller()
{
    up.Button::set_button(release_forever, MAX_FRAMES);
    down.Button::set_button(release_forever, MAX_FRAMES);
    left.Button::set_button(release_forever, MAX_FRAMES);
    right.Button::set_button(release_forever, MAX_FRAMES);
    a.Button::set_button(release_forever, MAX_FRAMES);
    b.Button::set_button(release_forever, MAX_FRAMES);
    select.Button::set_button(release_forever, MAX_FRAMES);
    start.Button::set_button(release_forever, MAX_FRAMES);
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows the caller to press a button for a number of frames.
/// The frames counter ticks down on each button each time button_tick() is
/// called.
/// 
/// @param[in]  button  The enum corresponding to the button being pressed.
///                     This is defined by NES_buttons_enum.
/// @param[in]  behavior    The enum corresponding to the type of behavior this
///                         button should have.  This is defined by the
///                         buttons_behavior_enum.
/// @param[in]  frames  The number of frames that the button will be held for.
///                     Note this is a uint32_t type.
///////////////////////////////////////////////////////////////////////////////
error_enum NES_controller::set_button(NES_buttons_enum button, 
                                button_behavior_enum behavior,
                                uint32_t frames)
{
    
    switch (button)
    {
        case nes_up:
            up.set_button(behavior, frames);
            break;
        case nes_down:
            down.set_button(behavior, frames);
            break;
        case nes_left:
            left.set_button(behavior, frames);
            break;
        case nes_right:
            right.set_button(behavior, frames);
            break;
        case nes_a:
            a.set_button(behavior, frames);
            break;
        case nes_b:
            b.set_button(behavior, frames);
            break;
        case nes_select:
            select.set_button(behavior, frames);
            break;
        case nes_start:
            start.set_button(behavior, frames);
            break;
        default:
            return ERR_CONTROLLER_UNDEFINED_BUTTON;
            break;
    }
    return ERR_NONE;
}

///////////////////////////////////////////////////////////////////////////////
/// This function queries the status of a button in the controller state.
/// 
/// @param[in]  button  The enum corresponding to the button being in question.
///                     This is defined by the NES_buttons_enum.
/// @return     A bool is returned indicating true if the button is pressed,
///             or false if the button is not pressed.
///////////////////////////////////////////////////////////////////////////////
bool NES_controller::is_button_pressed(NES_buttons_enum button)
{
    switch (button)
    {
        case nes_up:
            return up.is_pressed();
        case nes_down:
            return down.is_pressed();
        case nes_left:
            return left.is_pressed();
        case nes_right:
            return right.is_pressed();
        case nes_a:
            return a.is_pressed();
        case nes_b:
            return b.is_pressed();
        case nes_select:
            return select.is_pressed();
        case nes_start:
            return start.is_pressed();
        default:
            return false; /// @todo return an error code.
    }
}

///////////////////////////////////////////////////////////////////////////////
/// This function will tick down the frame counter by one on each of the button
/// frame counters.  If a frame counter reaches 0, the corresponding button is
/// released (status = false)
/// 
///////////////////////////////////////////////////////////////////////////////
error_enum NES_controller::button_tick()
{
    error_enum error = ERR_NONE;
    error_enum temp_error = ERR_NONE;
    
    // Return only the last error or ERR_NONE
    temp_error = up.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    down.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    left.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    right.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    a.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    b.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    select.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    start.tick();
    if (temp_error != ERR_NONE) {error = temp_error;}
    
    return error;
}

///////////////////////////////////////////////////////////////////////////////
/// This function will print the remaining time of each of the currently pressed
/// buttons to stdout.  This is intended only as a means of debug.
/// 
/// @param[in]  new_line    A bool that determines if this print is to be on a
/// new line or if it is to be drawn over the previous line.  The intended use
/// of this is that if the function is called successivly, it will not pollute
/// the debug terminal with multiple lines for each call.
///////////////////////////////////////////////////////////////////////////////
void NES_controller::print_buttons(bool new_line, bool print_time)
{
    // Create 80 spaces on the line if we call for a new line.  This should 
    // give enough room to not have overlap.
    if (!new_line) 
    { 
        // Carriage return
        cout << "\r" << flush;
        for (int i = 80; i >= 0; i--) 
        {
            // print 80 spaces
            cout << " ";
            
        }
        // Carriage return to setup for next line
        cout << "\r";
    }
    
    // Determine if we are printing the buttons remaining time
    // or just the button presses.
    if (print_time)
    {    
        // If the status of the button is pressed, print its time.
        if (up.is_pressed())     {cout << " up_time = "     << up.get_frames();}
        if (down.is_pressed())   {cout << " down_time = "   << down.get_frames();}
        if (left.is_pressed())   {cout << " left_time = "   << left.get_frames();}
        if (right.is_pressed())  {cout << " right_time = "  << right.get_frames();}
        if (a.is_pressed())      {cout << " a_time = "      << a.get_frames();}
        if (b.is_pressed())      {cout << " b_time = "      << b.get_frames();}
        if (select.is_pressed()) {cout << " select_time = " << select.get_frames();}
        if (start.is_pressed())  {cout << " start_time = "  << start.get_frames();}
    }
    else
    {
        cout << (up.is_pressed()     ? " Up "     : "    ");
        cout << (down.is_pressed()   ? " Down "   : "      ");
        cout << (left.is_pressed()   ? " Left "   : "      ");
        cout << (right.is_pressed()  ? " Right "  : "       ");
        cout << (a.is_pressed()      ? " A "      : "   ");
        cout << (b.is_pressed()      ? " B "      : "   ");
        cout << (select.is_pressed() ? " Select " : "        ");
        cout << (start.is_pressed()  ? " Start "  : "       ");
    }
    // If anything was printed, and we we call for new lines, print a line feed.
    if (((up.is_pressed()     || 
          down.is_pressed()   || 
          left.is_pressed()   || 
          right.is_pressed()  || 
          a.is_pressed()      || 
          b.is_pressed()      || 
          select.is_pressed() || 
          start.is_pressed()) && new_line) ||
          /* OR if nothing was printed and we DONT call for new lines.*/
          (get_buttons() == 0 && !new_line))
    {
        cout << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// This function returns the status of the buttons as a single byte.
/// 
/// @return Returns the status of the buttons as an 8-bit byte.
///////////////////////////////////////////////////////////////////////////////
uint8_t NES_controller::get_buttons()
{
    uint8_t output_byte = 0;
    
    if (up.is_pressed())     {output_byte += 1;}
    if (down.is_pressed())   {output_byte += 2;}
    if (left.is_pressed())   {output_byte += 4;}
    if (right.is_pressed())  {output_byte += 8;}
    if (a.is_pressed())      {output_byte += 16;}
    if (b.is_pressed())      {output_byte += 32;}
    if (select.is_pressed()) {output_byte += 64;}
    if (start.is_pressed())  {output_byte += 128;}
    
    return output_byte;
}

///////////////////////////////////////////////////////////////////////////////
/// This function returns the status of the buttons as a single byte.
/// 
/// @param[in]  button  The enum defined by NES_buttons_enum corresponding to
///                     the button that is being queried.
/// @return     Returns the number of frames left in the frame counter for 
///                     this button.
///////////////////////////////////////////////////////////////////////////////
uint32_t NES_controller::get_frames(NES_buttons_enum button)
{
    switch (button)
    {
        case nes_up:
            return up.get_frames();
        case nes_down:
            return down.get_frames();
        case nes_left:
            return left.get_frames();
        case nes_right:
            return right.get_frames();
        case nes_a:
            return a.get_frames();
        case nes_b:
            return b.get_frames();
        case nes_select:
            return select.get_frames();
        case nes_start:
            return start.get_frames();
        default:
            cout << "something went wrong" << endl;
            return 0; /// @todo this function may need error checking...
    }
}

///////////////////////////////////////////////////////////////////////////////
/// This function outputs the status of the controller to the GPIO pins.  This
/// function has no inputs or outputs.
///////////////////////////////////////////////////////////////////////////////
void NES_controller::output_buttons(void)
{

    if (up.is_pressed())
    {
        gpio_set_value(UP_PIN, LOW);
    }
    else
    {
        gpio_set_value(UP_PIN, HIGH);
    }
    
    if (down.is_pressed())
    {
        gpio_set_value(DOWN_PIN, LOW);
    }
    else
    {
        gpio_set_value(DOWN_PIN, HIGH);
    }
    
    if (left.is_pressed())
    {
        gpio_set_value(LEFT_PIN, LOW);
    }
    else
    {
        gpio_set_value(LEFT_PIN, HIGH);
    }
    
    if (right.is_pressed())
    {
        gpio_set_value(RIGHT_PIN, LOW);
    }
    else
    {
        gpio_set_value(RIGHT_PIN, HIGH);
    }
    
    if (a.is_pressed())
    {
        gpio_set_value(A_PIN, LOW);
    }
    else
    {
        gpio_set_value(A_PIN, HIGH);
    }
    
    if (b.is_pressed())
    {
        gpio_set_value(B_PIN, LOW);
    }
    else
    {
        gpio_set_value(B_PIN, HIGH);
    }
    
    if (select.is_pressed())
    {
        //gpio_set_value(SELECT_PIN, LOW);
    }
    else
    {
        //gpio_set_value(SELECT_PIN, HIGH);
    }
    
    if (start.is_pressed())
    {
        gpio_set_value(START_PIN, LOW);
    }
    else
    {
        gpio_set_value(START_PIN, HIGH);
    }
    
}

void NES_controller::set_all_buttons(uint8_t buttons_byte)
{
    if (buttons_byte & 1)
    {
        // UP WAS PRESSED
        //cout << "UP ";
        up.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // UP WAS NOT PRESSED
        //cout << "   ";
        up.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 2)
    {
        // DOWN WAS PRESSED
        //cout << "DOWN ";
        down.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // DOWN WAS NOT PRESSED
        //cout << "     ";
        down.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 4)
    {
        // LEFT WAS PRESSED
        //cout << "LEFT ";
        left.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // LEFT WAS NOT PRESSED
        //cout << "     ";
        left.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 8)
    {
        // RIGHT WAS PRESSED
        //cout << "RIGHT ";
        right.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // RIGHT WAS NOT PRESSED
        //cout << "      ";
        right.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 16)
    {
        // A WAS PRESSED
        //cout << "A ";
        a.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // A WAS NOT PRESSED
        //cout << "  ";
        a.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 32)
    {
        // B WAS PRESSED
        //cout << "B ";
        b.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // B WAS NOT PRESSED
        //cout << "  ";
        b.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 64)
    {
        // SELECT WAS PRESSED
        //cout << "SELECT ";
        select.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // SELECT WAS NOT PRESSED
        //cout << "       ";
        select.set_button(release_forever, MAX_FRAMES);
    }
    
    if (buttons_byte & 128)
    {
        // START WAS PRESSED
        //cout << "START ";
        start.set_button(press_forever, MAX_FRAMES);
    }
    else
    {
        // START WAS NOT PRESSED
        //cout << "      ";
        start.set_button(release_forever, MAX_FRAMES);
    }
    //cout << endl;
}

