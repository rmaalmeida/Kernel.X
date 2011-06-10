#include "disp7seg.h"
#include "basico.h"

//vetor para armazenar a conversão do display
static const char valor[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
//armazena qual é o display disponivel
static char display;
//armazena o valor a ser enviado ao display
static char v0, v1, v2, v3;

void MudaDigito(char val, char pos)
{
	if (pos == 0)
	{
		v0 = val;
	}
	if (pos == 1)
	{
		v1 = val;
	}
	if (pos == 2)
	{
		v2 = val;
	}
	if (pos == 3)
	{
		v3 = val;
	}

}

char AtualizaDisplay(void)
{
	//desliga todos os displays
	PORTA = 0x00;
	PORTE = 0x00;
	//desliga todos os leds
	PORTD = 0x00;

	switch(display) //liga apenas o display da vez
	{
		case 0:
			PORTD = valor[v0];
			BitSet(PORTA,5);
			display = 1;
		break;

		case 1:
			PORTD = valor[v1];
			BitSet(PORTA,2);
			display = 2;
		break;

		case 2:
			PORTD = valor[v2];
			BitSet(PORTE,0);
			display = 3;
		break;

		case 3:
			PORTD = valor[v3];
			BitSet(PORTE,2);
			display = 0;
		break;

		default:
			display = 0;
		break;
	}
	return 2;
}


void InicializaDisplays(void)
{
	//configuração dos pinos de controle
	BitClr(TRISA,2);
	BitClr(TRISA,5);
	BitClr(TRISE,0);
	BitClr(TRISE,2);
	ADCON1 = 0x0E; //apenas AN0 é analogico, a referencia é baseada na fonte
	TRISD = 0x00;	//Porta de dados

}