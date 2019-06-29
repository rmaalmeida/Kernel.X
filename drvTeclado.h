// -----------------------------------------------------------------------
//   drvSerial.h -> header das definições do driver do teclado matricial
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


#ifndef TECLADO_H
    #define TECLADO_H
    #include "kernel.h"
    #include "ddCtr_types.h"

    // Tempo máximo de espera para oscilação de uma tecla
    #define MAX_TIME_DEBOUNCE 100

    // Tempo mínimo, sem oscilação, na qual a leitura de uma tecla seja aceita (experimental)
    #define MIN_TIME_DEBOUNCE 2

    //apenas retorna o "objeto" do driver
    driver* getTecladoDriver(void) ;

    // define os identificadores das funções do driver
    enum {
        VALUE_TECLADO,
        VALUE_TECLADO_ASCII,
        TECLADO_INT_EN,
        TECLADO_END
    } ;

    // função de 'debounce' das teclas do teclado matricial
    char debounceTeclas() ;

#endif

