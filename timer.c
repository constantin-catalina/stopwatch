#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/iom16.h>
#include <stdint.h>

#include "timer.h"
#include "digit.h"

void timer_init(){
	unsigned int value = 0x0900;
	OCR1AH = (value >> 8) & 0xFF; // Set the upper byte of OCR1A
	OCR1AL = (value & 0xFF); // Set the lower byte of OCR1A
	TIFR = 0x00; // Clear any pending interrupts
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Set prescaler to 64 and CTC mode
}

void timer_init_interrupts(){
	unsigned int value = 0x0900;
	OCR1AH = (value >> 8) & 0xFF; // Set the upper byte of OCR1A
	OCR1AL = (value & 0xFF); // Set the lower byte of OCR1A
	TIFR = 0x00; // Clear any pending interrupts
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); // Set prescaler to 64 and CTC mode
	TIMSK |= (1 << OCIE1A); // Enable Timer1 Compare Match Interrupt
}

bool timer_match() {
	return ((TIFR & (1 << 4)) != 0);
}

void reset_match() {
	TIFR |= (1 << 4); // Clear the timer match flag
}

volatile unsigned long millis_counter = 0;

ISR(TIMER1_COMPA_vect) {
	millis_counter += 10;
	if(millis_counter >= 60000) { 
		millis_counter = 0;
	}
}

unsigned long get_millis() {
	unsigned long m;
	cli(); 
	m = millis_counter;
	sei();
	return m;
}