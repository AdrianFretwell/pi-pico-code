/*-------------------------------------------------------------------------*/
/*
    @file    main.c
    @author  Adrian Fretwell
    @brief   Implements a simple test of the rotary encoder functions.

*/
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "rotaryencoder.h"

//define rotary encoder GPIOs
#define ROT1_A 10
#define ROT1_B 11
#define ROT1_SW 12
#define ROT2_A 13
#define ROT2_B 14
#define ROT2_SW 15

bool display_timer_fired = false;
RotaryEncoder_inst_t *firstRot = NULL;

int main() {
    // Initialise the encoder structures
    RotaryEncoder_inst_t rot2 = {ROT2_A, ROT2_B, ROT2_SW, false, false, 0, 0, 4, NULL}; // second rotary encoder
    RotaryEncoder_inst_t rot1 = {ROT1_A, ROT1_B, ROT1_SW, false, false, 0, 0, 4, &rot2}; // first rotary encoder
    firstRot = &rot1;

    // Enable uart so we can use printf for debugging
    stdio_init_all();

    // Only need to set enabled to true for one of the encoders
    // this sets up the interrupts but no need to call it more than once.
    RotaryEncoder_init(&rot1, true);
    RotaryEncoder_init(&rot2, false);
    printf("Rotary Encoder test started.");

    // update serial port with encoder status every 500 ms
    while (1) {
        sleep_ms(500);
        printf("Encoder Positions\n");
        printf("Encoder 1: %d\n", rot1.pos);
        printf("Encoder 2: %d\n\n", rot2.pos);
        printf("Encoder Deltas\n");
        printf("Encoder 1: %d\n", RotaryEncoder_getDelta(&rot1));
        printf("Encoder 2: %d\n\n", RotaryEncoder_getDelta(&rot2));
        printf("Encoder Switches\nEncoder 1: ");
        if (RotaryEncoder_getSwitch(&rot1)) {
            printf("Pressed");
        }
        printf("\nEncoder 2: ");
        if (RotaryEncoder_getSwitch(&rot2)) {
            printf("Pressed");
        }
        printf("\n======================================\n\n");
    }
}
