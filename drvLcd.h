// -----------------------------------------------------------------------
//   LCD.h -> Visa permitir acesso ao LCD
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

#ifndef LCD_H
    #define LCD_H

    #include "ddCtr_types.h"

enum {
    LCD_COMMAND, LCD_CHAR, LCD_LINE, LCD_INTEGER, LCD_END
};

//apenas retorna o "objeto" do driver
driver* getLCDDriver(void);

#endif