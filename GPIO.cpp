///////////////////////////////////////////////////////////////////////////////
/// @file GPIO.cpp
/// This file contains functions for interfacing with the GPIO hardware.
///
///////////////////////////////////////////////////////////////////////////////

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

/////////////////////////// PROJECT INCLUDES   ////////////////////////////////
#include "GPIO.hpp"
#include "Error.hpp"

///////////////////////////////////////////////////////////////////////////////
/// This function will export the specified GPIO pin to userspace, meaning it
/// will be available to modify via the otehr functions in this module.
/// 
/// @param[in]  gpio    The GPIO number specifying which pin should be 
///                     exported.
///
/// @return Returns an error_enum type indicating success or failure.
///////////////////////////////////////////////////////////////////////////////
error_enum gpio_export(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

    // Attempt to open the export file for write only
	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0)
	{
		// If the open fails, return error
		perror("gpio_export() Cannot export pin!");
		return ERR_GPIO_EXPORT_ERROR;
	}
    
    // If the open is successful, write the GPIO number to the export file
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	
	// Close the export file and return.
	close(fd);
	return ERR_NONE;
}

///////////////////////////////////////////////////////////////////////////////
/// This function will unexport the specified GPIO pin, removing it from 
/// userspace.
/// 
/// @param[in]  gpio    The GPIO number specifying which pin should be 
///                     unexported.
/// @return Returns an error_enum type indicating success or failure.
///////////////////////////////////////////////////////////////////////////////
error_enum gpio_unexport(unsigned int gpio)
{
	int fd, len;
	char buf[MAX_BUF];

    // Attempt to open the unexport file for write only
	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd < 0) 
	{
		// If the open fails, return error
		perror("gpio_unexport() cannot unexport pin!");
		return ERR_GPIO_UNEXPORT_ERROR;
	}

    // If the open is successful, write the GPIO number to the unexport file
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	write(fd, buf, len);
	
	// Close the unexport file and return
	close(fd);
	return ERR_NONE;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows the caller to set the direction of a pin that has
/// been previously exported.
/// 
/// @param[in]  gpio    The GPIO number specifying which pin should be 
///                     modified.
/// @param[in]	out_flag	The new direction of the pin.
///
/// @return Returns an error_enum type indicating success or failure.
///////////////////////////////////////////////////////////////////////////////
error_enum gpio_set_dir(unsigned int gpio, PIN_DIRECTION out_flag)
{
	int fd;
	char buf[MAX_BUF];

	// Attempt to open the direction file of the GPIO pin.
	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
   	fd = open(buf, O_WRONLY);
	
	if (fd < 0) 
	{
		// If the open fails, return error.
		perror("gpio_set_dir() cannot set direction!");
		return ERR_GPIO_SET_DIR_ERROR;
	}

    // Write the cooresponding direction to the direction file.
	if (out_flag == OUTPUT_PIN)
		write(fd, "out", 4);
	else
		write(fd, "in", 3);

    // Close the direction file and return
	close(fd);
	return ERR_NONE;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows 
///////////////////////////////////////////////////////////////////////////////
int gpio_set_value(unsigned int gpio, PIN_VALUE value)
{
	int fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return fd;
	}

	if (value==LOW)
		write(fd, "0", 2);
	else
		write(fd, "1", 2);

	close(fd);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows
///////////////////////////////////////////////////////////////////////////////
int gpio_get_value(unsigned int gpio, unsigned int & value)
{
	int fd;
	char buf[MAX_BUF];
	char ch;

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perror("gpio/get-value");
		return fd;
	}

	read(fd, &ch, 1);

	if (ch != '0') {
		value = 1;
	} else {
		value = 0;
	}

	close(fd);
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
/// This function allows th
///////////////////////////////////////////////////////////////////////////////

int gpio_set_edge(unsigned int gpio, PIN_EDGE edge)
{
	int fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-edge");
		return fd;
	}

    if (edge == RISING_EDGE)
    {
	    write(fd, "rising", 6); /* len("rising") == 6 */
    }
    else if (edge == FALLING_EDGE)
    {
	    write(fd, "falling", 7); /* len("falling") == 7 */
    }
    else
    {
    	/// @todo ERROR!
    }
	close(fd);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allows the
///////////////////////////////////////////////////////////////////////////////
int gpio_fd_open(unsigned int gpio)
{
	int fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

///////////////////////////////////////////////////////////////////////////////
/// This function allo
///////////////////////////////////////////////////////////////////////////////

int gpio_fd_close(int fd)
{
	return close(fd);
}
