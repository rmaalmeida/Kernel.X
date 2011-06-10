// -----------------------------------------------------------------------
//   kernel.h -> header das fun��es para gerenciamento do kernel
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


#ifndef KERNEL_H
    #define KERNEL_H

    #include "kernel_prm.h"
    #include "kernel_types.h"

//funcoes do kernel
char kernelInit(void);
char kernelAddProc(process *func);
void kernelLoop(void);
void kernelClock(void);
#endif //KERNEL_H