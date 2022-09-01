/*
 * robo_ydet.h
 *
 *  Created on: 30 de agos de 2022
 *      Author: Rodrigo Printes
 */


#ifndef ROBO_YDET_H_
#define ROBO_YDET_H_

#include "matrix.h"
#include <math.h>

Matrix L(Matrix x);
Matrix L_inversa(Matrix x);
Matrix robo_ydet(Matrix x, Matrix u);

#endif /* ROBO_YDET_H_ */