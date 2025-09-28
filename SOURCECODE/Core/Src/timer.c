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
