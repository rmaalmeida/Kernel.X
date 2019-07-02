// -----------------------------------------------------------------------
//   ddCtr.c -> funções de gerenciamento dos drivers de dispositivos
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

#include "ddCtr.h"

static driver* driversLoaded[QNTD_DRV]; //vetor com os drivers iniciados
static char qntDrvLoaded;

//inicializa a controladora de drivers
char initCtrDrv(void) {
    qntDrvLoaded = 0;
    return OK;
}

//inicializa um determinado driver
char initDriver(char newDriver) {
    char resp = FAIL;
    if (qntDrvLoaded < QNTD_DRV) {
        driversLoaded[qntDrvLoaded] = drvGetFunc[newDriver]();
        resp = driversLoaded[qntDrvLoaded]->drv_init(&newDriver);
        qntDrvLoaded++;
    }
    return resp;
}

//transfere a um determinado driver uma função a ser executada, em conjunto com seus parâmetros
char callDriver(char drv_id, char func_id, void *parameters) {
    char i;

    for (i = 0; i < qntDrvLoaded; i++) {
        if (drv_id == driversLoaded[i]->drv_id) {
            return driversLoaded[i]->func_ptr[func_id](parameters);
        }
    }
    return DRV_FUNC_NOT_FOUND;
}

