#ifndef ADC_H
	#define ADC_H
    #include "ddCtr_types.h"


enum {
    ADC_START, ADC_INT_EN, ADC_LAST_VALUE, ADC_END
};

//apenas retorna o "objeto" do driver
driver* getAdcDriver(void);

#endif