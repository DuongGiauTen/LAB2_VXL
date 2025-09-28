/*
 * timer.h
 *
 *  Created on: Sep 28, 2025
 *      Author: my pc
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define TICK 10
int count;
int flag;
int count2;
int flag2;

void setTimer1(int duration);
void timer1Run(void);
void setTimer2(int duration);
void timer2Run(void);


#endif /* INC_TIMER_H_ */
