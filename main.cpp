#include <iostream>
//#include <thread>
#include <stdio.h>
#include <poll.h>
#include <string.h> /* for memset */

using namespace std;



#include "Controller.hpp"
#include "CS_time.hpp"
#include "GPIO.hpp"
#include "FM2.hpp"
#include <unistd.h>

#define WAIT_TIME_U_SEC 14750
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */

//static bool latched = false;
static bool set = false;
//static uint32_t latches = 0;


/*void strobe_thread_function(void) 
{
    unsigned int sel_value = 0;
    unsigned int prev_value = 0;
    
    // Setup comparison value
    gpio_get_value(SELECT_PIN, prev_value);
    while(true) // Loop forever
    {
        gpio_get_value(SELECT_PIN, sel_value);
        if ((sel_value == 0) && (prev_value == 1))
        {
            // A falling edge was detected - previous input is latched
            latched = true;
            set = false;
        }
        else if ((sel_value == 1) && (prev_value == 0))
        {
            // A rising edge was detected - input is unlatched
            latched = false;
        }
        prev_value = sel_value;
    }

}*/

///////////////////////////////////////////////////////////////////////////////
/// The Main function.  For now, this function will serve only to read command
/// line arguments and pass them to the appropriate top level functions.
///
/// @param[in]  argc    An int specifying the command line argument count.
/// @param[in]  argv    An array of char* storing each of the arguments.
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{

    
    
    // Setup Pins
    gpio_export(UP_PIN);
    gpio_set_dir(UP_PIN, OUTPUT_PIN);
    
    gpio_export(DOWN_PIN);
    gpio_set_dir(DOWN_PIN, OUTPUT_PIN);
    
    gpio_export(LEFT_PIN);
    gpio_set_dir(LEFT_PIN, OUTPUT_PIN);
    
    gpio_export(RIGHT_PIN);
    gpio_set_dir(RIGHT_PIN, OUTPUT_PIN);    
    
    gpio_export(A_PIN);
    gpio_set_dir(A_PIN, OUTPUT_PIN);    
    
    gpio_export(B_PIN);
    gpio_set_dir(B_PIN, OUTPUT_PIN);
    
    gpio_export(SELECT_PIN);
    gpio_set_dir(SELECT_PIN, INPUT_PIN);
    gpio_set_edge(SELECT_PIN, FALLING_EDGE);
    int select_fd = gpio_fd_open(SELECT_PIN);
    
    gpio_export(START_PIN);
    gpio_set_dir(START_PIN, OUTPUT_PIN);    
    
    
    // Set all pins high (OFF, active low)
    gpio_set_value(UP_PIN,     HIGH);
    gpio_set_value(DOWN_PIN,   HIGH);
    gpio_set_value(LEFT_PIN,   HIGH);
    gpio_set_value(RIGHT_PIN,  HIGH);
    gpio_set_value(A_PIN,      HIGH);
    gpio_set_value(B_PIN,      HIGH);
    //gpio_set_value(SELECT_PIN, HIGH);
    gpio_set_value(START_PIN,  HIGH);

    
#if 0 // Experimental code to run through the inputs, one at a time
    while (true)
    {
        gpio_set_value(START_PIN, HIGH);
        gpio_set_value(UP_PIN, LOW);
        cout << "UP ON" << endl;
        usleep(1000000);
        
        gpio_set_value(UP_PIN, HIGH);
        gpio_set_value(DOWN_PIN, LOW);
        cout << "DOWN ON" << endl;
        usleep(1000000);
        
        gpio_set_value(DOWN_PIN, HIGH);
        gpio_set_value(LEFT_PIN, LOW);
        cout << "LEFT ON" << endl;
        usleep(1000000);
        
        gpio_set_value(LEFT_PIN, HIGH);
        gpio_set_value(RIGHT_PIN, LOW);
        cout << "RIGHT ON" << endl;
        usleep(1000000);
        
        gpio_set_value(RIGHT_PIN, HIGH);
        gpio_set_value(A_PIN, LOW);
        cout << "A ON" << endl;
        usleep(1000000);
        
        gpio_set_value(A_PIN, HIGH);
        gpio_set_value(B_PIN, LOW);
        cout << "B ON" << endl;
        usleep(1000000);
        
        gpio_set_value(B_PIN, HIGH);
        gpio_set_value(SELECT_PIN, LOW);
        cout << "SELECT ON" << endl;
        usleep(1000000);
        
        gpio_set_value(SELECT_PIN, HIGH);
        gpio_set_value(START_PIN, LOW);
        cout << "START ON" << endl;
        usleep(1000000);
        
    }
#endif

#if 0 // Blind code to play a movie "Blind" or without any input from the NES
    string movie_name ("./Movies/SMB3.fm2");
    string line;
    
    uint8_t byte;
    FM2 movie(movie_name);
    NES_controller nes;
    
    error_enum error = ERR_NONE;
    while (error == ERR_NONE)
    {
        
        start_timer();
        error = movie.advance_line();
        byte = movie.get_data_byte();
        //byte = FM2_to_controller(byte);
        nes.set_all_buttons(byte);
        nes.output_buttons();
        
        //while (get_elapsed_time() < 0.010) // contoller sampled at 60hz
        //{
        //    // do nothing, we are waiting for the next controller cycle.
        //}
        usleep(WAIT_TIME_U_SEC);
    }   
    movie.close();
    
#endif

#if 1 // Code that reads the select line (which has been re-routed to the strobe)
// and updates the controller output based on the strobe.
    string movie_name ("./Movies/MM5Fast.fm2");
    string line;


    uint32_t frame_count = 0;
    uint8_t byte;
    FM2 movie(movie_name);
    NES_controller nes;
    error_enum error = ERR_NONE;
    uint32_t rc;
    //int len;
    char *buf[MAX_BUF];
    
    // Launch a thread which will sit on the strobe line
    /// @todo create strobe_thread_function
    //std::thread strobe_thread;
    //strobe_thread = std::thread(strobe_thread_function); 
    
    // Setup Polling filedescriptor? 
    struct pollfd fdset[1];

    while (error == ERR_NONE)
    {   
        if(set == true)
        {
            // Set the value on the output pins
            error = movie.advance_line();
            byte = movie.get_data_byte();
            nes.set_all_buttons(byte);
            nes.output_buttons();
            set = false;
            //cout << frame_count++ << endl;
            //if (byte != 0)
            //{
            //    nes.print_buttons(true, false);
            //}
        }
        
        // Wait for an interrupt
        memset((void*)fdset, 0, sizeof(fdset));
        fdset[0].fd = select_fd;
        fdset[0].events = POLLPRI | POLLERR;
        
        rc = poll(fdset, 1, POLL_TIMEOUT);   
        if (rc < 0) 
        {
			printf("\npoll() failed!\n");
			return -1;
		}
      
		if (rc == 0) 
		{
			//printf(".");
		}
            
		if (fdset[0].revents & POLLPRI) 
		{
			(void)read(fdset[0].fd, buf, MAX_BUF);
			set = true;
		}

        lseek(fdset[0].fd, 0, SEEK_SET);
    }
    
#endif
    // DONE
    return 0;
}




/*
struct pollfd fdset[1];
memset((void*)fdset, 0, sizeof(fdset));
fdset[0].fd = fd;
fdset[0].events = POLLPRI | POLLERR;
...
poll()
...
lseek(fdset[0].fd, 0, SEEK_SET);
const ssize_t rc = read(fdset[0].fd, buf, MAX_BUF);
*/

