/*
 * timer.h
 *
 *  Created on: Sep 28, 2025
 *      Author: my pc
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define TICK 10
#define TIMER_CYCLE 10

int count;
int flag;
int count2;
int flag2;

//var of lab2_ex6
int timer0_counter;
int timer0_flag;



void setTimer1(int duration);
void timer1Run(void);
void setTimer2(int duration);
void timer2Run(void);
// LAB2_ex6 func
void setTimer0(int duration);
void timer_run();


#endif /* INC_TIMER_H_ */
