// -----------------------------------------------------------------------
//   drvInterrupt.c -> implementação do driver de interrupção
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

#include "drvInterrupt.h"

// variável utilizada para auto-referência do driver
static driver thisDrivers;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[INT_END];

// armazena o ponteiro para a função de interrupção
typedef void (*intFunc)(void);

// cada ponteiro de função de interrupção deve ser inserida
static intFunc adcInterrupt;
static intFunc timerInterrupt;
static intFunc serialRxInterrupt ;
static intFunc serialTxInterrupt ;
static intFunc tecladoInterrupt ;

// permite que ocorram interrupções
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.
char enableInterrupts(void *parameters) {
    BitSet(INTCON, 7); //habilita todas as interrupções globais
    BitSet(INTCON, 6); //habilita todas as interrupções de periféricos
    return OK;
}

// rotinas de configuração das funções de retorno de interrupção dos drivers
char setTimerInt(void *parameters) {
    timerInterrupt = (intFunc)parameters;
    return OK;
}

char setAdcInt(void *parameters) {
    adcInterrupt = (intFunc)parameters;
    return OK;
}

char setTecladoInt(void *parameters) {
    tecladoInterrupt = (intFunc)parameters ;
    return OK ;
}

char setSerialRxInt(void *parameters) {
    serialRxInterrupt = (intFunc)parameters;
    return OK;
}

char setSerialTxInt(void *parameters) {
    serialTxInterrupt = (intFunc)parameters;
    return OK;
}

// inicialização do driver
char initInterrupt(void *parameters) {
    thisDrivers.drv_id = *((char*)parameters);
    this_functions[INT_ADC_SET] = setAdcInt;
    this_functions[INT_TIMER_SET] = setTimerInt;
    this_functions[INT_SERIAL_RXSET] = setSerialRxInt;
    this_functions[INT_SERIAL_TXSET] = setSerialTxInt;
    this_functions[INT_TECLADO_SET] = setTecladoInt ;
    this_functions[INT_ENABLE] = enableInterrupts;

    // desabilita IPEN (modo de compatibilidade)
    BitClr(RCON, 7);

    // desabilita as interrupções de todos os dispositivos
    PIE1 = 0x00;

    // desabilita as interrupções de todos os dispositivos
    INTCON = 0x00;

    return OK;
}

// função de auto-referência
driver* getInterruptDriver(void) {
    thisDrivers.drv_init = initInterrupt;
    thisDrivers.func_ptr = this_functions;
    return &thisDrivers;
}

// rotina de atendimento de interrupções
void isr(void) interrupt 1 {

    if (BitTst(INTCON, 2)) {
        timerInterrupt();
    } // estouro de faixa do Timer

    if (BitTst(PIE1, 5) && BitTst(PIR1, 5)) {
        BitClr(PIR1, 5) ;
        serialRxInterrupt();
    } // recepção de dados via serial

    if (BitTst(PIE1, 4) && BitTst(PIR1, 4)) {
        BitClr(PIR1, 4) ;
        serialTxInterrupt();
    } // envio de dados via serial

    if (BitTst(INTCON, 3) && BitTst(INTCON, 0)) {
        BitClr(INTCON, 0) ;
        PORTD++;
        tecladoInterrupt() ;
    } // tecla do teclado matricial pressionada

    if (BitTst(PIE1, 6) && BitTst(PIR1, 6)) {
        adcInterrupt();
    } // término da conversão de dados no conversor A/D
}

