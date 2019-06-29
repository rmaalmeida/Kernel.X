// -----------------------------------------------------------------------
//   drvAdc.c -> implementação do driver do conversor A/D
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

#include "drvAdc.h"

// variável utilizada para auto-referência do driver
static driver thisDrivers;

// quantidade de funções neste driver
static ptrFuncDrv this_functions[ADC_END];

// resposta da chamada de outro driver
static process *callBack;

// valor armazenado da última conversão A/D
static unsigned int value;

// inicializa a conversão da informação analógica em digital
char startConversion(void* parameters){
    // recebe a função de retorno de interrupção a ser executada após esta pelo programa principal
    callBack = parameters;

    // inicia conversão
    ADCON0 |= 0b00000010;

    return OK;
}

// retorna na variável recebida o resultado da última conversão A/D
char adcReturnLastValue(void* parameters){
    (*(unsigned int*)parameters) = value;
    return OK;
}

// rotina de tratamento de interrupção do conversor A/D
void adcISR(void){
    value = ADRESH;
    value <<= 8;
    value += ADRESL;
    BitClr(PIR1,6);
    kernelAddProc(callBack);
}

// permite que o conversor A/D gere interrupções
// Por padronização, funções de drivers recebem parâmetros, mesmo que não os utilizem.
char enableAdcInterrupt(void* parameters){
        callDriver(DRV_INTERRUPT,INT_ADC_SET,(void*)adcISR);
        BitSet(PIE1, 6) ;
        return OK;
}

// inicialização do driver
char initAdc(void *parameters) {
    thisDrivers.drv_id = *((char*) parameters);
    this_functions[ADC_START] = startConversion;
    this_functions[ADC_INT_EN] = enableAdcInterrupt;
    this_functions[ADC_LAST_VALUE] = adcReturnLastValue;

    // configura o bit 0 como entrada
    BitSet(TRISA,0);

    //seleciona o canal 0 e liga o conversor A/D
    ADCON0 = 0b00000001;

    // apenas o pino AN0 será analogico, e a referencia será baseada na fonte
    ADCON1 = 0b00001110;

    // FOSC /32. Alinhamento à direita e tempo de conv = 12 TAD
    // TODO comentário???
    ADCON2 = 0b10101010;

    // desativa a interrupção do conversor A/D
    BitClr(PIE1, 6) ;

    return OK;
}

// função de auto-referência
driver* getAdcDriver(void) {
    thisDrivers.drv_init = initAdc;
    thisDrivers.func_ptr = this_functions;
    return &thisDrivers;
}
