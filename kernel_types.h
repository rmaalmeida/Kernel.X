// -----------------------------------------------------------------------
//   kernel_types.h -> definições de tipos especiais para o kernel
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

#ifndef kernel_types_h
    #define kernel_types_h

    //declaracao do tipo ponteiro para funcao
    typedef char(*ptrFunc)(void);

    //estrutura do processo
    typedef struct {
        ptrFunc function;
        unsigned int period;
        signed int start;
    } process;

#endif // kernel_types_h

