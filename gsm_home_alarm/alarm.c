/*
 * alarm.c
 *
 *  Created on: Jun 19, 2014
 *      Author: Tibo
 */
#include  	"msp430g2553.h"
#include  	"defines.h"
#include  	"modem.h"
#include	"time.h"
#include "alarm.h"


void setup_alarm(void){
	//P2DIR= 	//Set up direction
	//P2IES=	//Interrupt Edge select
	//P2IE=		//Interrupt enable

}

void send_warning(void){
	if(P2IFG==PIR_1){
	//snprintf();

	}
	else if (P2IFG==PIR_2){

	}
	else if (P2IFG==PIR_3){

	}
	//send_sms
}


/*
#pragma vector = PORT2_VECTOR
__interrupt void P2_IT(void){

}

*/
