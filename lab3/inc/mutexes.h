/*
    Define o monitor para acesso às variáveis
*/

#pragma once

#include "matrix.h"

void mutexes_init();
void mutexes_destroy();

void mutexes_setRef(Matrix  ref);
void mutexes_getRef(Matrix *ref);

void mutexes_setYm(Matrix  ym);
void mutexes_getYm(Matrix *ym);

void mutexes_setYmdot(Matrix  ymdot);
void mutexes_getYmdot(Matrix *ymdot);

void mutexes_setX(Matrix  x);
void mutexes_getX(Matrix *x);

void mutexes_setV(Matrix  v);
void mutexes_getV(Matrix *v);

void mutexes_seU(Matrix  u);
void mutexes_getU(Matrix *u);
