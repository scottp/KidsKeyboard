KidsKeyboard
============

Kids keyboard for controlling Media Centre - rugged and easy to use.

I have two versions. The Arduino (Teensyduino) version which is working now in
MediaButtons/MediaButtons.ino. And the AVR C version - example.c and supporting
files.

Current
-------
Current version is hardwired using an Teensy 2.0. My original version used a
3.3V mega and Bluetooth module, and a numchuck - it used gestures to control
the TV. The plan was to build a bluetooth box for the kids with solar panel for
charging. I have gone with the Teensy for simplicity (no battery, no charger,
and mostly no Bluetooht reconnect issues).

Hardware
--------
My original version uses a single analogue input (resistor network). Today
though I have decided to use straight analog inputs, pull up resistors
(internal) and a common ground. Pins are all indicated in the code.

Just connect all one side to ground, the others to each digital input you want.
Easy.

MediaButtons/MediaButtons.ino
-----------------------------
* Teensyduino version
	Teensyduino is a plutin for Arduuino IDE that allows you 
	to use arduino code style.
* This code is working now

exampe.c
--------
* AVR C version.
* Had trouble getting Media buttons to work
* Works, but not what I am currently using
