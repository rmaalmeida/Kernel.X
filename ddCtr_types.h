/*
   File:   ctrdrv_types.h
   Author: rmaax

   Created on 14 de Abril de 2011, 08:32
 */

#ifndef ctrdrv_types_h
    #define ctrdrv_types_h

typedef char(*ptrFuncDrv)(void *parameters);
//estrutura do processo

typedef struct {
    //char func_id;
    ptrFuncDrv func_ptr;
} driver_functions;

typedef struct {
    char drv_id;
    //char func_qntd;
    driver_functions *func_ptr;
    ptrFuncDrv drv_init;
} driver;

typedef driver* (*ptrGetDrv)(void);

#endif // ctrdrv_types_h
