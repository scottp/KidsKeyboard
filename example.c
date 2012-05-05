/* Keyboard example for Teensy USB Development Board
 * http://www.pjrc.com/teensy/usb_keyboard.html
 * Copyright (c) 2008 PJRC.COM, LLC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.

Kids box controller
	Copyright Scott Penrose (c) 2012

Connections:

  Joystick:
	B0 left
	B1 up
	B2 right
	B3 down

  Buttons:
	B6  Blue
	F0	Yellow
	B5	Green
	F1	Black
	F5	Pink
	B4	White
	F7	Aqua
	F6	Light green
	F4	Red

BUGS:
	- Bouncing buttons - need better debounce
	- Media buttons...

 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usb_keyboard.h"

#define LED_CONFIG	(DDRD |= (1<<6))
#define LED_ON		(PORTD &= ~(1<<6))
#define LED_OFF		(PORTD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

uint8_t number_keys[10]=
	{KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9};

uint16_t idle_count=0;

int main(void)
{
	uint8_t b, d, f, mask, i, reset_idle;
	uint8_t b_prev=0xFF, d_prev=0xFF, f_prev=0xFF;

	// set for 16 MHz clock
	CPU_PRESCALE(0);

	// Configure all port B and port D pins as inputs with pullup resistors.
	// See the "Using I/O Pins" page for details.
	// http://www.pjrc.com/teensy/pins.html
	DDRD = 0x00;
	DDRB = 0x00;
	DDRF = 0x00;
	PORTB = 0xFF;
	PORTD = 0xFF;
	PORTF = 0xFF;

	// Initialize the USB, and then wait for the host to set configuration.
	// If the Teensy is powered without a PC connected to the USB port,
	// this will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;

	// Wait an extra second for the PC's operating system to load drivers
	// and do whatever it does to actually be ready for input
	_delay_ms(1000);

	// Configure timer 0 to generate a timer overflow interrupt every
	// 256*1024 clock cycles, or approx 61 Hz when using 16 MHz clock
	// This demonstrates how to use interrupts to implement a simple
	// inactivity timeout.
	TCCR0A = 0x00;
	TCCR0B = 0x05;
	TIMSK0 = (1<<TOIE0);

	while (1) {
		// read all port B and port D pins
		b = PINB;
		d = PIND;
		f = PINF;

		// check if any pins are low, but were high previously
		mask = 1;
		reset_idle = 0;
		for (i=0; i<8; i++) {
			if (((b & mask) == 0) && (b_prev & mask) != 0) {
				//usb_keyboard_press(KEY_B, KEY_SHIFT);
				//usb_keyboard_press(number_keys[i], 0);
				switch (i) {
					case 0:
						usb_keyboard_press(KEY_LEFT, 0);
						break;
					case 1:
						usb_keyboard_press(KEY_UP, 0);
						break;
					case 2:
						usb_keyboard_press(KEY_RIGHT, 0);
						break;
					case 3:
						usb_keyboard_press(KEY_DOWN, 0);
						break;
					default:
						usb_keyboard_press(KEY_B, KEY_SHIFT);
						usb_keyboard_press(number_keys[i], 0);
						break;
				}
				
				reset_idle = 1;
			}
			if (((d & mask) == 0) && (d_prev & mask) != 0) {
				usb_keyboard_press(KEY_D, KEY_SHIFT);
				usb_keyboard_press(number_keys[i], 0);
				reset_idle = 1;
			}
			if (((f & mask) == 0) && (f_prev & mask) != 0) {
				usb_keyboard_press(KEY_F, KEY_SHIFT);
				usb_keyboard_press(number_keys[i], 0);
				reset_idle = 1;
			}
			mask = mask << 1;
		}
		// if any keypresses were detected, reset the idle counter
		if (reset_idle) {
			// variables shared with interrupt routines must be
			// accessed carefully so the interrupt routine doesn't
			// try to use the variable in the middle of our access
			cli();
			idle_count = 0;
			sei();
		}
		// now the current pins will be the previous, and
		// wait a short delay so we're not highly sensitive
		// to mechanical "bounce".
		b_prev = b;
		d_prev = d;
		f_prev = f;
		_delay_ms(2);
	}
}

// This interrupt routine is run approx 61 times per second.
// A very simple inactivity timeout is implemented, where we
// will send a space character.
ISR(TIMER0_OVF_vect)
{
	idle_count++;
	if (idle_count > 61 * 8) {
		idle_count = 0;
		usb_keyboard_press(KEY_SPACE, 0);
	}
}


