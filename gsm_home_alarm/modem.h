/*
 * modem.h
 *
 *  Created on: May 11, 2014
 *      Author: Tibo
 */

#ifndef MODEM_H_
#define MODEM_H_



#define MODEM_PORTI	P1IN
#define MODEM_PORTO	P1OUT

#define STATUS_BIT		BIT(0)
#define RESET_BIT		BIT(3)
#define RI_BIT			BIT(4)
#define SIMPWR_BIT		BIT(5)
#define PWR_EN_BIT		BIT(6)

void init_modem_pin(void);
void setup_modem(void);
void power_en_on(void);
void power_en_off(void);
void power_on(void);
void power_off(void);
void power_off_AT(void);
void reset_modem(void);
void send_cmd(void);
void read_sms(void);
void send_sms(void);






#endif /* MODEM_H_ */
