#include <stdint.h>
#include "catch.hpp"
#include "./../GPIO.hpp"
#include "./../Controller.hpp"


TEST_CASE("NES_controller::set_button", "[NES_controller][set_button][get_buttons][button_tick]") 
{
    SECTION("release_after_frames")
    {
        error_enum error_expected = ERR_NONE;
        error_enum error_actual = ERR_NONE;
        NES_controller nes;
        uint8_t buttons_test = 0x00;
        
        
        CHECK(nes.get_buttons() == buttons_test);
        
        error_actual = nes.set_button(nes_up,     release_after_frames, 1);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 0)));
        CHECK(nes.get_frames(nes_up) == 1);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_down,   release_after_frames, 2);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 1)));
        CHECK(nes.get_frames(nes_down) == 2);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_left,   release_after_frames, 3);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 2)));
        CHECK(nes.get_frames(nes_left) == 3);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_right,  release_after_frames, 4);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 3)));
        CHECK(nes.get_frames(nes_right) == 4);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_a,      release_after_frames, 5);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 4)));
        CHECK(nes.get_frames(nes_a) == 5);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_b,      release_after_frames, 6);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 5)));
        CHECK(nes.get_frames(nes_b) == 6);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_select, release_after_frames, 7);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 6)));
        CHECK(nes.get_frames(nes_select) == 7);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.set_button(nes_start,  release_after_frames, 8);
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 7)));
        CHECK(nes.get_frames(nes_start) == 8);
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 0)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 1)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 2)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 3)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 4)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 5)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 6)));
        CHECK(error_actual == error_expected);
        
        error_actual = nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test ^= (1 << 7)));
        CHECK(error_actual == error_expected);
    }
    
    SECTION("press_after_frames")
    {
        NES_controller nes;
        nes.set_button(nes_up,     press_after_frames, 1);
        nes.set_button(nes_down,   press_after_frames, 2);
        nes.set_button(nes_left,   press_after_frames, 3);
        nes.set_button(nes_right,  press_after_frames, 4);
        nes.set_button(nes_a,      press_after_frames, 5);
        nes.set_button(nes_b,      press_after_frames, 6);
        nes.set_button(nes_select, press_after_frames, 7);
        nes.set_button(nes_start,  press_after_frames, 8);
        
        uint8_t buttons_test = 0x00;
        CHECK(nes.get_buttons() == buttons_test);
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 0)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 1)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 2)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 3)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 4)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 5)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 6)));
        
        nes.button_tick();
        CHECK(nes.get_buttons() == (buttons_test |= (1 << 7)));
    }
}
