/*
 * Implement the following routines to set GPIO pins to input or output,
 * and to read (input) and write (output) them.
 *
 * DO NOT USE loads and stores directly: only use GET32 and PUT32 
 * to read and write memory.  Use the minimal number of such calls.
 *
 * See rpi.h in this directory for the definitions.
 */
#include "rpi.h"
#include <stdint.h>

// see broadcomm documents for magic addresses.
#define GPIO_BASE 0x20200000
static const unsigned gpio_set0  = (GPIO_BASE + 0x1C);
static const unsigned gpio_clr0  = (GPIO_BASE + 0x28);
static const unsigned gpio_lev0  = (GPIO_BASE + 0x34);

//
// Part 1 implement gpio_set_on, gpio_set_off, gpio_set_output
//

// set <pin> to be an output pin.  
//
// note: fsel0, fsel1, fsel2 are contiguous in memory, so you 
// can (and should) use array calculations!
void gpio_set_output(unsigned pin) {
    // implement this
    // use <gpio_fsel0>

    unsigned input_bits = 0b001;

    // 1. compute the right register number
    unsigned reg_n = pin / 10;

    // 2. compute the local position
    unsigned local_number = pin % 10;

    // 3. compute the bit offset
    unsigned offset = local_number * 3;

    // 4. compute the target address
    unsigned target_addr = GPIO_BASE + reg_n * 4;

    // 5. get and update current value
    unsigned current_bits = GET32(target_addr) | input_bits << offset;

    // 6. update 
    PUT32(target_addr, current_bits);
}

// set GPIO <pin> on.
void gpio_set_on(unsigned pin) {
    // implement this
    // use <gpio_set0>
    
    // GPIO adresses are 0x20200000 (GPIO_BASE)
    // The adress to set a GPIO is 0x2020001C (gpio_set0)
    // To set the GPIO(n) pin, we have to use the nth bit
    // 
    PUT32(gpio_set0, 1 << pin);
}

// set GPIO <pin> off
void gpio_set_off(unsigned pin) {
    // implement this
    // use <gpio_clr0>
    PUT32(gpio_clr0, 1 << pin);
}

// set <pin> to <v> (v \in {0,1})
void gpio_write(unsigned pin, unsigned v) {
    if(v)
       gpio_set_on(pin);
    else
       gpio_set_off(pin);
}

//
// Part 2: implement gpio_set_input and gpio_read
//

// set <pin> to input.
void gpio_set_input(unsigned pin) {
    // implement.
}

// return the value of <pin>
int gpio_read(unsigned pin) {
    unsigned v = 0;

    // implement.
    return v;
}
