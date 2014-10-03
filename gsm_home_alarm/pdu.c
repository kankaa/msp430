#include "pdu.h"


void decode_pdu (const char inputBuffer[], UNPROCESSED_PDU * unprocessed )
{
	const char mess[3]="071";
	int test_sscanf;
	sscanf(mess, "%2d", &test_sscanf);
}
