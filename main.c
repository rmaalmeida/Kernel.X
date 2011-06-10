// -----------------------------------------------------------------------
//   main.c -> rotina principal
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
#include "basico.h"
#include "config.h"

#include "kernel.h"

//prototipos dos processos
char portd_func(void);
char adc_func(void);
char adc_callback(void);

//Interrupção

void timerISR(void) {
    callDriver(DRV_TIMER, TMR_RESET, 1000);
    kernelClock();
}

void main(void) {

    //criação dos processos
    
    static process proc_portd = {portd_func, 100, 0};
    static process proc_adc = {adc_func, 1000, 0};
 

    //inicialização do sistema
    kernelInit();

    initDriver(DRV_TIMER);
    initDriver(DRV_INTERRUPT);
    initDriver(DRV_GEN);
    initDriver(DRV_LCD);
    initDriver(DRV_ADC);


    callDriver(DRV_TIMER, TMR_START, 0);

    //enabling all interrupts
    callDriver(DRV_TIMER, TMR_INT_EN, 0);
    callDriver(DRV_ADC, ADC_INT_EN, 0);
    callDriver(DRV_INTERRUPT, INT_TIMER_SET, (void*) timerISR);
    callDriver(DRV_INTERRUPT, INT_ENABLE, 0);

    //inserção dos processos no kernel
    kernelAddProc(&proc_adc);
    kernelAddProc(&proc_portd);
    //Start do kernel
    kernelLoop();
}

//implementação dos processos

char portd_func(void) {
    static unsigned char v;
    callDriver(DRV_GEN, GEN_PORTD, &v);
    v++;
    return REPETIR;
}

char adc_func(void) {
    static process proc_adc_callback = {adc_callback, 0, 0};
    callDriver(DRV_ADC,ADC_START,&proc_adc_callback);
    return REPETIR;
}

char adc_callback(void) {
    unsigned int resp;
    callDriver(DRV_ADC,ADC_LAST_VALUE,&resp);
    callDriver(DRV_LCD,LCD_LINE,1);
    callDriver(DRV_LCD,LCD_INTEGER,resp);
    return FIM_OK;
}