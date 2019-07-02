// -----------------------------------------------------------------------
//   drvSerial.c -> implementação do driver da serial
//   Autor: Lucas Carvalho de Sousa
//          lucas.c.s at unifei.edu.br
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

#include "drvSerial.h"

// variável utilizada para auto-referência do driver
static driver thisDriver ;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[SERIAL_END] ;

// resposta da chamada de outro driver
static process *callBack ;

// valor armazenado da última transmissão de dados via serial
static unsigned char valueTx ;

// valor armazenado da última recepção de dados via serial
static unsigned char valueRx ;

// indica se o buffer da serial está cheio ou não
static unsigned char bufferFull ;

char startSerialTx(void *parameters) {
    // verifica se existe algum dado que ainda não foi escrito na serial
    if (bufferFull == 0) {
        valueTx = (unsigned char)parameters ;
        
        // indica que existe um dado a ser escrito na serial
        bufferFull = 1 ;

        // ativa interrupção de transmissão EUSART
        BitClr(PIE1, 4) ;

        return OK ;
    }
    return FAIL ;
}

// retorna o valor lido na serial em uma variável passada como parâmetro
char serialRxReturnLastValue(void* parameters) {
    (*(unsigned char*)parameters) = valueRx ;
    return OK ;
}

// lê o buffer de recepção EUSART
void serialRxISR(void* parameters) {
    valueRx = RCREG ;
    kernelAddProc(callBack) ;
}

// rotina de tratamento de interrupção da transmissão de dados da serial
void serialTxISR() {
    // desativa interrupção de transmissão EUSART
    BitClr(PIE1, 4) ;

    // escreve no buffer de transmissão EUSART
    TXREG = valueTx ;

    // indica que não existe dado a ser escrito na serial
    bufferFull = 0 ;
}

// habilita recepçsão de dados serial por interrupção
char enableSerialRxInterrupt(void* parameters) {
    // configura a função de retorno para interrupção de recepção EUSART
    callDriver(DRV_INTERRUPT, INT_SERIAL_RXSET, (void*)serialRxISR) ;

    // configura a função de retorno para o programa principal em caso de um tratamento de interrupção
    callBack = parameters ;

    //ativa interrupção de recepção EUSART
    BitSet(PIE1, 5) ;

    return OK ;
}

// habilita tranmissão de dados serial por interrupção
char enableSerialTxInterrupt(void* parameters) {
    //seta a função de retorno para o driver de serial em caso de uma interrupção
    callDriver(DRV_INTERRUPT, INT_SERIAL_TXSET, (void*)serialTxISR) ;

    // A interrupção de transmissão EUSART ocorre quando o buffer de transmissão esta preparado para _
    // receber um dado (buffer vazio), ou seja, enquanto não enchermos o buffer (operação de escrita) a interrupção ocorrerá, por _
    // isso a linha abaixo esta comentada.
    //BitSet(PIE1, 4) ;
    return OK ;
}

// inicialização do driver
char initSerial(void* parameters) {
    thisDriver.drv_id = *((char*) parameters) ;
    this_functions[SERIAL_WRITE] = startSerialTx ;
    this_functions[SERIAL_INT_RX_EN] = enableSerialRxInterrupt ;
    this_functions[SERIAL_INT_TX_EN] = enableSerialTxInterrupt ;
    this_functions[SERIAL_LAST_VALUE] = serialRxReturnLastValue ;

    // configura a serial:
    // transmissão de dados da serial
    TXSTA = 0b00101100 ;

    // recepção de dados da serial
    RCSTA = 0b10010000 ;

    // sistema de velocidade da serial
    BAUDCON = 0b00001000 ;

    // velocidade de transmissão para 57600bps
    SPBRGH = 0x00 ;
    SPBRG = 0x42 ;

    //pino de recepção de dados
    BitSet(TRISC,6) ;

    // pino de envio de dados
    BitClr(TRISC,7) ;

    // indica que não há informação no buffer
    bufferFull = 0 ;

    // inicializa, por padrão, as interrupção geradas pelo driver desativadas
    BitClr(PIE1, 5) ;
    BitClr(PIE1, 4) ;

    return OK ;
}

// função de auto-referência
driver* getSerialDriver(void) {
    thisDriver.drv_init = initSerial ;
    thisDriver.func_ptr = (ptrFuncDrv*) &this_functions ;
    return &thisDriver ;
}

