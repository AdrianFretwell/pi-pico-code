/*--------------------------------------------------------------------------*/
/*
    @file    rotaryencoder.h
    @author  Adrian Fretwell
    @brief   Implements a simple set of functions for reading one or more
    rotary encoders.
    This code assumes you will use three consecutive GPIO pins in the order
    ENC A, ENC B, and ENC Switch, with ENC A having the lowest number.
*/
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "rotaryencoder.h"

void RotaryEncoder_init(RotaryEncoder_inst_t* rot, bool enabled)
{
    RotaryEncoder_setGpio(rot->encA);
    RotaryEncoder_setGpio(rot->encB);
    RotaryEncoder_setGpio(rot->encSw);
    gpio_set_irq_enabled(rot->encA, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(rot->encB, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(rot->encSw, GPIO_IRQ_EDGE_FALL, true);
    if (enabled) {
        gpio_set_irq_callback(RotaryEncoder_gpioCallback);
        irq_set_enabled(IO_IRQ_BANK0, true);
    }
}

void RotaryEncoder_setGpio(uint gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
}

void RotaryEncoder_gpioCallback(uint gpio, uint32_t events) {
    static uint32_t gpio_state = 0;
    static uint32_t rot_state = 0;
    static uint8_t rot_value = 0;
    RotaryEncoder_inst_t *currentRot = firstRot;
    gpio_state = gpio_get_all();

    while (currentRot) {
        rot_state = gpio_state >> currentRot->encA;
        if (currentRot->sw)
            currentRot->sw = rot_state & 0b100;
        rot_value = rot_state & 0b11;
        if (gpio == currentRot->encA) {
            currentRot->wtgEncB = true;
            if (currentRot->wtgEncA && rot_value == 0)
                currentRot->pos--;
            currentRot->wtgEncA = false;
        }
        if (gpio == currentRot->encB) {
            currentRot->wtgEncA = true;
            if (currentRot->wtgEncB && rot_value == 0)
                currentRot->pos++;
            currentRot->wtgEncB = false;
        }
        currentRot = currentRot->next;
    }
    return;
}

int32_t RotaryEncoder_getPosition(RotaryEncoder_inst_t* rot)
{
    return rot->pos;
}

int32_t RotaryEncoder_getDelta(RotaryEncoder_inst_t* rot)
{
    int32_t rotDelta;
    int32_t rotDeltaTmp;

    rotDeltaTmp = rot->pos;
    rotDelta = rotDeltaTmp - rot->lastDelta;
    rot->lastDelta = rotDeltaTmp;
    return rotDelta;
}

bool RotaryEncoder_getSwitch(RotaryEncoder_inst_t* rot)
{
    if (!rot->sw) {
        rot->sw = 1;
        return true;
    }
    return false;
}
