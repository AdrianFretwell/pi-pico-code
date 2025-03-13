/*-------------------------------------------------------------------------*/
/*
    @file    rotaryencoder.h
    @author  Adrian Fretwell
    @brief   Implements a simple set of functions for reading one or more
    rotary encoders.
    This code assumes you will use three consecutive GPIO pins in the order
    ENC A, ENC B, and ENC Switch with ENC A having the lowest number.
*/
/*--------------------------------------------------------------------------*/

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <stdint.h>

// This struct represents and instance of an encoder
typedef struct RotaryEncoder_inst_t RotaryEncoder_inst_t;
struct RotaryEncoder_inst_t {
    uint8_t encA;
    uint8_t encB;
    uint8_t encSw;
    bool wtgEncA;
    bool wtgEncB;
    int32_t pos;
    int32_t lastDelta;
    uint8_t sw;
    RotaryEncoder_inst_t *next;
};

extern RotaryEncoder_inst_t *firstRot;
void RotaryEncoder_init(RotaryEncoder_inst_t* rot, bool enabled);
int32_t RotaryEncoder_getPosition(RotaryEncoder_inst_t* rot);
int32_t RotaryEncoder_getDelta(RotaryEncoder_inst_t* rot);
bool RotaryEncoder_getSwitch(RotaryEncoder_inst_t* rot);
void RotaryEncoder_setGpio(uint gpio);
void RotaryEncoder_gpioCallback(uint gpio, uint32_t events);

#endif // ROTARYENCODER_H
