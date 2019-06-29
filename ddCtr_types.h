// -----------------------------------------------------------------------
//   ddCtr_types.h -> definições de tipos especiais da controladora de drivers
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

#ifndef ddCtr_types_h
    #define ddCtr_types_h

    typedef char(*ptrFuncDrv)(void *parameters);

    //estrutura do driver
    typedef struct {
        char drv_id; // identificador do driver
        ptrFuncDrv drv_init; // ponteiro da função de inicialização do driver
        ptrFuncDrv *func_ptr; // vetor dos demais ponteiros de funções do driver
    } driver;

    // definição de um ponteiro de função para drivers (com número indefinido de parâmetros)
    typedef driver* (*ptrGetDrv)(void);

#endif // ddCtr_types_h

