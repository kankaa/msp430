#include "misc.h"


unsigned char swap_nibble(unsigned char c){
	unsigned char tmp;
	tmp = ((c & 0xF0) >> 4) | ((c & 0x0F) << 4);
	return tmp;
}

//No protection against buffer overflow
void hex_to_ascii(unsigned char c, unsigned char buffer[], unsigned char pos){
	unsigned int masked;

	masked = (c & 0xF0) >> 4;

	if(masked <= 9)
		buffer[pos]= masked + '0';
	else if ((masked >= 10) && (masked <= 15))
		buffer[pos]= masked + 'A';

	masked = (c & 0x0F);
	if(masked <= 9)
		buffer[pos + 1]= masked + '0';
	else if ((masked >= 10) && (masked <= 15))
		buffer[pos + 1]= masked + 'A';

}

/*
void hex_to string(unsigned char inputBuffer[],unsigned char length, unsigned char outputBuffer[]){
	unsigned int i;

	for(i = 0; i < length; i++){
		hex_to_ascii(inputBuffer[i], outputBuffer, i*2);
	}
}
*/

//Work
void ascii_to_decsemioct(unsigned char inputBuffer[],unsigned char length, unsigned char *outputBuffer){
	unsigned char i;

	i = 0;
	while(i<length)
	{

		if(i%2==0)
			outputBuffer[i/2] = ((inputBuffer[i]-0x30) & 0x0f);
		else
			outputBuffer[i/2] |= (((inputBuffer[i]-0x30) & 0x0f) << 4);

		i++;
	}

	if((length)%2)		//If odd, add 0xF0
		outputBuffer[i/2] |= 0xF0;
}

//Work
void decsemioct_to_ascii(unsigned char inputBuffer[],unsigned char length, unsigned char *outputBuffer){
	unsigned char i;

	i=0;
	while(i<length)
	{
		outputBuffer[i*2] = (inputBuffer[i] & 0x0F) + 0x30;

		if((inputBuffer[i] & 0xF0) == 0xF0)
			outputBuffer[(i*2)+1] = '\0';
		else
			outputBuffer[(i*2)+1] = ((inputBuffer[i] & 0xF0) >> 4) + 0x30;

		i++;
	}
}

//Work
unsigned int septet_encoding(unsigned char inputBuffer[],unsigned int length, unsigned char *outputBuffer){
	unsigned int i;			//Loop counter
	unsigned char bit;		//Number to shift incremented each loop
	unsigned char byte;	//Temporary value
	unsigned char septets;	//Number of seven bytes packets grouped
	unsigned int encoded_length;

	encoded_length=0;
	septets=0;
	bit=0;
	for(i = 0; i < length; i++)
	{
		byte=0;
		if(bit ==7)
		{
			bit=0;
			septets++;
		}
		byte = (inputBuffer[i+septets] & 0x7F) >> bit;
		if(i < (length - (1+septets)))
		{
			byte |= inputBuffer[i + 1 + septets] << (7 - bit);

		}

		if(i < length - (length/8))
		{
			bit++;
			encoded_length++;//A amèliorer
		}
		else
			byte = 0x00;
		//if(i >= length - (length/8))
		//	byte = 0x00;

			outputBuffer[i]=byte;
	}
	return encoded_length;
}


//Doesn't work
unsigned int septet_decoding(unsigned char inputBuffer[],unsigned int length, unsigned char *outputBuffer){
	unsigned int i,cpt;			//Loop counter
	unsigned int bits;		//Number to shift incremented each loop
	unsigned char byte;		//Temporary value
	unsigned int septets;	//Number of seven bytes packets ungrouped
	unsigned char presentmask, lastmask, presentvalue, lastvalue;



	septets=0;
	bits=0;
	for(i=0; i < length; i++){
		presentmask = 0;
		lastmask = 0;
		byte=0;


		for(cpt = 0; cpt < (7 - bits); cpt++){
			presentmask = (1 << cpt);
		}
		for(cpt = 0; cpt < (bits + 1); cpt++){
			lastmask = (1 >> cpt);
		}

		presentvalue = inputBuffer[i] & presentmask;
		lastvalue = inputBuffer[i] & lastmask;

		if(bits == 0)
			outputBuffer[i + septets] = presentvalue;
		else
			outputBuffer[i + septets] = (presentvalue << bits) | (lastvalue >> (7 - bits)) ;






		if(bits==6)
			septets++;

		if(bits==7)
			bits=0;

		if(bits == 0)
			byte = inputBuffer[i] & 0x7F;
		else
		{
			byte = (inputBuffer[i] << bits + 1);
			byte |= (inputBuffer[i-1] >> 8 - bits);
		}


		outputBuffer[i + septets]= byte & 0x7F;
		bits++;

		/*


		if(bits==6)
		{
			septets++;
			byte = inputBuffer[i] >> (8 - bits);
			bits=0;
		}
		else
		{
			byte = (inputBuffer[i ] << bits);
			byte |= (inputBuffer[i - 1] >> ( 8 - bits));
		}

		/*
		//if((septets > 0) && (bits == 0))
		//	octet = inputBuffer[i - septets] >> 1;


	//	else
	//	{

			//byte = (inputBuffer[i - 1] >> bits);

			if(i > 0)

			bits++;
	//	}

		 */


	}
}



