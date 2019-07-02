// -----------------------------------------------------------------------
//   drvTimer.h -> header das definições do driver do Timer 0
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

#ifndef DRVTIMER_H
    #define DRVTIMER_H
    #include "basico.h"
    #include "ddCtr_types.h"

    //apenas retorna o "objeto" do driver
    driver* getTimerDriver(void);

    // define os identificadores das funções do driver
    enum {
        TMR_IS_END,
        TMR_WAIT,
        TMR_RESET,
        TMR_START,
        TMR_INT_EN,
        TMR_END
    };

#endif //DRVTIMER_H

