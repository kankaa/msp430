/*
 * time.h
 *
 *  Created on: May 22, 2014
 *      Author: Tibo
 */

#ifndef TIME_H_
#define TIME_H_


#define CLOCK_1MHZ	0xCF
//#define CLOCK_8MHZ	0x93
//#define CLOCK_12MHZ	0x9C
//#define CLOCK_16MHZ	0x92




void init_timerA0(void);
void start_timer(unsigned char timer_nb, unsigned char mode);
void load_compA0_freq(unsigned long freq);
void delay_us(unsigned int us);
void delay_ms(unsigned int ms);
void init_rtc(unsigned char timer, unsigned char comp);


unsigned char timeout_occured(void);		//A continuer
void set_timeout(unsigned char timeout);
void decrement_delays(void);
void rtc_tick(void);
void timerA0routine(void);


#endif /* TIME_H_ */
