#include "drvAdc.h"
#include "basico.h"
#include "kernel_types.h"
#include "kernel.h"

static driver thisDrivers;
static driver_functions this_functions[ADC_END];
static process *callBack;
static unsigned int value;

char startConversion(void* parameters){
    callBack = parameters;
	ADCON0 |= 0b00000010;	 //inicia conversao
        
        return FIM_OK;
}

char adcReturnLastValue(void* parameters){
    (*(unsigned int*)parameters) = value;
    return FIM_OK;
}

void adcISR(void){
    value = ADRESH;
    value <<= 8;
    value += ADRESL;
    BitClr(PIR1,6);
    kernelAddProc(callBack);
}

char enableAdcInterrup(void* parameters){
        callDriver(DRV_INTERRUPT,INT_ADC_SET,(void*)adcISR);
	BitClr(PIE1,6);
        return FIM_OK;
}

char initAdc(void *parameters) {

    thisDrivers.drv_id = *((char*) parameters);
    this_functions[ADC_START].func_ptr = startConversion;
    this_functions[ADC_INT_EN].func_ptr = enableAdcInterrup;
    this_functions[ADC_LAST_VALUE].func_ptr = adcReturnLastValue;

    BitSet(TRISA,0); //seta o bit 0 como entrada

    ADCON0 = 0b00000001; //seleciona o canal 0 e liga o ad
    ADCON1 = 0b00001110; //apenas AN0 � analogico, a referencia � baseada na fonte
    ADCON2 = 0b10101010; //FOSC /32, Alinhamento � direita e tempo de conv = 12 TAD

    return FIM_OK;
}

driver* getAdcDriver(void) {
    //to ensure that at least the init function will be known
    thisDrivers.drv_init = initAdc;
    thisDrivers.func_ptr = this_functions;
    return &thisDrivers;
}