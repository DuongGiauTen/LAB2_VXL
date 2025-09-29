/*
 * timer.c
 *
 *  Created on: Sep 28, 2025
 *      Author: my pc
 */
#include "timer.h"



void setTimer1(int duration){
	count = duration/ TICK;
	flag = 0;
}

void timer1Run(){
	if (count > 0) {
		count--;
		if (count == 0){
			flag = 1;
		}
	}
}
void setTimer2(int duration){
	count2 = duration/ TICK;
	flag2 = 0;
}

void timer2Run(){
	if (count2 > 0) {
		count2--;
		if (count2 == 0){
			flag2 = 1;
		}
	}
}


void setTimer0(int duration){
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}

void timer_run(){
	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter == 0){
			timer0_flag = 1;
		}
	}
}
