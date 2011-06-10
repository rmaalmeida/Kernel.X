#include "teclado.h"
#include "basico.h"

static unsigned int valor = 0x0000;

unsigned int LerTeclas(void)
{
	return valor;
}

void DebounceTeclas(void)
{
	unsigned char i,j;
	static unsigned char tempo;
	static unsigned int valorNovo = 0x0000;
	static unsigned int valorAntigo = 0x0000;

	for(i = 0; i < 4; i++)
	{
		//desliga todas as colunas
		PORTB |= 0x0F;
		BitClr(PORTB,i);	//liga a coluna correspondente
		//gasta tempo atoa, necess�rio para garantir que o pino atingiu o nivel alto
		for(j=0;j<100;j++);

		//realiza o teste para cada bit e atualiza a vari�vel
		for(j = 0; j < 4; j++)
		{
			if (!BitTst(PORTB,j+4))
			{
				BitSet(valorNovo,(i*4)+j);
			}
			else
			{
				BitClr(valorNovo,(i*4)+j);
			}
		}
	}
	if (valorAntigo == valorNovo)
	{
		tempo --;
	}
	else
	{
		tempo = 10;
		valorAntigo = valorNovo;
	}
	if (tempo == 0)
	{
		valor = valorAntigo;
	}
}

void InicializaTeclado(void)
{
	TRISB = 0xF0;	//quatro entradas e quatro saidas
	BitClr(INTCON2,7); //liga pull up
	ADCON1 = 0b00001110; //apenas AN0 � analogico, a referencia � baseada na fonte
	SPPCFG = 0x00;
}