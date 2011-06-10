// -----------------------------------------------------------------------
//   int.c -> fun��es para gerenciamento das interrup��es
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
#include "basico.h"

typedef void (*intFunc)(void);
//store the pointer to the interrupt function
static intFunc adcInterrupt;
static intFunc timerInterrupt;
static intFunc serialRxInterrupt;

static driver thisDrivers;
static driver_functions this_functions[INT_END];

char setTimerInt(void *parameters) {
    timerInterrupt = (intFunc)parameters;
    return FIM_OK;
}

char setAdcInt(void *parameters) {
    adcInterrupt = (intFunc)parameters;
    return FIM_OK;
}

char setSerialRxInt(void *parameters) {
    serialRxInterrupt = (intFunc)parameters;
    return FIM_OK;
}

char enableInterrupts(void *parameters) {
    BitSet(INTCON, 7); //habilita todas as interrupções globais
    BitSet(INTCON, 6); //habilita todas as interrupções de periféricos
    return FIM_OK;
}

char initInterrupt(void *parameters) {

    thisDrivers.drv_id = *((char*)parameters);
    this_functions[INT_ADC_SET].func_ptr = setAdcInt;
    this_functions[INT_TIMER_SET].func_ptr = setTimerInt;
    this_functions[INT_SERIAL_SET].func_ptr = setSerialRxInt;
    this_functions[INT_ENABLE].func_ptr = enableInterrupts;

    BitClr(RCON, 7); //desabilita IPEN (modo de compatibilidade)

    return FIM_OK;
}

driver* getInterruptDriver(void) {
    //to ensure that at least the init function will be known
    thisDrivers.drv_init = initInterrupt;
    thisDrivers.func_ptr = this_functions;
    return &thisDrivers;
}

void isr(void) interrupt 1 {
    if (BitTst(INTCON, 2)) {
        timerInterrupt();
    } //Timer overflow
    if (BitTst(PIR1, 5)) {
        serialRxInterrupt();
    } //serial data recive
    if (BitTst(PIR1, 6)) {
        adcInterrupt();
    } //ADC conversion finished
}
