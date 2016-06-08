# LightLoopController

This is the Arduino code for the lightloopcontroller of the lightlab. The controller was made for easy and quick access the some of the basic functionalities of the lightloop.

![Alt text](/controllerPhoto.jpg?raw=true)

# Should have
- Flickering of light when switching between scenes

# Nice to have
- Make presets with variating max channel levels
- More cool on/off animations

# Short electronics documentation
The electronics of the controller are quite basic, therefore I haven't made an extensive documentation. This is a list of what should be connected to each pin of the arduino the make this work.

A0		: Pot meter
A1		: simple switch
A2 - A5	: NA
1  - 6 	: Pushbutton
7  - 10	: Leds
11		: effective DMX shield pin
12 - 13 : Leds
+5V		: Use this to create the voltage drop for the switches and buttons
GND		: Use this to ground everything

# Help

For questions send an email to: ID [dot] Lightsupport [at] tue [dot] nl