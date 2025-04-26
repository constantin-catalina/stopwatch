#define F_CPU 14745600UL

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/iom16.h>
#include <util/delay.h>
#include <stdbool.h>

#include "timer.h"
#include "digit.h"

/*
Connections:
PA0 - SEG A
PA1 - SEG B
PA2 - SEG C
PA3 - SEG D
PA4 - SEG E
PA5 - SEG F
PA6 - SEG G
PA7 - DP

PB0 - CC1
PB1 - CC2
PB2 - CC3
PB3 - CC4

PD0 - PB0 (button)
*/

#define BUTTON_PIN PD0
#define DEBOUNCE_DELAY 10

void init_button() {
	DDRD &= ~(1 << BUTTON_PIN); 
	PORTD |= (1 << BUTTON_PIN); 
}

bool is_button_pressed() {
	if (!(PIND & (1 << BUTTON_PIN))) { 
		_delay_ms(DEBOUNCE_DELAY); 
		if (!(PIND & (1 << BUTTON_PIN))) { 
			return true; 
		}
	}
	return false;
}

volatile bool stopwatchRunning = false;
volatile unsigned long stopwatchValue = 0;
volatile unsigned long lastButtonPress = 0;
volatile unsigned long startTime = 0;
volatile unsigned long elapsedTime = 0;

int main(void){
	unsigned char digits[4];
	unsigned int seconds, milliseconds;
	unsigned long current_time;

	bool dp_state = false;
	unsigned long last_dp_toggle = 0;

	bool button_state = false;
	bool last_button_state = false;

	init_digit();
	init_button();
	timer_init_interrupts();
	sei();

    while(1){
		current_time = get_millis();

		button_state = is_button_pressed();

		if (button_state && !last_button_state) {
			stopwatchRunning = !stopwatchRunning;
			if (stopwatchRunning) {
				startTime = current_time; 
			} 
		}

		last_button_state = button_state;

		if(stopwatchRunning){
			if (current_time >= startTime) {
				stopwatchValue = elapsedTime + (current_time - startTime);
			} else {
				stopwatchValue = elapsedTime + (60000 - startTime) + current_time;
			}		
		}
		else {
			elapsedTime = stopwatchValue;
		}

		if(stopwatchValue >= 60000) {
			stopwatchValue = 0; 
			elapsedTime = 0;
			startTime = current_time; 
		}

		seconds = (stopwatchValue / 1000) % 60; // 0-59 seconds
		milliseconds = stopwatchValue % 1000; // 0-999 milliseconds
		
		digits[0] = seconds / 10;
		digits[1] = seconds % 10;
		digits[2] = milliseconds / 100;
		digits[3] = (milliseconds /10) % 10;

		if(current_time - last_dp_toggle >= 500) {
			dp_state = !dp_state; 
			last_dp_toggle = current_time;
		}

		display_4digit_with_dp(digits, 1, dp_state);			
	}
}


