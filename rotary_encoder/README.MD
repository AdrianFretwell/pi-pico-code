# Rotary Encoder

This sub section contains details of a set of C language functions and structs that allows one or more rotary encoded to be "plugged in" to a project.

The encoders used are the inexpensive [PEC11 series](https://cdn-shop.adafruit.com/datasheets/pec11.pdf).  These encoders also have a push button action
for a momentary switch.

Below is an image of a pico-w with serial lines attached and a ribbon connecting a lashed up board with two rotary encoders on it.
![rotary_encoder](https://github.com/AdrianFretwell/pi-pico-code/blob/main/assets/rotary_encoder.jpg)

main.c is a simple test that continuously displais the status of the two encoders via a serial connection.
