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

#include "config.h"
#include "kernel.h"

// protótipos dos processos
char led_func(void);
char LCD_func(void);
char adc_func(void);
char adc_callback(void);
char serial_func(void) ;
char serialRx_callback(void);
char teclado_callback(void);
char disp7seg_add_func(void);

unsigned char disp7seg ;
unsigned char i ;

// rotina de tratamento de interrupção do Timer 0
void timerISR(void) {
    callDriver(DRV_TIMER, TMR_RESET, 1000);
    kernelClock();
}

// programa principal
void main(void) {
    //criação dos processos
    static process proc_led = {led_func, 1001, 0};
    static process proc_adc = {adc_func, 4000, 0} ;
    static process proc_serial = {serial_func, 1000, 0} ;
    static process proc_serialRx_callback = {serialRx_callback, 0, 0} ;
    static process proc_teclado_callback = {teclado_callback, 0, 0} ;
    static process proc_add_disp7seg = {disp7seg_add_func, 1000, 0} ;
    static process proc_LCD = {LCD_func, 300, 0} ;

    disp7seg = 0 ;
    i = 0 ;

    //inicialização do sistema
    kernelInit();

    initDriver(DRV_TIMER);
    initDriver(DRV_INTERRUPT);
    initDriver(DRV_LED);
    initDriver(DRV_ADC);
    initDriver(DRV_LCD);
    initDriver(DRV_SERIAL);
    initDriver(DRV_TECLADO) ;
    initDriver(DRV_DISP7SEG) ;

    callDriver(DRV_TIMER, TMR_START, 0);

    // habilitando todas as interrupções
    callDriver(DRV_TIMER, TMR_INT_EN, 0);
    
    //callDriver(DRV_SERIAL, SERIAL_INT_RX_EN, (void*) &proc_serialRx_callback) ;

    //callDriver(DRV_SERIAL, SERIAL_INT_TX_EN, 0) ;
    //callDriver(DRV_ADC, ADC_INT_EN, 0);
    callDriver(DRV_INTERRUPT, INT_TIMER_SET, (void*) timerISR) ;
    //callDriver(DRV_TECLADO, TECLADO_INT_EN, (void*) &proc_teclado_callback) ;
    callDriver(DRV_INTERRUPT, INT_ENABLE, 0);
    //callDriver(DRV_DISP7SEG, DISP7SEG_ON, 0) ;

    // inserção dos processos no kernel
    //kernelAddProc(&proc_led);
    kernelAddProc(&proc_LCD);
    //kernelAddProc(&proc_adc);
    //kernelAddProc(&proc_serial);
    //kernelAddProc(&proc_serialRx_callback);
    //kernelAddProc(&proc_add_disp7seg);
    //kernelAddProc(&proc_teclado_callback);

    //Start do kernel
    kernelLoop();
}

//implementação dos processos
char serial_func(void) {
    callDriver(DRV_SERIAL, SERIAL_WRITE, (void*)'c') ;
    return REPEAT;
}

char led_func(void) {
    callDriver(DRV_LED, LED_PORTD, (void*)i);
    return REPEAT;
}

char LCD_func(void) {
    unsigned char* str = "Oi Bete, tudo bem?" ;
    if (str[i]) {
        if (i > 1) {
            callDriver(DRV_LCD, LCD_DELETE, 0) ;
        }
        callDriver(DRV_LCD, LCD_CHAR, (void*)str[i]) ;
        i++ ;
    }
    return REPEAT ;
}

char adc_callback(void) {
    unsigned int resp2;
    callDriver(DRV_ADC, ADC_LAST_VALUE, &resp2);
    callDriver(DRV_LCD, LCD_LINE, 1);
    callDriver(DRV_LCD, LCD_INTEGER, resp2);
    return OK;
}

char adc_func(void) {
    static process proc_adc_callback = {adc_callback, 0, 0};
    callDriver(DRV_ADC, ADC_START, &proc_adc_callback);
    return REPEAT;
}

char serialRx_callback(void) {
    unsigned char resp2 ;
    callDriver(DRV_SERIAL, SERIAL_LAST_VALUE, &resp2) ;
    callDriver(DRV_LCD, LCD_LINE, 1) ;
    callDriver(DRV_LCD, LCD_CHAR, resp2) ;
    return OK ;
}

char teclado_callback(void) {
    unsigned char ascii ;
    callDriver(DRV_TECLADO, VALUE_TECLADO_ASCII, &ascii) ;
    callDriver(DRV_LCD, LCD_CHAR, ascii) ;
    return OK ;
}

char disp7seg_add_func(void) {
    callDriver(DRV_DISP7SEG, DISP7SEG_INTEGER, (void*)disp7seg) ;
    disp7seg++ ;
    return REPEAT ;
}

