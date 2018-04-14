#include <stdint.h>
#include <string.h>
#include "catch.hpp"
#include "./../FM2.hpp"

using namespace std;

TEST_CASE("FM2::FM2", "[FM2][advance_line][get_current_line][get_data_byte]") 
{
    string movie_name ("./fm2_test.fm2");
    string line;
    
    SECTION("get_data_byte no conversion")
    {
        uint8_t byte;
        FM2 movie(movie_name);
        
        // Nothin pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 0);
        
        // Right pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 8);
        
        // Left pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 4);
        
        // Down pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 2);
        
        // Up pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 1);
        
        // Start pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 128);
        
        // Select pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 64);
        
        // B pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 32);
        
        // A pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 16);
        
        movie.close();
    }
    
    SECTION("get_data_byte conversion")
    {
        uint8_t byte;
        FM2 movie(movie_name);
        
        // Nothin pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == 0);
        
        // Right pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(1));
        
        // Left pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(2));
        
        // Down pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(4));
        
        // Up pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(8));
        
        // Start pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(16));
        
        // Select pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(32));
        
        // B pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(64));
        
        // A pressed
        movie.advance_line();
        byte = movie.get_data_byte();
        CHECK(byte == FM2_to_controller(128));
        
        movie.close();
    }
    
    SECTION("FM2_to_controller()")
    {
        uint8_t FM2_Up = 8;
        uint8_t FM2_Down = 4;
        uint8_t FM2_Left = 2;
        uint8_t FM2_Right = 1;
        uint8_t FM2_A = 128;
        uint8_t FM2_B = 64;
        uint8_t FM2_Start = 16;
        uint8_t FM2_Select = 32;
        
        uint8_t Con_Up = 1;
        uint8_t Con_Down = 2;
        uint8_t Con_Left = 4;
        uint8_t Con_Right = 8;
        uint8_t Con_A = 16;
        uint8_t Con_B = 32;
        uint8_t Con_Select = 64;
        uint8_t Con_Start = 128;
        
        CHECK(0 == FM2_to_controller(0));
        CHECK(Con_Up == FM2_to_controller(FM2_Up));
        CHECK(Con_Down == FM2_to_controller(FM2_Down));
        CHECK(Con_Left == FM2_to_controller(FM2_Left));
        CHECK(Con_Right == FM2_to_controller(FM2_Right));
        CHECK(Con_A == FM2_to_controller(FM2_A));
        CHECK(Con_B == FM2_to_controller(FM2_B));
        CHECK(Con_Select == FM2_to_controller(FM2_Select));
        CHECK(Con_Start == FM2_to_controller(FM2_Start));
        
        uint8_t Con_byte = 0;
        uint8_t FM2_byte = 0;
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_Up;
        FM2_byte += FM2_Up;
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_Down;
        FM2_byte += FM2_Down; 
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_Left;
        FM2_byte += FM2_Left;
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_Right;
        FM2_byte += FM2_Right;
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_A;
        FM2_byte += FM2_A; 
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_B;
        FM2_byte += FM2_B; 
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_Select;
        FM2_byte += FM2_Select;
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));
        Con_byte += Con_Start;
        FM2_byte += FM2_Start;
        
        CHECK(Con_byte == FM2_to_controller(FM2_byte));        
    }
    
    SECTION("controller_to_FM2()")
    {
        uint8_t FM2_Up = 8;
        uint8_t FM2_Down = 4;
        uint8_t FM2_Left = 2;
        uint8_t FM2_Right = 1;
        uint8_t FM2_A = 128;
        uint8_t FM2_B = 64;
        uint8_t FM2_Start = 16;
        uint8_t FM2_Select = 32;
        
        uint8_t Con_Up = 1;
        uint8_t Con_Down = 2;
        uint8_t Con_Left = 4;
        uint8_t Con_Right = 8;
        uint8_t Con_A = 16;
        uint8_t Con_B = 32;
        uint8_t Con_Select = 64;
        uint8_t Con_Start = 128;
        
        CHECK(0 == controller_to_FM2(0));
        CHECK(FM2_Up == controller_to_FM2(Con_Up));
        CHECK(FM2_Down == controller_to_FM2(Con_Down));
        CHECK(FM2_Left == controller_to_FM2(Con_Left));
        CHECK(FM2_Right == controller_to_FM2(Con_Right));
        CHECK(FM2_A == controller_to_FM2(Con_A));
        CHECK(FM2_B == controller_to_FM2(Con_B));
        CHECK(FM2_Select == controller_to_FM2(Con_Select));
        CHECK(FM2_Start == controller_to_FM2(Con_Start));
        
        uint8_t Con_byte = 0;
        uint8_t FM2_byte = 0;
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_Up;
        FM2_byte += FM2_Up;
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_Down;
        FM2_byte += FM2_Down; 
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_Left;
        FM2_byte += FM2_Left;
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_Right;
        FM2_byte += FM2_Right;
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_A;
        FM2_byte += FM2_A; 
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_B;
        FM2_byte += FM2_B; 
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_Select;
        FM2_byte += FM2_Select;
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));
        Con_byte += Con_Start;
        FM2_byte += FM2_Start;
        
        CHECK(FM2_byte == controller_to_FM2(Con_byte));        
    }
}


