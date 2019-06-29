// -----------------------------------------------------------------------
//   ddCtr.h -> header das funções de gerenciamento dos drivers de dispositivos
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

#ifndef ddCtr_h
    #define ddCtr_h

    #include "ddCtr_prm.h"
    #include "ddCtr_types.h"
    #include "basico.h"

char initCtrDrv(void);
char initDriver(char newDriver);
char callDriver(char drv_id, char func_id, void *parameters);

#endif // ddCtr_h

