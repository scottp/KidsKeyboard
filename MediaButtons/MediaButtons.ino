
/* 
 Kids Keyboard - Scott Penrose (c) 2012
 http://scott.dd.com.au/
 https://github.com/scottp/KidsKeyboard
 
 Versions:
 2012-05-05 Initial release
 2012-05-06 Better buttons
 
 Buttons to USB Keyboard Example - Special Media Player Keys
 
 You must select Keyboard from the "Tools > USB Type" menu
 
 This example code is in the public domain.
 
 0    left
 1    up
 2    right
 3    down
 
 15     Blue       Back and X
 21	Yellow     (spare)
 14	Green      Volume up 
 20	Black      RUN Boxee
 18	Pink       RUN Plex
 13	White      Volume down
 16	Aqua       OK/Go
 17	L green    (spare)
 19	Red        Space (starrt/stop)
 
 TODO
 	- Combine Back (ESC) and Yellow (X)
 	- Make sure (some how) Boxee goes full screen
 	- How to jump to things in Plex - e.g. ABC for Kids
 	- How to jump to things in Boxee - e.g. My little pony
 
 Multiple Modes
 	- Switch / Button input to change mode
 	- Modes e.g.
 	  	. TV
 		. Game XYZ
 
 */

#include <Bounce.h>

Bounce buttonLEFT = Bounce(0, 10);
Bounce buttonUP = Bounce(1, 10);
Bounce buttonRIGHT = Bounce(2, 10);
Bounce buttonDOWN = Bounce(3, 10);

Bounce button_Blue = Bounce(15, 10);
Bounce button_Yellow = Bounce(21, 10);
Bounce button_Green = Bounce(14, 10);
Bounce button_Black = Bounce(20, 10);
Bounce button_Pink = Bounce(18, 10);
Bounce button_White = Bounce(13, 10);
Bounce button_Aqua = Bounce(16, 10);
Bounce button_LGreen = Bounce(17, 10);
Bounce button_Red = Bounce(19, 10);

void setup() {
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  pinMode(21, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
}

bool joystickActive = false;      // Prevent Left & Up operating together (kids getting confused)
void loop() {

  // Joystick
  buttonLEFT.update();
  buttonUP.update();
  buttonRIGHT.update();
  buttonDOWN.update();

  // Buttons
  button_Blue.update();
  button_Yellow.update();
  button_Green.update();
  button_Black.update();
  button_Pink.update();
  button_White.update();
  button_Aqua.update();
  button_LGreen.update();
  button_Red.update();

  // Long press - e.g. click and hold joystick

  if (! joystickActive) {
    // Prevent two at once, by using active, and usin 'else' to check
    if (buttonLEFT.fallingEdge()) {
      Keyboard.set_key1(KEY_LEFT);
      Keyboard.send_now();	// send the button press
      joystickActive = true;
    }
    else if (buttonRIGHT.fallingEdge()) {
      Keyboard.set_key1(KEY_RIGHT);
      Keyboard.send_now();	// send the button press
      joystickActive = true;
    }
    else if (buttonUP.fallingEdge()) {
      Keyboard.set_key1(KEY_UP);
      Keyboard.send_now();	// send the button press
      joystickActive = true;
    }
    else if (buttonDOWN.fallingEdge()) {
      Keyboard.set_key1(KEY_DOWN);
      Keyboard.send_now();	// send the button press
      joystickActive = true;
    }
  }

  if (
  buttonLEFT.risingEdge()
    || buttonRIGHT.risingEdge()
    || buttonUP.risingEdge()
    || buttonDOWN.risingEdge()
    ) {
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button press
    joystickActive = false;
  }

  // Single Press

  // Volume
  if (button_Green.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_VOLUME_INC);
    Keyboard.send_now();	// send the button press
    Keyboard.set_media(0);
    Keyboard.send_now();	// send the button release
  }
  if (button_White.fallingEdge()) {
    Keyboard.set_media(KEY_MEDIA_VOLUME_DEC);
    Keyboard.send_now();	// send the button press
    Keyboard.set_media(0);
    Keyboard.send_now();	// send the button release
  }

  // Escape / Back
  if (button_Blue.fallingEdge()) {
    Keyboard.set_key1(KEY_ESC);
    Keyboard.send_now();	// send the button press
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button release
    Keyboard.set_key1(KEY_X);
    Keyboard.send_now();	// send the button press
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button release
  }

  if (button_Yellow.fallingEdge()) {
  }

  // Play/Pause
  if (button_Red.fallingEdge()) {
    Keyboard.set_key1(KEY_SPACE);
    Keyboard.send_now();	// send the button press
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button release
  }

  // OK
  if (button_Aqua.fallingEdge() || button_LGreen.fallingEdge()) {
    Keyboard.set_key1(KEY_ENTER);
    Keyboard.send_now();	// send the button press
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button release
  }

  // STARTU APPS
  if (button_Black.fallingEdge()) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_GUI);
    Keyboard.set_key1(KEY_B);
    Keyboard.send_now();	// send the button press
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button release
  }
  if (button_Pink.fallingEdge()) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_GUI);
    Keyboard.set_key1(KEY_P);
    Keyboard.send_now();	// send the button press
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();	// send the button release
  }

}





