#include  "msp430g2553.h"
#include  "uart.h"
#include  "stdint.h"
#include  "fifo.h"
#include  "misc.h"
#include  "pdu.h"
#include  "modem.h"
#include  "time.h"

inline void interr(void){

	uart_puts("ooooo");
}
unsigned char flag;
/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    /*
    unsigned char  number_c[6],
    	  number_uc[11]="31641600986",
    	  mess[11]="Hello world",
    	  mess_c[11],//="B1584C2693CD66331A8D56ABD500",
    	  mess_dc[11];

    unsigned int text_coded;
    unsigned int * ptr_txt=&text_coded;
    setup_uart_9600();
   // decsemioct_to_ascii(number_c, 6, number_uc);
   // ascii_to_decsemioct(number_uc, 11, number_c);

   // text_coded = septet_encoding(mess,11, mess_c);//A vérifier avec 1 à 8/9
   // septet_decoding(mess_c, 11, mess_dc);
   // uart_putc(text_coded);


    const char  pdu[16]="07911326040000F0";
    UNPROCESSED_PDU message_brut;

    decode_pdu (pdu, &message_brut);

    uart_putc(message_brut.SMSC_IF + 0x30);
    */
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;
    setup_uart_9600();
/*
    init_modem_pin();
    power_en_on();
    delay_ms(500);
    power_on();
*/
   // setup_modem();
    P1DIR = 0x01;
    init_rtc(0,0);
    //init_rtc(1,0);	//Pour timer b rtc
    flag=0;

    //uart_putc('o');
    while(1){
    	if(flag==1){
    		interr();
    		flag=0;
    	}


    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void T0A0_ISR(void){
	//uart_puts("bitch\r");
	//timerA0routine();
	P1OUT ^= 0x01;
	interr();
	flag=1;
}

/*
#pragma vector = TIMER1_A0_VECTOR
__interrupt void T0A0_ISR(void){
	//uart_puts("bitch\r");
	//timerA0routine();
	P1OUT ^= 0x01;
	interr();
	flag=1;
}
*/
