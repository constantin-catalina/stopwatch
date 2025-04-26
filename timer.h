/*
 * timer.h
 *
 * Created: 4/2/2025 4:05:24 PM
 *  Author: dspuser
 */ 

#ifndef TIMER_H_
#define TIMER_H_

#include <stdbool.h>

#define LED_PIN PB0

void timer_init();
void timer_init_interrupts();

bool timer_match();
void reset_match();

unsigned long get_millis(); 

#endif /* TIMER_H_ */
