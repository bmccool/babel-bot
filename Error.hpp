///////////////////////////////////////////////////////////////////////////////
/// @file Error.hpp
/// This header file contains all the error codes for this project and
/// prototypes for any public Error functions.
///
///////////////////////////////////////////////////////////////////////////////
// Make sure this is only included once
#ifndef ERROR_HPP
#define ERROR_HPP

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <stdint.h>

/////////////////////////// DEFINITIONS ///////////////////////////////////////
enum error_enum
{
    ERR_NONE = 0,
    ERR_BUTTON_UNDEFINED_BEHAVIOR,
    ERR_CONTROLLER_UNDEFINED_BUTTON,
    ERR_GPIO_EXPORT_ERROR,
    ERR_GPIO_UNEXPORT_ERROR,
    ERR_GPIO_SET_DIR_ERROR,
    ERR_GPIO_SET_VAL_ERROR,
    ERR_GPIO_GET_VAL_ERROR,
    ERR_FM2_END_OF_FILE,
    ERR_FM2_IO_ERROR
};
/////////////////////////// TYPES  ////////////////////////////////////////////

#endif