// -----------------------------------------------------------------------
//   kernel.c -> funções para gerenciamento do kernel
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
De acordo com o manual do SDCC (http://sdcc.sourceforge.net/doc/sdccman.html/node183.html):

Não pode ser realizada passagem de parâmetro por valor em struct e unions, somente passagem por referência!
 */

#include "kernel.h"

//variáveis do kernel
static process* pool[SLOT_SIZE]; //'pool' de processos
static volatile unsigned char start; //posição inicial do 'pool' de processos
static volatile unsigned char end; //posição final do 'pool' de processos

//inicializa o kernel em conjunto com a controladora de drivers
char kernelInit(void) {
    BitSet(OSCCON, 7) ; //'Idle mode' em caso de instrução SLEEP
    initCtrDrv();
    start = 0;
    end = 0;
    return OK;
}

//executa os processos do 'pool' de acordo com seus tempos de execução
void kernelLoop(void) {
    unsigned char j;
    unsigned char next;
    process *tempProc;
    for (;;) {
        if (start != end) {
            //Procura a próxima função a ser executada com base no tempo
            j = (start + 1) % SLOT_SIZE;
            next = start;
            while (j != end) {
                if ((pool[j]->start) < (pool[next]->start)) {
                    next = j;
                }
                j = (j + 1) % SLOT_SIZE; //para poder incrementar e ciclar o contador
            }

            //troca e coloca o processo com menor tempo como o próximo
            tempProc = pool[next];
            pool[next] = pool[start];
            pool[start] = tempProc;
            
            while ((pool[start]->start) > 0) {
                //coloca a cpu em modo de economia de energia
                _asm
                    SLEEP
                _endasm ;
            }

            //retorna se precisa repetir novamente ou não
            switch (pool[start]->function()) {
                case REPEAT:
                    kernelAddProc(pool[start]);
                    break;
                case FAIL:
                    break;
                default:;
            }
            //próxima função
            start = (start + 1) % SLOT_SIZE;
        }
    }
}

//adiciona os processos no pool
char kernelAddProc(process *func) {
    //adiciona processo somente se houver espaço livre
    //o fim nunca pode coincidir com o inicio
    if (((end + 1) % SLOT_SIZE) != start) {
        //adiciona o novo processo e agenda para executar imediatamente
        func->start += func->period;
        pool[end] = func;

        end = (end + 1) % SLOT_SIZE;
        return OK; //sucesso
    }
    return FAIL; //falha
}

//atualiza os tempos de execução dos processos
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

