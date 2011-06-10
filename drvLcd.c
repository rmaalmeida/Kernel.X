// -----------------------------------------------------------------------
//   LCD.c -> Visa permitir acesso ao LCD
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


#include "drvLcd.h"
#include "basico.h"

#define RS 0
#define EN 1
#define RW 2

static driver thisDriver;
static driver_functions this_functions[LCD_END];

//internal delays

void Delay40us(void) {
    //para um cristal de 8MHz cada instrucao
    //gasta 0,5 us: 40/0,5 = 80 instrucoes
    unsigned char i;
    for (i = 0; i < 25; i++); //3 + 3 * 25 = 78
}

void Delay2ms(void) {
    unsigned char i;
    for (i = 0; i < 200; i++) {
        Delay40us();
    }
}

char sendCommand(void *parameters) {
    BitClr(PORTE, RS); //comando
    BitClr(PORTE, RW); // habilita escrita

    PORTD = (unsigned char) parameters;
    BitSet(PORTE, EN); //habilita leitura
    Delay2ms();
    BitClr(PORTE, EN); //termina leitura
    BitClr(PORTE, RS); //deixa em nivel baixo
    BitClr(PORTE, RW); //deixa em nivel baixo
    Delay40us();
    return FIM_OK;
}

char changeLine(void *parameters) {
    if ((unsigned char) parameters == 1) {
        sendCommand(0x80);
    }
    if ((unsigned char) parameters == 2) {
        sendCommand(0xC0);
    }
    return FIM_OK;
}

char sendData(void *parameters) {
    BitSet(PORTE, RS); //dados
    BitClr(PORTE, RW); // habilita escrita
    PORTD = (unsigned char) parameters;
    BitSet(PORTE, EN); //habilita leitura
    Delay40us();
    BitClr(PORTE, EN); //termina leitura
    BitClr(PORTE, RS); //deixa em nivel baixo
    BitClr(PORTE, RW); //deixa em nivel baixo
    Delay40us();
    return FIM_OK;
}

char intWrite(void *parameters) {
    sendData(((unsigned int) parameters / 10000) % 10 + 48);
    sendData(((unsigned int) parameters / 1000) % 10 + 48);
    sendData(((unsigned int) parameters / 100) % 10 + 48);
    sendData(((unsigned int) parameters / 10) % 10 + 48);
    sendData(((unsigned int) parameters) % 10 + 48);
    return FIM_OK;
}

char initLCD(void *parameters) {

    thisDriver.drv_id = *(char*) parameters;
    this_functions[LCD_COMMAND].func_ptr = sendCommand;
    this_functions[LCD_CHAR].func_ptr = sendData;
    this_functions[LCD_INTEGER].func_ptr = intWrite;
    this_functions[LCD_LINE].func_ptr = changeLine;
    

    // garante inicializacao do LCD
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();

    // configuracoes de direcao dos terminais
    BitClr(TRISE, RS); //RS
    BitClr(TRISE, EN); //EN
    BitClr(TRISE, RW); //RW
    TRISD = 0x00; //dados
    ADCON1 = 0b00001110; //apenas

    //configura o display
    sendCommand(0x38); //8bits, 2 linhas, 5x8
    sendCommand(0x06); //modo incremental
    sendCommand(0x0F); //display e cursor on, com blink
    sendCommand(0x03); //zera tudo
    sendCommand(0x01); //limpar display
    sendCommand(0x80); //posicao inicial
    
    return FIM_OK;
}

driver* getLCDDriver(void) {
    //to ensure that at least the init function will be known
    thisDriver.drv_init = initLCD;
    thisDriver.func_ptr = (driver_functions*) & this_functions;
    return &thisDriver;
}
