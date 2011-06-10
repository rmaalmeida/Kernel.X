/*
   File:   drvGenerico.h
   Author: rmaax

   Created on 13 de Abril de 2011, 11:35
 */

#ifndef drvGenerico_h
    #define drvGenerico_h
    #include "ddCtr_types.h"

enum {
    GEN_PORTD, GEN_END
};

//apenas retorna o "objeto" do driver
driver* getGenericoDriver(void);
#endif // drvGenerico_h
