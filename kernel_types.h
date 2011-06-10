/*
   File:   kernel_types.h
   Author: rmaax

   Created on 14 de Abril de 2011, 10:03
 */

#ifndef kernel_types_h
    #define kernel_types_h

//declaracao do tipo ponteiro para funcao
typedef char(*ptrFunc)(void);

//estrutura do processo
typedef struct {
    ptrFunc function;
    unsigned int period;
    signed int start;
} process;

#endif // kernel_types_h
