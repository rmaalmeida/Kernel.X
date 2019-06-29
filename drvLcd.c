// -----------------------------------------------------------------------
//   drvLcd.c -> implementação do driver do display LCD
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

//Definições do LCD
#define RS 0 // pino de seleção de registro do LCD
#define EN 1 // pino de habilitação do LCD, para futura leitura/escrita
#define RW 2 // pino de leitura/escrita do LCD

// número de colunas disponível no display LCD
#define COLUMNS 16

//protótipos das funções locais

// variável utilizada para auto-referência do driver
static driver thisDriver;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[LCD_END];

// caracteres escritos em uma linha, de acordo com o número de colunas
static unsigned int lastLine[COLUMNS] ;

// linha da posição atual do cursor
static unsigned char posX ;

// coluna da posição atual do cursor
static unsigned char posY ;

// gera um delay na resposta do LCD de 40us
void Delay40us(void) {
    // para um cristal de 8 MHz, cada instrução gasta 0.5 us: 40/0.5 = 80 instruções
    unsigned char i;
    for (i = 0; i < 25; i++); //3u + 3u * 25 = 78 us
}

// gera um delay na resposta do LCD de 2ms
void Delay2ms(void) {
    unsigned char i;
    for (i = 0; i < 200; i++) {
        Delay40us();
    }
}

// envia um comando ao display LCD
char sendCommand(void *parameters) {
    // comando
    BitClr(PORTE, RS);

    // habilita escrita
    BitClr(PORTE, RW);

    // insere o caracter na linha de comunicação do display LCD
    PORTD = (unsigned char) parameters;

    // habilita leitura
    BitSet(PORTE, EN);
    Delay2ms();

    //termina leitura
    BitClr(PORTE, EN);

    //deixa em nivel baixo
    BitClr(PORTE, RS);

    //deixa em nivel baixo
    BitClr(PORTE, RW);
    Delay40us();

    return OK;
}

// pula uma linha no LCD
char changeLine(void *parameters) {
    if ((unsigned char) parameters == 1) {
        sendCommand(0x80);
    }
    if ((unsigned char) parameters == 2) {
        sendCommand(0xC0);
    }
    return OK;
}

// apaga todos os caracteres e símbolos escritos no LCD
char clearLCD() {
    sendCommand(0x01) ;
    return OK ;
}

// envia um caracter para o display LCD
char sendData(void *parameters) {
    unsigned char character = (unsigned char) parameters ;
    unsigned char i ;

    if (posX > 15) {
        if (posY == 1) {
            posY = 0 ;
            posX = 0 ;
            clearLCD() ;
            changeLine(1) ;

            for (i = 0; i < COLUMNS; i++) {
                sendData(lastLine[i]) ;
            }
            
        }

        posY = 1 ;
        posX = 0 ;
        changeLine(2) ;
    }

    //dados
    BitSet(PORTE, RS);
    
    // habilita escrita
    BitClr(PORTE, RW);
    PORTD = character ;

    //habilita leitura
    BitSet(PORTE, EN);
    Delay40us();

    //termina leitura
    BitClr(PORTE, EN);

    //deixa em nivel baixo
    BitClr(PORTE, RS);

    //deixa em nivel baixo
    BitClr(PORTE, RW);
    Delay40us();

    if (posY == 1) {
        lastLine[posX] = character ;
    }
    posX++ ;

    return OK;
}

// apaga um caracter do display LCD
char deleteChar() {
    unsigned char pos ;

    //posiciona o cursor uma posição anterior à inicial
    posX -= 1 ;
    if (posY == 1) {
        pos = 0xC0 + posX ;
    }
    else {
        pos = 0x80 + posX ;
    }
    sendCommand(pos) ;

    //escreve um caracter vazio no display LCD
    sendData(' ') ;
    
    //posiciona novamente o cursor uma posição anterior à inicial
    posX -= 1 ;
    sendCommand(pos) ;
    
    return OK ;
}

// envia um conjunto de caracteres para o display LCD
char stringWrite(void *parameters) {
    unsigned char i = 0 ;
    unsigned char* str = (unsigned char*)parameters ;
    while (str[i]) {
        sendData(str[i]) ;
        i++ ;
    }
    return OK ;
}

// envia um número para o display LCD
char integerWrite(void *parameters) {
    sendData(((unsigned int) parameters / 10000) % 10 + 48);
    sendData(((unsigned int) parameters / 1000) % 10 + 48);
    sendData(((unsigned int) parameters / 100) % 10 + 48);
    sendData(((unsigned int) parameters / 10) % 10 + 48);
    sendData(((unsigned int) parameters) % 10 + 48);
    return OK;
}

// cria um símbolo e o escreve no display LCD
void LCD_build(void){
	char i;
/*
1: 0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x1, 0x4
2: 0xe, 0x1f, 0x4, 0x4, 0x1f, 0xe, 0x11, 0x1f
3: 0x0, 0x10, 0x18, 0x18, 0x18, 0x18, 0x10, 0x4
4: 0xc, 0x3, 0x0, 0x0, 0x0, 0x3, 0xc, 0x4
5: 0x0, 0x0, 0x1b, 0x4, 0x1b, 0x0, 0x0, 0x0
6: 0x6, 0x18, 0x0, 0x0, 0x0, 0x18, 0x6, 0x2
*/
	char defcon[48] = {0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x1, 0x4,
		               0xe, 0x1f, 0x4, 0x4, 0x1f, 0xe, 0x11, 0x1f,
		               0x0, 0x10, 0x18, 0x18, 0x18, 0x18, 0x10, 0x4,
		               0xc, 0x3, 0x0, 0x0, 0x0, 0x3, 0xc, 0x4,
		               0x0, 0x0, 0x1b, 0x4, 0x1b, 0x0, 0x0, 0x0,
		               0x6, 0x18, 0x0, 0x0, 0x0, 0x18, 0x6, 0x2};
	
        // primeira posição
        sendCommand(0x40);

        for(i=0;i<48;i++)
	{
		sendData(defcon[i]);
	}

        sendCommand(0x80);
}

// inicialização do driver
char initLCD(void *parameters) {
    thisDriver.drv_id = *(char*) parameters;
    this_functions[LCD_COMMAND] = sendCommand;
    this_functions[LCD_CHAR] = sendData;
    this_functions[LCD_INTEGER] = integerWrite;
    this_functions[LCD_LINE] = changeLine;
    this_functions[LCD_STRING] = stringWrite ;
    this_functions[LCD_DELETE] = deleteChar ;
    this_functions[LCD_CLEAR] = clearLCD ;

    // garante inicialização do LCD
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();
    Delay2ms();

    // configurações de direção dos terminais
    BitClr(TRISE, RS);
    BitClr(TRISE, EN);
    BitClr(TRISE, RW);
    TRISD = 0x00;
    ADCON1 = 0b00001110;

    // Configura o display:
    // 8bits, 2 linhas, caracteres formados por células 5x8
    sendCommand(0x38);

    // modo incremental: insere caracter, vai para a célula seguinte
    sendCommand(0x06);

    // backlight ligada; cursor piscante ligado
    sendCommand(0x0F);

    // zera o buffer do display LCD
    sendCommand(0x03);

    // apaga todos os caracteres e símbolos escritos no LCD
    sendCommand(0x01);

    // posição inicial
    sendCommand(0x80);

    posX = 0 ;
    posY = 0 ;

    return OK;
}

driver* getLCDDriver(void) {
    thisDriver.drv_init = initLCD;
    thisDriver.func_ptr = (ptrFuncDrv*) & this_functions;
    return &thisDriver;
}
