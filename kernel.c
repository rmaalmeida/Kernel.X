// -----------------------------------------------------------------------
//   kernel.c -> fun��es para gerenciamento do kernel
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


/*
Do manual do SDCC (http://sdcc.sourceforge.net/doc/sdccman.html/node183.html):

"structures and unions cannot be assigned values directly, cannot be passed as function parameters or assigned to each other and cannot be a return value from a function"
 */

#include "kernel.h"
#include "basico.h"
#include "ddCtr.h"
//variaveis do kernel
static process* pool[SLOT_SIZE];
static volatile unsigned char start;
static volatile unsigned char end;

char kernelInit(void) {
    //the kernel initializates the driver controler
    initCtrDrv();
    start = 0;
    end = 0;
    return FIM_OK;
}

void kernelLoop(void) {
    unsigned char j;
    unsigned char next;
    process *tempProc;
    for (;;) {
        if (start != end) {
            //Procura a pr�xima fun��o a ser executada com base no tempo
            j = (start + 1) % SLOT_SIZE;
            next = start;
            while (j != end) {
                if ((pool[j]->start) < (pool[next]->start)) {
                    next = j;
                }
                j = (j + 1) % SLOT_SIZE; //para poder incrementar e ciclar o j
            }

            //troca e coloca o processo com menor tempo como o proxima
            tempProc = pool[next];
            pool[next] = pool[start];
            pool[start] = tempProc;
            while ((pool[start]->start) > 0) {
                //adicionar sleep aqui, acorda na int.
            }

            //retorna se precisa repetir novamente ou n�o
            if (pool[start]->function() == REPETIR) {
                kernelAddProc(pool[start]);
            }
            //pr�xima fun��o
            start = (start + 1) % SLOT_SIZE;
        }
    }
}

char kernelAddProc(process *func) {
    //para poder adicionar um processo tem que existir espaco
    //o fim nunca pode coincidir com o inicio
    if (((end + 1) % SLOT_SIZE) != start) {//se incrementar nessa condicao fim vai ficar igual a ini
        //adiciona o novo processo e agenda para executar j�
        func->start += func->period;
        pool[end] = func;

        end = (end + 1) % SLOT_SIZE;
        return FIM_OK; //sucesso
    }
    return FIM_FALHA; //falha
}

void kernelClock(void) {
    unsigned char i;
    i = start;
    while (i != end) {
        if ((pool[i]->start)>(MIN_INT)) {
            pool[i]->start--;
        }
        i = (i + 1) % SLOT_SIZE;
    }
}