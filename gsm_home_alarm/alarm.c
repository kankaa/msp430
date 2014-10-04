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

//Fill this table with positions of each sensor
char sensor_name[6][15] = {
  "Living room",
  "Office",
  "Kitchen",
  "Bedroom",
  "Unused",
  "Unused"
};


void setup_alarm(void){
	//P2DIR= 0x00; 	//Set up direction
	//P2IES= 	//Interrupt Edge select
	//P2IE=	0x	//Interrupt enable

}

void P2interrupt(void){
	//Save input port
	//Translate input port to sensor name
	//Save rtc time
	//Concatenation with sensor name
	//Send sms
}

/*
#pragma vector = PORT2_VECTOR
__interrupt void P2_IT(void){

}

*/
