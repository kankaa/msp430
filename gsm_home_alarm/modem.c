/*
 * modem.c
 *
 *  Created on: May 11, 2014
 *      Author: Tibo
 */

#include  "defines.h"
#include  "modem.h"
#include "time.h"
#include  "msp430g2553.h"
#include "uart.h"

/*

char block_until_sequence(char* s)
{
	char current;
	char* s_orig = s;
	while(1){
		if(*s == '\0'){
			return 1;
		}
		set_timeout(2);
		while(!fifo_available(struct my_fifo * const fif)){
			if(timeout_occured()){
				return 0;
			}
		}
		current = fifo_read(struct my_fifo * const fif);
		if(*s == current){
			s++;
		}else{
			s = s_orig;
		}
	}
}
*/

void init_modem_pin(void){
	P1DIR |= RESET_BIT + SIMPWR_BIT + PWR_EN_BIT;		//RST and PWR : OUTPUT
	P1DIR &= ~RI_BIT + ~STATUS_BIT;						//RI and STATUS : INPUT
	MODEM_PORTO = 0x00;									//Reset output port
	//P1IES |= RI_BIT;									//Interrupt on falling edge of RI



	//P1IE = RI_BIT;										//Interrupt on RI enabled
}

void setup_modem(void){
	uart_puts("AT+CPIN=3601\r");	//Enter PIN
	//wait until ok
	delay_ms(1000);
	uart_puts("AT+CMGF=1 \r");		//Select SMS message format(0 : PDU , 1 : text)
	//uart_puts("AT+CMGL=\r");		//Preferred SMS message storage
	//uart_putc("AT+CSAS=");	//Save SMS settings

}

void power_en_on(void){
	MODEM_PORTO |= PWR_EN_BIT;
}

void power_en_off(void){
	MODEM_PORTO &= ~PWR_EN_BIT;
}

void power_on(void){
	MODEM_PORTO |= SIMPWR_BIT;
	delay_ms(2000);
	MODEM_PORTO &= ~SIMPWR_BIT;
	while(!(MODEM_PORTI & STATUS_BIT));
}

void power_off(void){
	MODEM_PORTO |= SIMPWR_BIT;
	delay_ms(2000);
	MODEM_PORTO &= ~SIMPWR_BIT;
	while(!(MODEM_PORTI & STATUS_BIT));
}

void power_off_AT(void){
	uart_puts("AT+CPOWD=1\r");
	while(!(MODEM_PORTI & STATUS_BIT));
}



void reset_modem(void){
	MODEM_PORTO |= RESET_BIT;
	delay_us(50);
	MODEM_PORTO &= ~RESET_BIT;
	delay_ms(1500);
}




void read_sms(void){

}

void send_sms(void){
	//snprintf();
	//uart_puts("AT+CSCS")
}

void interrupt_P1_routine(void){

}

/*
#pragma vector = PORT1_VECTOR
__interrupt void P1_IT(void){
	interrupt_P1_routine();
}

*/
