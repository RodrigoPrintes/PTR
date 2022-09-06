/*
 * matrix.h
 *
 *  Created on: 29 de jun. de 2022
 *      Author: Luiza Paula && Rodrigo Printes
 */

/* ADT Matrix */

#ifndef _MATRIX_H
#define _MATRIX_H


/*
	* Definição de parametros e types;
*/
typedef struct Matrix {
	/*
		* nlins - número de linhas;
		* ncols - número de colunas;
		* values[nlins][ncols] - matriz do tipo double
	*/
	unsigned int nlins;
	unsigned int ncols;
	double      *values;
} Matrix;
/*
	* Métodos e seus paramentros e extern/global variaveis ; 
	* Cada Método tem suas entradas e saidas descritas na documentação.
*/
extern Matrix matrix_nul;

Matrix matrix_zeros(unsigned int nlins, unsigned int ncols);
Matrix matrix_value_init(unsigned int nlins, unsigned int ncols, double value);
double matrix_getValue(Matrix m, int i, int j);
Matrix matrix_ones(unsigned int nlins, unsigned int ncols);
Matrix matrix_identity(unsigned int nlins, unsigned int ncols);
Matrix matrix_copy(Matrix m);
Matrix matrix_inversa(Matrix m);
Matrix matrix_mult_escalar(double c, Matrix m);
Matrix matrix_div_escalar(double c, Matrix m);
Matrix matrix_soma_escalar(double c, Matrix m);
Matrix matrix_sub_escalar(double c, Matrix m);
Matrix matrix_transposta(Matrix m);
Matrix matrix_rand(int nlins, int ncols);
Matrix matrix_soma(Matrix a, Matrix b);
Matrix matrix_sub(Matrix a, Matrix b);
Matrix matrix_mult(Matrix a,Matrix b);

void matrix_free(Matrix *m);
void matrix_value(Matrix m, int i, int j, double value);
unsigned int matrix_nlins(Matrix m);
unsigned int matrix_ncols(Matrix m);
double matrix_det(Matrix m);

double matrix_value_1(Matrix m, int i, int j) ;

Matrix matrix_integral(double a, double b, Matrix x){

#endif