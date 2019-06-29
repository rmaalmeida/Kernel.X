// -----------------------------------------------------------------------
//   drvDisp7seg.h -> header das definições dos displays de 7 segmentos
//   Autor:  Lucas Carvalho de Sousa
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

#ifndef Disp7seg_H
    #define Disp7seg_H
    #include "kernel.h"
    #include "ddCtr_types.h"

    //apenas retorna o "objeto" do driver
    driver* getDisp7segDriver(void);

    // define os identificadores das funções do driver
    enum {
        DISP7SEG_INTEGER,
        DISP7SEG_ON,
        DISP7SEG_END
    } ;

    // função de atualização de valor mostrado no display de 7 segmentos
    char atualizaDisplay(void) ;

#endif
