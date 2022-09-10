/*
    Context Switching header file
    Author: Andre Cavalcante
    Last change: July, 2020
    License: CC BY-SA
*/

#ifndef __CONTEXT_H
#define __CONTEXT_H_H

typedef void(*corrotine_t)(void);

void ctx_init(unsigned int size, corrotine_t corrotines[size]);
void ctx_run();
void ctx_yield(int next);

#endif
