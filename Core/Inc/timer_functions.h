/*
 * timer_functons.h
 *
 *  Created on: May 21, 2024
 *      Author: ngp
 */

#ifndef INC_TIMER_FUNCTIONS_H_
#define INC_TIMER_FUNCTIONS_H_

void set_time (char hrs, char min, char sec, char date, uint8_t weekday, uint8_t month, char year);
void get_time(char Time[], char Date[]);
void get_timestamp(char timestamp[]);

#endif /* INC_TIMER_FUNCTIONS_H_ */
