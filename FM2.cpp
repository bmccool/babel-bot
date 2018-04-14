///////////////////////////////////////////////////////////////////////////////
/// @file FM2.cpp
/// This file contains functions for interfacing with the FM2 class.
///
///////////////////////////////////////////////////////////////////////////////

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <stdint.h>
#include <iostream>
#include <fstream>
/////////////////////////// PROJECT INCLUDES   ////////////////////////////////
#include "FM2.hpp"
#include "Error.hpp"
#include "Controller.hpp"

using namespace std;
/////////////////////////// CLASS DEFINITIONS /////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// The Constructor for FM2 class.  The constructor requires a filename to be
/// associated with the class instance.
///////////////////////////////////////////////////////////////////////////////
FM2::FM2(string & movie_name)
{
    stream.open (movie_name.c_str());  // Open the movie file.
    if (stream.is_open())
    {
        return;
    }
    else cout << "ERR: Unable to open file";
    return;
}

///////////////////////////////////////////////////////////////////////////////
/// This function will close the stream associated with this class.  It would
/// be nice if this could be included in the destructor, but I haven't figured
/// out a way to do that.  It should be simple.
///////////////////////////////////////////////////////////////////////////////
void FM2::close()
{
    stream.close();
}
///////////////////////////////////////////////////////////////////////////////
/// This function allows the caller to read the current line in the class.
/// This is the raw text from the movie file.
///
/// @param[in/out] line A string that is used to pass back the current line.
///////////////////////////////////////////////////////////////////////////////
void FM2::get_line_current(string & line)
{
    line = line_current;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows the caller to read the current line in the class.
/// This is the raw text from the movie file.
///
/// @return Returns a bool indicating if line_current is frame_data or not.
///////////////////////////////////////////////////////////////////////////////
bool FM2::is_frame_data()
{
    if (line_current[0] == '|')
    {
        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
/// This function will advance line_current to the next line that has valid
/// frame data.
///////////////////////////////////////////////////////////////////////////////
error_enum FM2::advance_line()
{
    do
    {
        getline(stream, line_current);
        /// @todo There should be some sort of check here against end of file conditions
        
        if (stream.eof()) 
        {
            cout << "END OF FILE REACHED!" << endl;
            return ERR_FM2_END_OF_FILE;
        }
        if (stream.bad()) 
        {
            cout << "io error!";
            return ERR_FM2_IO_ERROR;
        }
        
    }while (is_frame_data() == false);
    

    return ERR_NONE;
}

///////////////////////////////////////////////////////////////////////////////
/// This function returns the current frame data in the form of a byte.  8-bits
/// for four d-pad directions and four buttons.
///
/// @return Returns a uint8_t byte that corresponds to the state of each button
///////////////////////////////////////////////////////////////////////////////
uint8_t FM2::get_data_byte()
{
    // Assuming data lines follow the format "|0|RLDUTSBA|........||"
    // Where the relevent controller information is located between the second
    // and third pipes, locations [3-10], and each letter corresponds to a
    // button being pressed for that frame.
    // R    Right
    // L    Left
    // D    Down
    // U    Up
    // T    Start
    // S    Select
    // B    B
    // A    A
    
    // We will be converting this to the format
    // typedef struct
    // {
    //     uint8_t up     : 1;
    //     uint8_t down   : 1;
    //     uint8_t left   : 1;
    //     uint8_t right  : 1;
    //     uint8_t a      : 1;
    //     uint8_t b      : 1;
    //     uint8_t select : 1;
    //     uint8_t start  : 1;
    // } NES_buttons_status_bits;
    
    NES_buttons_status_union buttons;
    buttons.byte = 0;
    
    if (line_current[3]  == 'R') buttons.bits.right  = 1;
    if (line_current[4]  == 'L') buttons.bits.left   = 1;
    if (line_current[5]  == 'D') buttons.bits.down   = 1;
    if (line_current[6]  == 'U') buttons.bits.up     = 1;
    if (line_current[7]  == 'T') buttons.bits.start  = 1;
    if (line_current[8]  == 'S') buttons.bits.select = 1;
    if (line_current[9]  == 'B') buttons.bits.b      = 1;
    if (line_current[10] == 'A') buttons.bits.a      = 1;
    
    return buttons.byte;
}

///////////////////////////////////////////////////////////////////////////////
/// This function converts a byte that describes the state of each button from
/// the FM2 format to the Controller format.
///
/// @param [in] FM2_byte A uint8_t that describes the state of the buttons in
///                      the FM2 format
///
/// @return Returns a uint8_t byte that corresponds to the state of each
///         button in the Controller format
///////////////////////////////////////////////////////////////////////////////
uint8_t FM2_to_controller(uint8_t FM2_byte)
{
    // Convert from this format:
    // button being pressed for that frame.
    // R    Right  // LEAST SIGNIFICANT
    // L    Left
    // D    Down
    // U    Up
    // T    Start
    // S    Select
    // B    B
    // A    A
    
    // Convert to this format:
    // typedef struct
    // {
    //     uint8_t up     : 1;  LEAST SIGNIFICANT
    //     uint8_t down   : 1;
    //     uint8_t left   : 1;
    //     uint8_t right  : 1;
    //     uint8_t a      : 1;
    //     uint8_t b      : 1;
    //     uint8_t select : 1;
    //     uint8_t start  : 1;
    // } NES_buttons_status_bits;
    
    NES_buttons_status_union buttons;
    buttons.byte = 0;
    
    if (FM2_byte & 0x01) /* Right  */ buttons.bits.right  = 1;
    if (FM2_byte & 0x02) /* Left   */ buttons.bits.left   = 1;
    if (FM2_byte & 0x04) /* Down   */ buttons.bits.down   = 1;
    if (FM2_byte & 0x08) /* Up     */ buttons.bits.up     = 1;
    if (FM2_byte & 0x10) /* Start  */ buttons.bits.start  = 1;
    if (FM2_byte & 0x20) /* Select */ buttons.bits.select = 1;
    if (FM2_byte & 0x40) /* B      */ buttons.bits.b      = 1;
    if (FM2_byte & 0x80) /* A      */ buttons.bits.a      = 1;

    return buttons.byte;    

}

///////////////////////////////////////////////////////////////////////////////
/// This function converts a byte that describes the state of each button from
/// the Controller format to the FM2 format.
///
/// @param [in] controller_byte A uint8_t that describes the state of the 
///                             buttons in the controller forrmat
///
/// @return Returns a uint8_t byte that corresponds to the state of each
///         button in the FM2 format
///////////////////////////////////////////////////////////////////////////////
uint8_t controller_to_FM2(uint8_t controller_byte)
{
    // Convert from this format:
    // typedef struct
    // {
    //     uint8_t up     : 1;  LEAST SIGNIFICANT
    //     uint8_t down   : 1;
    //     uint8_t left   : 1;
    //     uint8_t right  : 1;
    //     uint8_t a      : 1;
    //     uint8_t b      : 1;
    //     uint8_t select : 1;
    //     uint8_t start  : 1;
    // } NES_buttons_status_bits;

    // Convert to this format:
    // button being pressed for that frame.
    // R    Right  // LEAST SIGNIFICANT
    // L    Left
    // D    Down
    // U    Up
    // T    Start
    // S    Select
    // B    B
    // A    A
    

    
    NES_buttons_status_union buttons;
    buttons.byte = controller_byte;
    uint8_t output = 0;
    
    if (buttons.bits.right)  /* Right   */ output += 1;
    if (buttons.bits.left)   /* Left    */ output += 2;
    if (buttons.bits.down)   /* Down    */ output += 4;
    if (buttons.bits.up)     /* Up      */ output += 8;
    if (buttons.bits.start)  /* Start   */ output += 16;
    if (buttons.bits.select) /* Select  */ output += 32;
    if (buttons.bits.b)      /* B       */ output += 64;
    if (buttons.bits.a)      /* A       */ output += 128;

    return output;    

}