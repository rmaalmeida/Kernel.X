// -----------------------------------------------------------------------
//   drvLed.c -> implementação do driver dos LED's
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

/* Por padrão, todos os drivers terão, ao menos, uma variável para se
 * auto-referenciar, um vetor com as funções que possui e as funções de
 * inicialização e de auto-referência ('get') */

#include "drvLed.h"

// variável utilizada para auto-referência do driver
static driver thisDriver;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[LED_END];

// acende ou apaga os LED's selecionados, de acordo com os parâmetros recebidos
char changePORTD(void *parameters) {
    PORTD = *((char*) parameters);
    return OK;
}

// inicialização do driver
char initLed(void *parameters) {
    // Configura os pinos da porta D como saída
    TRISD = 0x00;

    thisDriver.drv_id = *((char*) parameters);
    this_functions[LED_PORTD] = changePORTD;

    return OK;
}

// função de auto-referência
driver* getLedDriver(void) {
    thisDriver.drv_init = initLed;
    thisDriver.func_ptr = (ptrFuncDrv*) &this_functions;
    return &thisDriver;
}

