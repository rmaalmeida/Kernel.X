// -----------------------------------------------------------------------
//   timer.c -> fun��es para acesso ao timer 0
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

#include "basico.h"
#include "drvTimer.h"

static driver thisDriver;
static driver_functions this_functions[TMR_END];

char isTimerEnd(void *parameters) {
    (*(char *) parameters) = BitTst(INTCON, 2);
    return FIM_OK;
}

char waitTimer(void *parameters) {
    while (!BitTst(INTCON, 2));
    return FIM_OK;
}

//tempo em mS

char resetTimer(void *parameters) {
    //para placa com 8MHz 1 ms = 2 ciclos
    unsigned int ciclos = ((unsigned int)parameters) * 2;
    //overflow acontece com 2^15-1 = 65535 (max unsigned int)
    ciclos = 65534 - ciclos;
    ciclos -= 14; //subtrai tempo de overhead(experimental)
    TMR0H = (ciclos >> 8); //salva a parte alta
    TMR0L = (ciclos & 0x00FF); // salva a parte baixa
    BitClr(INTCON, 2); //limpa a flag de overflow

    return FIM_OK;
}

char startTimer(void *parameters) {
    BitSet(T0CON, 7); //liga o timer 0
    return FIM_OK;
}

char enableTimerInt(void *parameters) {
    BitSet(INTCON, 5); // liga a interrupção para o timer 0
    return FIM_OK;
}

char initTimer(void *parameters) {

    thisDriver.drv_id = *(char*) parameters;
    this_functions[TMR_WAIT].func_ptr = waitTimer;
    this_functions[TMR_IS_END].func_ptr = isTimerEnd;
    this_functions[TMR_RESET].func_ptr = resetTimer;
    this_functions[TMR_START].func_ptr = startTimer;
    this_functions[TMR_INT_EN].func_ptr = enableTimerInt;

    T0CON = 0b00001000; //configura timer 0 sem prescaler
    
    return FIM_OK;
}

driver* getTimerDriver(void) {
    //to ensure that at least the init function will be known
    thisDriver.drv_init = initTimer;
    thisDriver.func_ptr = (driver_functions*) & this_functions;
    return &thisDriver;
}
