// -----------------------------------------------------------------------
//   config.h -> configurações do microcontrolador PIC18F4550 (compilador SDCC)
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
code char at 0x300000 CONFIG1L = 0x00 ; // sem 'prescale' no PLL
code char at 0x300001 CONFIG1H = 0x0C ; // oscilador 'HS'
code char at 0x300002 CONFIG2L = 0x1F ; // Power-up ativo e Brown-out ativado em configuração mínima
code char at 0x300003 CONFIG2H = 0b00011110 ; // controle do 'Watchdog' via bit 'SWDTEN' e 'postscale' 1:256
code char at 0x300005 CONFIG3H = 0x83 ; //Master Clear Reset ativo, RE3 desabilitado
code char at 0x300006 CONFIG4L = 0b10000000 ; // programção em baixa tensão desativada
code char at 0x300008 CONFIG5L = 0x0F ; // proteção de código desativada
code char at 0x300009 CONFIG5H = 0xC0 ; // proteção de código da EEPROM desativada
code char at 0x30000A CONFIG6L = 0x0F ; // proteção contra escrita desativada
code char at 0x30000B CONFIG6H = 0xE0 ; // proteção contra escrita na EEPROM desativada
code char at 0x30000C CONFIG7L = 0x0F ; //
code char at 0x30000D CONFIG7H = 0x40 ; //

//demais configurações padrão. Vide datasheet.
#endif

