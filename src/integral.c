/*
 * integral.cc
 *
 *  Created on: 2 de jul de 2022
 *      Author: Luiza Paula && Rodrigo Printes
 *      implementação da ADT Integral
 */

#include "integral.h"

double integral_trapezioSimples(double a, double b , FX_ *ptrFunction ){


	return ( ( ((*ptrFunction)(a))+ ((*ptrFunction)(b)) ) * (b-a) )/2;

}
double integral_Trapezio(double a, double b , FX_ *ptrFunction){
	double s = 0 ;
		for( float i  = a; i < b  ; i+= 0.001){
			s+= integral_trapezioSimples(i, i+0.001,ptrFunction );

		}

	return s;

}

