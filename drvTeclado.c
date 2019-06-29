// -----------------------------------------------------------------------
//   drvSerial.c -> implementação do driver do conversor A/D
//   Autor: Lucas Carvalho de Sousa
//          lucas.c.s at unifei.edu.br
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

#include "drvTeclado.h"

// variável utilizada para auto-referência do driver
static driver thisDriver ;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[TECLADO_END] ;

// resposta da chamada de outro driver
static process *callBack ;

// última coluna do teclado matricial acessada
static unsigned int value ;

static process proc_debounceTeclas = {debounceTeclas, 0, 0} ;

// retorna o caracter da última tecla pressionada
static unsigned char value2ascii[] = {'A', 'B', 'C', 'D', '3', '6', '9', 'F',
                                      '2', '5', '8', '0', '1', '4', '7', 'E'} ;

// implementação da função de 'debounce'
char debounceTeclas(void) {
    unsigned char i, j ;
    unsigned char cont = 0x00 ;
    unsigned char tempo = MIN_TIME_DEBOUNCE ;
    volatile unsigned int valorNovo = 0x0000 ;
    volatile unsigned int valorAntigo = value;

    while ((tempo > 0) && (cont < MAX_TIME_DEBOUNCE)) {
        for (i = 0; i < 4; i++) {
            // desliga todas as colunas
            PORTB |= 0x0F ;

            // liga a coluna correspondente
            PORTB &= ~(1<<i) ;

            // teste para cada bit, atualiza a variável
            for (j = 0; j < 4; j++) {
                if (!BitTst(PORTB,j+4)) {
                    BitSet(valorNovo,(i*4)+j) ;
                }
                else {
                    BitClr(valorNovo,(i*4)+j) ;
                }
            }
        }

        // rotina de 'debounce' propriamente dita: a cada chamada,
        // o tempo é decrementado em 1 unidade
        if (valorAntigo == valorNovo) {
            tempo-- ;
        }
        else {
            tempo = MIN_TIME_DEBOUNCE ;
            valorAntigo = valorNovo ;
            cont++ ;
        }
    }

    if (tempo == 0) {
        if (value != valorAntigo){
            value = valorAntigo ;
            if (value) {
                kernelAddProc(callBack) ;
            }
        }


        // TODO duas vezes???
        PORTB &= 0xf0 ;
        PORTB &= 0xf0 ;

        // desativa a flag de interrupção, possivelmente ativada durante
        // a oscilação do sinal no pressionamento da tecla
        BitClr(INTCON, 0) ;

        //ativa a interrupção por mudança de estado na Porta B
        BitSet(INTCON, 3) ;
    }
    else
    {
        return FAIL ;
    }
    return OK ;
}

// retorna na variável recebida o resultado da última leitura do teclado, em hexadecimal
char tecladoReturnLastValue(void* parameters) {
    (*(unsigned int*)parameters) = value ;
    return OK ;
}

// retorna na variável recebida o resultado da última leitura do teclado, em código ASCII
char tecladoReturnLastValueASCII(void* parameters) {
    unsigned char i ;
    for (i = 0; i < 16; i++) {
        if (BitTst(value, i)) {
            (*(unsigned char*)parameters) = value2ascii[i] ;
            return OK ;
        }
    }

    // se nenhuma tecla foi pressionada, então não há código ASCII
    return FAIL ;
}

// rotina de tratamento de interrupção do teclado matricial
void tecladoISR() {
    //desativa a interrupção por mudança de estado na porta B
    BitClr(INTCON, 3) ;
    kernelAddProc(&proc_debounceTeclas) ;
}

// permite que o teclado matricial gere interrupções
char enableTecladoInterrupt(void* parameters) {
    // configura a função de retorno para interrupção por mudança de estado nas teclas
    callDriver(DRV_INTERRUPT, INT_TECLADO_SET, (void*)tecladoISR) ;
    
    // configura a função de retorno para o programa principal em caso de um tratamento de interrupção
    callBack = parameters ;

    // desativa a flag de interrupção, permitindo que as teclas possam
    // ser pressionadas e tratadas pela rotina de debounce
    BitClr(INTCON, 0) ;

    // ativa a interrupção por mudança de estado na Porta B
    BitSet(INTCON, 3) ;

    return OK ;
}

// inicialização do driver
char initTeclado(void* parameters) {
    thisDriver.drv_id = *((char*) parameters) ;
    this_functions[VALUE_TECLADO] = tecladoReturnLastValue ;
    this_functions[VALUE_TECLADO_ASCII] = tecladoReturnLastValueASCII ;
    this_functions[TECLADO_INT_EN] = enableTecladoInterrupt ;

    value = 0x0000 ;

    // configuração do teclado:
    // desativa a interrupção por mudança de estado na Porta B
    BitClr(INTCON, 3) ;
    TRISB = 0xf0 ;

    // habilita função I/O para o pino RB4 ;
    BitClr(SPPCFG, 5) ;
    PORTB = 0x00 ;

    // habilita pull-up
    BitClr(INTCON2, 7) ;

    return OK ;
}

// função de auto-referência
driver* getTecladoDriver(void) {
    thisDriver.drv_init = initTeclado ;
    thisDriver.func_ptr = (ptrFuncDrv*) &this_functions ;
    return &thisDriver ;
}

