///////////////////////////////////////////////////////////////////////////////
/// @file FM2.hpp
/// This file contains header information for the file FM2.cpp.
///
///////////////////////////////////////////////////////////////////////////////
// Make sure this is only included once
#ifndef FM2_HPP
#define FM2_HPP

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <stdint.h>
#include <iostream>
#include <fstream>
/////////////////////////// PROJECT INCLUDES //////////////////////////////////
#include "Error.hpp"

/////////////////////////// DEFINITIONS ///////////////////////////////////////
uint8_t FM2_to_controller(uint8_t FM2_byte);
uint8_t controller_to_FM2(uint8_t Controller_byte);
/////////////////////////// TYPES  ////////////////////////////////////////////

////////////////////////////// CLASS DECLARATION ///////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// A class used for reading and writing the FM2 movie files used to play NES
/// games.
////////////////////////////////////////////////////////////////////////////////
class FM2
{
    std::fstream stream; // The file stream associated with this FM2 movie.
    std::string line_current; // The current line that is being processed.
    uint32_t frame_index;  // The frame index of the current line.
    
    bool is_frame_data(); // Checks if the line_current is frame data or not.

  public:
    FM2(std::string & movie_name); 
    void close(); // Close the stream when we are done with this object
    /// @todo Is there a way we could put this in the destructor for this class?
    error_enum advance_line(); // Advances line_current tothe next valid data frame line
    void get_line_current(std::string & line);  // Returns the current line.
    uint8_t get_data_byte(); // Returns the button presses of the current frame

};

#endif