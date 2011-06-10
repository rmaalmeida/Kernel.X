/*
   File:   ctrdrv.c
   Author: rmaax

   Created on 13 de Abril de 2011, 10:06
 */
#include "ddCtr.h"
#include "basico.h"

static driver* driversLoaded[QNTD_DRV];
static char qntDrvLoaded;

char initCtrDrv(void) {
    qntDrvLoaded = 0;
    return FIM_OK;
}

char initDriver(char newDriver) {
    char resp = FIM_FALHA;
    if (qntDrvLoaded < QNTD_DRV) {
        driversLoaded[qntDrvLoaded] = drvGetFunc[newDriver]();
        resp = driversLoaded[qntDrvLoaded]->drv_init(&newDriver);
        qntDrvLoaded++;
    }
    return resp;
}

char callDriver(char drv_id, char func_id, void *parameters) {
    char i, j;

    for (i = 0; i < qntDrvLoaded; i++) {
        if (drv_id == driversLoaded[i]->drv_id) {
            //for(j=0;j<drivers[i]->func_qntd;j++)
            {
                //if (drivers[i]->func_ptr[j].func_id == func_id)
                {

                    return driversLoaded[i]->func_ptr[func_id].func_ptr(parameters);
                }
            }
        }
    }
    return DRV_FUNC_NOT_FOUND;
}