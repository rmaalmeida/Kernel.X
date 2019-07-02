// -----------------------------------------------------------------------
//   drvAdc.h -> header das definições do driver do conversor A/D
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

#ifndef ADC_H
    #define ADC_H
    #include "ddCtr_types.h"
    #include "kernel_prm.h"
    #include "kernel.h"

    //apenas retorna o "objeto" do driver
    driver* getAdcDriver(void);

    // define os identificadores das funções do driver
    enum {
        ADC_START,
        ADC_INT_EN,
        ADC_LAST_VALUE,
        ADC_END
    };

#endif
