// -----------------------------------------------------------------------
//   drvSerial.h -> header das definições do driver de comunicação Serial
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


#ifndef SERIAL_H
    #define SERIAL_H
    #include "kernel.h"
    #include "ddCtr_types.h"

    //apenas retorna o "objeto" do driver
    driver* getSerialDriver(void) ;

    // define os identificadores das funções do driver
    enum {
        SERIAL_INT_RX_EN,
        SERIAL_INT_TX_EN,
        SERIAL_WRITE,
        SERIAL_LAST_VALUE,
        SERIAL_END
    } ;

#endif

