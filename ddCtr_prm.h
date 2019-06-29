// -----------------------------------------------------------------------
//   ddCtr_prm.h -> parâmetros da controladora, e drivers implementados
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

#ifndef ddCtr_prm_h
    #define ddCtr_prm_h

    // quantidade máxima de drivers disponíveis para o sistema simultaneamente
    #define QNTD_DRV 20

    // é necessário para incluir todos os arquivos de drivers
    #include "drvLed.h"
    #include "drvInterrupt.h"
    #include "drvTimer.h"
    #include "drvLcd.h"
    #include "drvAdc.h"
    #include "drvSerial.h"
    #include "drvTeclado.h"
    #include "drvDisp7seg.h"

    // este enumerado auxilia o desenvolvedor/usuário a acessar os drivers
    enum {
        DRV_LED,
        DRV_INTERRUPT,
        DRV_TIMER,
        DRV_LCD,
        DRV_ADC,
        DRV_SERIAL,
        DRV_TECLADO,
        DRV_DISP7SEG,
        DRV_END /* DRV_END deve sempre ser o último, para facilitar o controle da quantidade de drivers */
    };

    // as funções para obter os drivers devem ser inseridas na mesma ordem que o enumerado acima
    static ptrGetDrv drvGetFunc[DRV_END] = {
        getLedDriver,
        getInterruptDriver,
        getTimerDriver,
        getLCDDriver,
        getAdcDriver,
        getSerialDriver,
        getTecladoDriver,
        getDisp7segDriver
    };

#endif // ddCtr_prm_h

