/*
 * time.c
 *
 *  Created on: May 22, 2014
 *      Author: Tibo
 */
#include "msp430g2553.h"
#include "time.h"
#include "uart.h"
#include "stdio.h"

static char delay_counter,
 	 	 	 	 	 seconds,
 	 	 	 	 	 minutes,
 	 	 	 	 	 hours,
 	 	 	 	 	 day;


//typedef struct {

//}time;

unsigned char buffer_test[40];


void init_timerA0(void){
	CCTL0 = CCIE;                     // CCR0 interrupt enabled
	CCR0 = 0xFFFF;
	TACTL = TASSEL_2;                 // SMCLK

}



void start_timer(unsigned char timer_nb, unsigned char mode){
	switch(mode){
		case 1 : {		//UP MODE, UP TO TACCR0
					if (timer_nb == 0)TACTL |= MC_1;
					else if (timer_nb == 1)TA1CTL &= MC_1;
				 }break;
		case 2 : {		//CONTINUOUS MODE, UP TO 0FFFFh
					if (timer_nb == 0)TACTL &= MC_2;
					else if (timer_nb == 1)TA1CTL &= MC_2;
				 }break;
		case 3 : {		//UP/DOWN MODE, UP TO TACCR0 THEN TO 0000h
					if (timer_nb == 0)TACTL &= MC_3;
					else if (timer_nb == 1)TA1CTL &= MC_3;
				 }break;
		default : break;
	}
}



//Use with care, only with SMCLK clock and using DCOCTL register
void load_compA0_freq(unsigned long freq){

#ifdef CLOCK_1MHZ

	if((freq >= 15) && (freq <= 20000)){
		TACTL |= ID_0;
		CCR0 = (1000000/freq)-1;
	}
	else if ((freq >= 7) && (freq <= 10000)){
		TACTL |= ID_1;
		CCR0 = (1000000/(freq*2))-1;
	}
	else if ((freq >= 4) && (freq <= 4800)){
		TACTL |= ID_2;
		CCR0 = (1000000/(freq*4))-1;
	}
	else if ((freq >= 1) && (freq <= 2400)){
		TACTL |= ID_3;
		CCR0 = (1000000/(freq*8))-1;
	}

#elif CLOCK_8MHZ

	if((freq >= 122) && (freq <= 155000)){
		TACTL |= ID_0;
		CCR0 = (8000000/freq)-1;
	}
	else if ((freq >= 60) && (freq <= 80000)){
		TACTL |= ID_1;
		CCR0 = (8000000/(freq*2))-1;
		}
	else if ((freq >= 30) && (freq <= 40000)){
		TACTL |= ID_2;
		CCR0 = (8000000/(freq*4))-1;
	}
	else if ((freq >= 15) && (freq <= 20000)){
		TACTL |= ID_3;
		CCR0 = (8000000/(freq*8))-1;
	}

#elif CLOCK_12MHZ

	if((freq >= 183) && (freq <= 240000)){
		TACTL |= ID_0;
		CCR0 = (12000000/freq)-1;
	}
	else if ((freq >= 92) && (freq <= 120000)){
		TACTL |= ID_1;
		CCR0 = (12000000/(freq*2))-1;
	}
	else if ((freq >= 46) && (freq <= 60000)){
		TACTL |= ID_2;
		CCR0 = (12000000/(freq*2))-1;
	}
	else if ((freq >= 23) && (freq <= 30000)){
		TACTL |= ID_3;
		CCR0 = (12000000/(freq*2))-1;
	}

#elif CLOCK_16MHZ

	if((freq >= 44) && (freq <= 320000)){
		TACTL |= ID_0;
		CCR0 = (16000000/freq)-1;
	}
	else if ((freq >= 120) && (freq <= 160000)){
		TACTL |= ID_1;
		CCR0 = (16000000/(freq*2))-1;
	}
	else if ((freq >= 60) && (freq <= 80000)){
		TACTL |= ID_2;
		CCR0 = (16000000/(freq*4))-1;
	}
	else if ((freq >= 30) && (freq <= 40000)){
		TACTL |= ID_3;
		CCR0 = (16000000/(freq*8))-1;
	}

#endif
}



void delay_us(unsigned int us){
#ifdef CLOCK_1MHZ		//Doesn't work well
	while (us--)
			__delay_cycles(1);

#elif CLOCK_8MHZ
	while (us--)
			__delay_cycles(5);

#elif CLOCK_12MHZ
	while (us--)
		__delay_cycles(9);

#elif CLOCK_16MHZ
	while (us--)
		__delay_cycles(13);
#endif
}


void delay_ms(unsigned int ms){
#ifdef CLOCK_1MHZ
	while (ms--)
			__delay_cycles(1000);

#elif CLOCK_8MHZ
	while (ms--)
			__delay_cycles(8000);

#elif CLOCK_12MHZ
	while (ms--)
		__delay_cycles(12000);

#elif CLOCK_16MHZ
	while (ms--)
		__delay_cycles(16000);
#endif
}


//Doesn't work with other than timer A and CCR0 now
void init_rtc(unsigned char timer, unsigned char comp){
	BCSCTL1 |= DIVA_3;				// ACLK/8
	BCSCTL3 |= XCAP_3;				//12.5pF cap- setting for 32768Hz crystal

	seconds=0;
	minutes=0;
	hours=0;
	day=1;

	if(timer==0)
	{
			if (comp==0){
			CCTL0 = CCIE;			// CCR0 interrupt enabled
			CCR0 = 511;				// 512 -> 1 sec, 30720 -> 1 min
		}
		else if (comp==1){
			CCTL1 = CCIE;
			CCR1 = 511;
		}
		else if (comp==2){
			CCTL1 = CCIE;
			CCR1 = 511;
		}
		TACTL =  TASSEL_1 + ID_3 + MC_1;			// ACLK, /8, upmode
	}
	else if(timer==1)
	{
		if (comp==0){
			TA1CCTL0 = CCIE;			// CCR0 interrupt enabled
			TA1CCR0 = 511;				// 512 -> 1 sec, 30720 -> 1 min
		}
		else if (comp==1){
			TA1CCTL1 = CCIE;			// CCR0 interrupt enabled
			TA1CCR1 = 511;				// 512 -> 1 sec, 30720 -> 1 min
		}
		else if (comp==2){
			TA1CCTL2 = CCIE;			// CCR0 interrupt enabled
			TA1CCR2 = 511;				// 512 -> 1 sec, 30720 -> 1 min
		}
		TA1CTL =  TASSEL_1 + ID_3 + MC_1;			// ACLK, /8, upmode
	}
}

void rtc_tick(void){
	if(seconds < 59){
		seconds++;
	}
	else{
		seconds = 0;
		if (minutes < 59){
			minutes++;
		}
		else {
			minutes=0;
			if (hours < 23){
				hours++;
			}
			else{
				hours=0;
				if(day < 7){
					day++;
				}
				else{
					day=1;
				}
			}
		}
	}
}



unsigned char timeout_occured(void)
{
	if(delay_counter > 0){
		return 0;
	}else{
		return 1;
	}
}

void set_timeout(unsigned char timeout)
{
	delay_counter = (timeout/10);
}


void decrement_delays(void)
{
	if(delay_counter > 0){
		delay_counter--;
	}
}

void timerA0routine(void){
	decrement_delays();
	rtc_tick();
	//snprintf(buffer_test, 20, "%d : %d and %d seconds \0",hours, minutes, seconds);
	uart_puts("bitch\r");
}

/*
#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR(void){
	uart_puts("bitch\r");
	timerA0routine();
	P1OUT ^= 0x01;
}
*/
