// -----------------------------------------------------------------------
//   Disp7Seg.c -> implementação do driver do conversor A/D
//   Autor:  Lucas Carvalho de Sousa & César Augusto Marcelino dos Santos
//          lucas.c.s at unifei.edu.br cesarmarcelino at uol.com.br
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


#include "drvDisp7seg.h"

// variável utilizada para auto-referência do driver
static driver thisDriver ;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[DISP7SEG_END] ;

static process proc_multiplexDisp7seg = {atualizaDisplay, 7, 0} ;

// vetor para armazenar a conversão do display
static const char valor[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71} ;

// armazena qual é o display disponivel
static char display;

// armazena o valor a ser enviado a cada display
static char valDisp0, valDisp1, valDisp2, valDisp3;

// implementação da função de atualização da exibição nos displays de 7 segmentos
char atualizaDisplay(void)
{
    	//desliga todos os displays
	PORTA &= 0b11011011;
	PORTE &= 0b11111010;

	//desliga todos os segmentos (LED's)
	PORTD = 0x00;

        // liga apenas um display por vez
	switch (display) {
            // display 0
            case 0:
                    PORTD = valor[valDisp0];
                    PORTA |= 0b00100000 ;
                    display = 1;
            break;

            // display 1
            case 1:
                    PORTD = valor[valDisp1];
                    PORTA |= 0b00000100 ;
                    display = 2;
            break;

            // display 2
            case 2:
                    PORTD = valor[valDisp2];
                    PORTE |= 0b00000001 ;
                    display = 3;
            break;

            // display 3
            case 3:
                    PORTD = valor[valDisp3];
                    PORTE |= 0b00000100 ;
                    display = 0;
            break;

            // acesso indevido: retorna ao display 0
            default:
                    display = 0;
            break;
	}

        return REPEAT ;
}

// exibe no display de 7 segmentos (recebido como valor de entrada) um número
char Disp7segIntWrite(void *parameters) {
    int valTemp = (unsigned int)parameters ;

    if (valTemp < 10000) {
        valDisp3 = valTemp / 1000 ;
        valTemp %= 1000 ;
        valDisp2 = valTemp / 100 ;
        valTemp %= 100 ;
        valDisp1 = valTemp / 10 ;
        valTemp %= 10 ;
        valDisp0 = valTemp ;

        return OK;
    }

    return FAIL;
}

// liga os displays de 7 segmentos
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.
char disp7segON(void *parameters) {
    kernelAddProc(&proc_multiplexDisp7seg) ;
    return OK ;
}

// inicialização do driver
char initDisp7seg(void *parameters) {
    thisDriver.drv_id = *(char*) parameters;

    this_functions[DISP7SEG_INTEGER] = Disp7segIntWrite ;
    this_functions[DISP7SEG_ON] = disp7segON ;

    // configuração dos pinos de controle:
    // os pinos ligados à alimentação dos displays serão de saída
    TRISA &= 0b11111011 ;
    TRISA &= 0b11011111 ;
    TRISE &= 0b11111110 ;
    TRISE &= 0b11111011 ;

    // desliga todos os segmentos (LED's)
    PORTD = 0x00 ;

    // configura como saída os pinos ligados aos segmentos (LED's)
    TRISD = 0x00 ;

    // a escrita nos displays de 7 segmentos se inicia pelo de número 0
    display = 0 ;

    return OK;
}

// função de auto-referência
driver* getDisp7segDriver(void) {
    thisDriver.drv_init = initDisp7seg;
    thisDriver.func_ptr = (ptrFuncDrv*) & this_functions;
    return &thisDriver;
}

