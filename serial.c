#include "serial.h"
#include "basico.h"

void EnviaSerial(unsigned char c) 
{ 
	while(!BitTst(PIR1,4));	//aguarda o registro ficar disponível
	TXREG=c; 		//coloca o valor para ser enviado
}
unsigned char RecebeSerial(void) 
{ 
	char resp = 0;
	if (BitTst(PIR1,5))	//Verifica se existe algum valor disponivel
	{	
		resp = RCREG;	//retorna o valor
	}
	return resp;		//retorna zero
}
void InicializaSerial(void)
{
	TXSTA = 0b00101100;	//configura a transmissão de dados da serial
	RCSTA = 0b10010000;	//configura a recepção de dados da serial
	BAUDCON = 0b00001000;	//configura sistema de velocidade da serial
	SPBRGH = 0b00000000;	//configura para 56k
	SPBRG = 0b00100010;	//configura para 56k
	BitSet(TRISC,6);	//pino de recepção de dados
	BitClr(TRISC,7);	//pino de envio de dados
}