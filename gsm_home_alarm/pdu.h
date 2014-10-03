#ifndef _PDU_H_
#define _PDU_H_


#include <stdio.h>


typedef struct {
	unsigned char SMSC_IF,		//SMSC Info length
				  SMSC_AT, 		//SMSC Adress Type
				  SMS_D,			//First Octet of SMS Delivery message
				  SN_AL, 			//Sender Number Adress Length
				  SN_AT, 			//Sender Number Adress Type
				  TP_PID, 		//Protocol Identifier
				  TP_DCS,			//Data Coding Scheme
				  TP_UDL; 		//User Data Length

	unsigned char SMSC_NB[20],	//To improve
				  SN[20],		//To improve
				  TP_SCTS[7];		//Time Stamp
}UNPROCESSED_PDU;

typedef struct {
	unsigned char smscInfoLength,
				  smscAdressType,
				  firstOctet,
				  snAdressLength,
				  snAdressType,
				  protocolIdentifier,
				  dataCodingScheme,
				  userDataLength;

	unsigned char smscNumber[20],
				  senderNumber[20],
				  timeStamp[20];
}PROCESSED_PDU;


void decode_pdu (const char inputBuffer[], UNPROCESSED_PDU * unprocessed);



#endif
