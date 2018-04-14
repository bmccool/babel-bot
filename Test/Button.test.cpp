#include "catch.hpp"
#include "./../Controller.hpp"

int Factorial( int number ) {
//   return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
 return number <= 1 ? 1      : Factorial( number - 1 ) * number;  // pass
}

TEST_CASE( "Factorial of 0 is 1 (fail)", "[single-file]" ) {
    REQUIRE( Factorial(0) == 1 );
}

TEST_CASE( "Factorials of 1 and higher are computed (pass)", "[single-file]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("Button::Button", "[Button][is_pressed][get_behavior][get_frames]") 
{
    Button test_button;
    
    SECTION("Button")
    {
        // Check that the button is created with the button released...
        CHECK(test_button.is_pressed() == false);
        // And behavior released_forever...
        CHECK(test_button.get_behavior() == release_forever);
        // And that the frame counter is set to MAX_FRAMES
        CHECK(test_button.get_frames() == MAX_FRAMES);
    }
}

TEST_CASE("Button::set_button", "[Button][set_button][is_pressed][get_frames][get_behavior]")
{
    Button test_button;
    
    uint32_t test_error_actual = ERR_NONE;
    uint32_t test_error_expected = ERR_NONE;
    bool test_press_expected = false;
    uint32_t test_frames_expected = MAX_FRAMES;
    uint32_t test_frames_input = MAX_FRAMES;
    button_behavior_enum test_behavior_expected = release_forever;
    button_behavior_enum test_behavior_input = release_forever;
    
    SECTION("release_forever, MAX_FRAMES")
    {
        test_press_expected = false;
        test_behavior_expected = release_forever;
        test_behavior_input = release_forever;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = MAX_FRAMES;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }
    
    SECTION("press_forever, MAX_FRAMES")
    {
        test_press_expected = true;
        test_behavior_expected = press_forever;
        test_behavior_input = press_forever;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = MAX_FRAMES;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }
    
    SECTION("release_after_frames, MAX_FRAMES")
    {
        test_press_expected = true;
        test_behavior_expected = release_after_frames;
        test_behavior_input = release_after_frames;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = MAX_FRAMES;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }    
    
    SECTION("press_after_frames, MAX_FRAMES")
    {
        test_press_expected = false;
        test_behavior_expected = press_after_frames;
        test_behavior_input = press_after_frames;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = MAX_FRAMES;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }    
    
    SECTION("button_behavior_enum_end, MAX_FRAMES")
    {
        test_error_expected = ERR_BUTTON_UNDEFINED_BEHAVIOR;
        test_press_expected = false;
        test_behavior_expected = release_forever;
        test_behavior_input = button_behavior_enum_end;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = MAX_FRAMES;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }
    
    SECTION("release_forever, 0")
    {
        test_press_expected = false;
        test_behavior_expected = release_forever;
        test_behavior_input = release_forever;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = 0;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }
    
    SECTION("press_forever, 0")
    {
        test_press_expected = true;
        test_behavior_expected = press_forever;
        test_behavior_input = press_forever;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = 0;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }
    
    SECTION("release_after_frames, 0")
    {
        test_press_expected = false;
        test_behavior_expected = release_forever;
        test_behavior_input = release_after_frames;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = 0;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }    
    
    SECTION("press_after_frames, 0")
    {
        test_press_expected = true;
        test_behavior_expected = press_forever;
        test_behavior_input = press_after_frames;
        test_frames_expected = MAX_FRAMES;
        test_frames_input = 0;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }    
    
    SECTION("button_behavior_enum_end, 0")
    {
        test_error_expected = ERR_BUTTON_UNDEFINED_BEHAVIOR;
        test_press_expected = DEFAULT_STATE;
        test_behavior_expected = DEFAULT_BEHAVIOR;
        test_behavior_input = button_behavior_enum_end;
        test_frames_expected = DEFAULT_FRAMES;
        test_frames_input = MAX_FRAMES;
        
        test_error_actual = test_button.set_button(test_behavior_input, test_frames_input);        

        CHECK(test_error_actual == test_error_expected);
        CHECK(test_button.is_pressed() == test_press_expected);
        CHECK(test_button.get_frames() == test_frames_expected);
        CHECK(test_button.get_behavior() == test_behavior_expected);
    }    
}

TEST_CASE("Button::is_pressed", "[Button][set_button][is_pressed]") 
{
    Button test_button;
    
    // Release button
    test_button.set_button(release_forever, MAX_FRAMES);
    CHECK(test_button.is_pressed() == false);
    
    // Press button
    test_button.set_button(press_forever, MAX_FRAMES);
    CHECK(test_button.is_pressed() == true);
}

TEST_CASE("Button::get_frames", "[Button][get_frames][set_button][tick]")
{
    Button test_button;
    
    test_button.set_button(release_forever, 10);

    // Test rollover +- 10 frames
    for (uint32_t i = 10; i > 0; i--)
    {
        CHECK(test_button.get_frames() == i);
        test_button.tick();
    }
    for (uint32_t i = MAX_FRAMES; i > MAX_FRAMES - 10; i--)
    {
        CHECK(test_button.get_frames() == i);
        test_button.tick();
    }


}

TEST_CASE("Button::get_behavior", "[Button][get_behavior][set_button]") 
{
    Button test_button;
    
    // release_forever
    test_button.set_button(release_forever, MAX_FRAMES);
    CHECK(test_button.get_behavior() == release_forever);
    
    // press_forever
    test_button.set_button(press_forever, MAX_FRAMES);
    CHECK(test_button.get_behavior() == press_forever);
    
    // press_after_frames
    test_button.set_button(press_after_frames, MAX_FRAMES);
    CHECK(test_button.get_behavior() == press_after_frames);   
    
    // release_after_frames
    test_button.set_button(release_after_frames, MAX_FRAMES);
    CHECK(test_button.get_behavior() == release_after_frames);       
}

