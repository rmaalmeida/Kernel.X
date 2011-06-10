// -----------------------------------------------------------------------
//   config.h -> defini��es do microcontrolador para o compilador SDCC
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


#ifndef CONFIG_H
    #define CONFIG_H

//configurações do microcontrolador
code char at 0x300000 CONFIG1L = 0x01; // No prescaler used
code char at 0x300001 CONFIG1H = 0x0C; // HS: High Speed Cristal
code char at 0x300003 CONFIG2H = 0x00; // Disabled-Controlled by SWDTEN bit
code char at 0x300006 CONFIG4L = 0x00; // Disabled low voltage programming

#endif