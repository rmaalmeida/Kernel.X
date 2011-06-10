/*
   File:   ctrdrv.h
   Author: rmaax

   Created on 13 de Abril de 2011, 10:06
 */

#ifndef ddCtr_h
    #define ddCtr_h

    #include "ddCtr_prm.h"
    #include "ddCtr_types.h"

char initCtrDrv(void);
char callDriver(char drv_id, char func_id, void *parameters);
char initDriver(char newDriver);

#endif // ddCtr_h
