/*
 * digit.c
 *
 * Created: 4/2/2025 4:56:49 PM
 *  Author: dspuser
 */ 

#include "digit.h"

void init_digit(){
	DDRA |= 0xFF;
	DDRB |= 0X0F;
}

void display_digit(uint8_t digit, bool dp){
	if(dp){
		PORTA = ~(digitmap[digit] & 0x7F);
	}
	else {
		PORTA = ~digitmap[digit];
	}
}

void display_4digit_with_dp(unsigned char digits[], uint8_t dp_position, bool dp_state){
	for(int i=0; i<4; i++){
		PORTB = (1<<i);
		if(i == dp_position && dp_state){
			display_digit(digits[i], true);
		} else {
			display_digit(digits[i], false);
		}
		_delay_ms(1);
	}
}

void clear_digit(){
	PORTA &= 0x00;
}

