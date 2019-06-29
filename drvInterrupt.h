// -----------------------------------------------------------------------
//   drvInterrupt.h -> header das definições do driver de interrupção
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

#ifndef INT_H
    #define INT_H
    #include "basico.h"
    #include "ddCtr_types.h"

    /* O driver de interrupção deve possuir funcionalidades que permitam que outros
     * drivers possam se utilizar de interrupções, então, cada função de interrupção
     * de cada driver deve ser inserida aqui. */

    //apenas retorna o "objeto" do driver
    driver* getInterruptDriver(void);

    // define os identificadores das funções do driver
    enum {
        INT_ENABLE,
        INT_ADC_SET,
        INT_SERIAL_RXSET,
        INT_SERIAL_TXSET,
        INT_TIMER_SET,
        INT_TECLADO_SET,
        INT_END
    };

#endif // drvInterrupt_H
