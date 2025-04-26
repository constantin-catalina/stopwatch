#ifndef DIGIT_H_
#define DIGIT_H_

#define F_CPU 14745600UL

#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom16.h>
#include <stdint.h>
#include <util/delay.h> 

static const uint8_t digitmap[10] = {
	0xC0,
	0xF9,
	0xA4,
	0xB0,
	0x99,
	0x92,
	0x82,
	0xF8,
	0x80,
	0x90
};

void init_digit(); // initialize the port lines
void display_digit(uint8_t digit, bool dp); // display a single digit with or without decimal point
void display_4digit_with_dp(unsigned char digits[], uint8_t dp_position, bool dp_state); // display 4 digits with a decimal point
void clear_digit(); // clear the digit on the module

#endif /* DIGIT_H_ */