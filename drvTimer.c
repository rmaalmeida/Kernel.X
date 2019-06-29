// -----------------------------------------------------------------------
//   drvTimer.c -> implementação do driver de Timer 0
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

#include "drvTimer.h"

// variável utilizada para auto-referência do driver
static driver thisDriver;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[TMR_END];

// checa se o Timer 0 chegou ao fim
char isTimerEnd(void *parameters) {
    (*(char *) parameters) = BitTst(INTCON, 2);
    return OK;
}

// paraliza temporariamente a contagem do Timer 0
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.
char waitTimer(void *parameters) {
    while (!BitTst(INTCON, 2));
    return OK;
}

// reinicializa o Timer 0, sendo o parâmetro de entrada dado em [ms]
char resetTimer(void *parameters) {
    // para placa com 8MHz, então 1 ms = 2 ciclos
    unsigned int ciclos = ((unsigned int)parameters) * 2;
    
    /* overflow acontece com 2^15 - 1 = 65535 (máximo valor atingido por uma
     * variável do tipo 'unsigned int') */
    ciclos = 65534 - ciclos;

    //subtrai tempo de overhead (experimental)
    ciclos -= 14;

    // salva os 8 bits mais significativos
    TMR0H = (ciclos >> 8);

    // salva os 8 bits menos significativos
    TMR0L = (ciclos & 0x00FF);

    //limpa a flag de overflow
    BitClr(INTCON, 2);

    return OK;
}

//liga o Timer 0
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.
char startTimer(void *parameters) {
    BitSet(T0CON, 7);
    return OK;
}

// liga a interrupção para o Timer 0
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.
char enableTimerInt(void *parameters) {
    BitSet(INTCON, 5);
    return OK;
}

// inicialização do driver
char initTimer(void *parameters) {
    thisDriver.drv_id = *(char*) parameters;
    this_functions[TMR_WAIT] = waitTimer;
    this_functions[TMR_IS_END] = isTimerEnd;
    this_functions[TMR_RESET] = resetTimer;
    this_functions[TMR_START] = startTimer;
    this_functions[TMR_INT_EN] = enableTimerInt;

    // configura Timer 0 sem 'prescaler'
    T0CON = 0b00001000;

    return OK;
}

// função de auto-referência
driver* getTimerDriver(void) {
    thisDriver.drv_init = initTimer;
    thisDriver.func_ptr = (ptrFuncDrv*) & this_functions;
    return &thisDriver;
}

