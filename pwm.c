// -----------------------------------------------------------------------
//   pwm.c -> funções para acesso ao pwm
//   Autor:  Rodrigo Maximiano Antunes de Almeida
//          rodrigomax at unifei.edu.br
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
// 
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "pwm.h"
#include "basico.h"

void SetaPWM1(unsigned char porcento)
{
	//formula do duty cycle:
	//DC_porcento = V / ((PR2+1)*4;
	//V = DC/100 * (PR2+1) * 4
	//V = DC * (PR2+1) /25
	
	unsigned int val = ((unsigned int)porcento) *(PR2+1);
	val = val / 25;
	//garante que tem apenas 10 bits
	val &= 0x03ff;
	//os 8 primeiros bits sao colocados no CCPR1L
	CCPR1L = val >> 2;
	//os ultimos dois são colocados na posição 5 e 4 do CCP1CON
	CCP1CON |= (val & 0x0003) << 4;
}

void SetaPWM2(unsigned char porcento)
{
	unsigned int val = ((unsigned int)porcento) *(PR2+1);
	val /= 25;
	//garante que tem apenas 10 bits
	val &= 0x03ff;
	//os 8 primeiros bits sao colocados no CCPR1L
	CCPR2L = val >> 2;
	//os ultimos dois são colocados na posição 5 e 4 do CCP1CON
	CCP2CON |= (val & 0x0003) << 4;
}

void SetaFreqPWM(unsigned int freq)
{
	//PR2 = fosc/(fpwm*4*prescaler)-1;
	//PR2 = (8000000/(freq*4*16)) - 1;
	PR2 = (125000/(freq)) - 1;
}

void InicializaPWM(void)
{
	BitClr(TRISC,2);//configura os pinos correspondentes como saídas
	BitClr(TRISC,3);

	T2CON |= 0b00000011; //configura o prescale do timer 2 para 1:16
	BitSet(T2CON,2); //Liga o timer 2
	
	
	CCP1CON |= 0b00001100;	//configura CCP1 como um PWM
	CCP2CON |= 0b00001100;	//configura CCP2 como um PWM
}