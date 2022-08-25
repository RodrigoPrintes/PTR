/*
 * matrix.h
 *
 *  Created on: 29 de jun. de 2022
 *      Author: Luiza Paula && Rodrigo Printes
 */

#include <stdio.h>
#include "matrix.h"
#include "integral.h"
#include <math.h>

static void print_matrix(const char *const name, const Matrix m) {

	printf("%s(%u,%u) = [\n", name, m.nlins, m.ncols);

	for(int i = 0; i < matrix_nlins(m); i++) {
		printf("\t[%4.4f", matrix_value(m, i, 0));
		for(int j = 1; j < matrix_ncols(m); j++) {
			printf(", %4.4f", matrix_value(m, i, j));
		}
		puts("]");
	}
	puts("]");
}

double potencia(double b){
	return b*b;
}
double sin(double x){

    return 0.0;
}
int main(int argc, char **argv) {
    
    printf("Main da Matrix\n");
    Matrix a = matrix_rand(2,1);
    print_matrix("A",a); 
    
    Matrix b = matrix_rand(1,3);
    print_matrix("B",b);
    
    
    Matrix matrix_m =  matrix_mult(a, b);
    print_matrix("A x B",matrix_m);
    
    Matrix matrix_so_esc = matrix_soma_escalar(3,a);
    print_matrix("3 + A",matrix_so_esc);
    
    Matrix matrix_s_esc = matrix_sub_escalar(2,b);
    print_matrix("2 - B",matrix_s_esc);
    
    Matrix c = matrix_rand(2,2);
    print_matrix("C",c); 
    
    Matrix d = matrix_rand(2,2);
    print_matrix("D",d);
    
    Matrix matrix_so =  matrix_soma(c,d);
    print_matrix("C + D",matrix_so);
    
    Matrix matrix_s =  matrix_sub(c,d);
    print_matrix("C - D",matrix_s);
    
    Matrix matrix_m_esc = matrix_mult_escalar(2,c);
    print_matrix("2 x C",matrix_m_esc);
    
    Matrix matrix_d_esc = matrix_div_escalar(2,d);
    print_matrix("D/2",matrix_d_esc);
    
    Matrix e = matrix_rand(3,3);
    print_matrix("E",e);
    
    Matrix matrix_inv =  matrix_inversa(e);
    print_matrix("Matrix inversa de E", matrix_inv);
    
    printf("Calculo do determinante:\n");
    Matrix f = matrix_rand(3,3);
    print_matrix("F",f);
    
    double det = matrix_det(f);
    printf("Determinante de F: %f\n",det);
    
   printf("Determinante de F: %f\n",det);
    
    printf("=====================================\n");

    printf("Teste da integral Integral\nFoi usado uma funcao polinomial de 2 grau x*x com limites de [0:5]\n");
    
    
    FX_ *ptrPow = potencia;


   
    double s2 = integral_Trapezio( 0,  5 ,  ptrPow);
    printf("%f \n" ,s2);

    return 0 ;

}
