/*
 * integral.h
 *
 *  Created on: 2 de jul de 2022
 *      Author: Luiza Paula && Rodrigo Printes
 */

#ifndef INTEGRAL_H_
#define INTEGRAL_H_

/*
* Definição de parametros e types;
	- FX_ (double x) - função generica do tipo double com um parametro double
	- Fx_trapezio --> função de calculo integral numerico pela tencinca do trapezio composto.
*/

typedef double FX_(double x); 
typedef double Fx_trapezio(double a, double b , FX_ *ptrFunction);


/*
 * Metodo do Trapézio
 * T(fx) = [f(a) - f(b)(b-a)]/2
 * Onde f é a função e 'a', 'b' os limites da integral
 * */

double integral_Trapezio( double a, double b , FX_ *ptrFunction);
double integral_trapezioSimples(double a, double b , FX_ *ptrFunction );
#endif 
/* INTEGRAL_H_ */