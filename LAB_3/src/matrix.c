/*
 * matrix.h
 *
 *  Created on: 29 de jun. de 2022
 *      Author: Luiza Paula && Rodrigo Printes
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include "matrix.h"

Matrix matrix_nul = {.nlins=0, .ncols=0, .values=NULL};

#define VALUES(m, i, j) (m.values[i * m.ncols + j])

void matrix_value(Matrix m, int i, int j, double value) {
   VALUES(m, i, j) = value;
}
double matrix_value_1(Matrix m, int i, int j) {
	return VALUES(m, i, j);
}



Matrix matrix_value_init(unsigned int nlins, unsigned int ncols, double value) {
	Matrix m = matrix_nul;
	m.values = malloc(nlins * ncols * sizeof(double));
	if(m.values) {
		m.nlins = nlins;
		m.ncols = ncols;
		for(int i=0; i<nlins; i++)
			for(int j=0; j<ncols; j++)
				VALUES(m, i, j) = value;
	
   }
    return m;
}

Matrix matrix_zeros(unsigned int nlins, unsigned int ncols) {
	return matrix_value_init(nlins, ncols, 0.0);
}

Matrix matrix_ones(unsigned int nlins, unsigned int ncols) {
	return matrix_value_init(nlins, ncols, 1.0);
}

Matrix matrix_identity(unsigned int nlins, unsigned int ncols) {
	Matrix m = matrix_nul;
	m.values = malloc(nlins * ncols * sizeof(double));
	if(m.values) {
		m.nlins = nlins;
		m.ncols = ncols;
		for(int i=0; i<nlins; i++)
			for(int j=0; j<ncols; j++)
				m.values[i*ncols + j] = (i == j) ? 1.0 : 0.0;
	
    }
     return m;
}
Matrix matrix_rand(int nlins, int ncols){
    Matrix m = matrix_nul;
	m.values = malloc(nlins * ncols * sizeof(double));
	if(m.values) {
		m.nlins = nlins;
		m.ncols = ncols;
		for(int i=0; i<nlins; i++)
			for(int j=0; j<ncols; j++)
				m.values[i*ncols + j] = rand()%100;
	
	
	}
    return m;
}
void matrix_free(Matrix *m) {
	if(m) {
		free(m->values);
		*m = matrix_nul;
	}
}

double matrix_getValue(Matrix m, int i, int j) {
	if(i >= m.nlins || j >= m.ncols)
		return NAN;
	return m.values[i*m.ncols + j];
}

unsigned int matrix_nlins(Matrix m) {
	return m.nlins;
}

unsigned int matrix_ncols(Matrix m) {
	return m.ncols;
}

Matrix matrix_copy(Matrix m) {
	Matrix res;
	res.nlins = m.nlins;
	res.ncols = m.ncols;
	res.values = calloc(res.nlins * res.ncols, sizeof(double));
	if(m.values) {
		for(int i=0; i < res.nlins; i++)
			for(int j=0; j < res.ncols; j++)
				VALUES(res, i, j) = VALUES(m, i, j);
		return m;
	}
	else
		return matrix_nul;
}
Matrix matrix_inversa(Matrix m){
    Matrix ident = matrix_identity(m.nlins,m.ncols);
    double temp=0;
    if(m.nlins == m.ncols){
    for (int k = 0; k < m.nlins; k++){
        temp = VALUES (m,k,k);
        for (int j = 0;j < m.nlins; j++){
            VALUES(m,k,j)/=temp;
            VALUES(ident,k,j)/=temp;
        }
        for (int i=0;i<m.nlins; i++){
            temp = VALUES (m,i,k);
            for (int j=0; j < m.nlins; j++){
                if(i==k) break;
                VALUES (m, i, j) -= VALUES (m, k,j) * temp;
                VALUES (ident, i, j) -= VALUES (ident, k,j) * temp;}
        }
        }
    return ident;
    }else{
        printf("ERRO: O numero de colunas da matriz A deve ser igual ao numero de linhas da matriz B\n");
        return matrix_nul;
    }
}
Matrix matrix_transposta(Matrix m){
    int i,j;
    Matrix res;
	res.nlins = m.ncols;
	res.ncols = m.nlins;
	res.values = calloc(res.nlins * res.ncols, sizeof(double));
	if(m.values) {
	    for(i=0; i < res.nlins; i++){
	        for(j=0; j < res.ncols; j++){
				VALUES(res, i,j) = VALUES(m, j,i);
            }
        }
		return res;
	}
	else
		return matrix_nul;
}

Matrix matrix_mult_escalar(double c, Matrix m) {

	for(int i=0; i < m.nlins; i++)
		for(int j=0; j < m.ncols; j++)
			 m.values[i*m.ncols + j] = c*(m.values[i*m.ncols + j]);
	return m;

}

Matrix matrix_div_escalar(double c, Matrix m) {

		for(int i=0; i < m.nlins; i++)
			for(int j=0; j < m.ncols; j++)
			      m.values[i*m.ncols + j] = (m.values[i*m.ncols + j])/c;
		return m;

}

Matrix matrix_soma_escalar(double c, Matrix m) {

		for(int i=0; i < m.nlins; i++)
			for(int j=0; j < m.ncols; j++)
			      m.values[i*m.ncols + j] = c + (m.values[i*m.ncols + j]);
		return m;

}

Matrix matrix_sub_escalar(double c, Matrix m) {
    	for(int i=0; i < m.nlins; i++)
			for(int j=0; j < m.ncols; j++)
			      m.values[i*m.ncols + j] = (m.values[i*m.ncols + j])-c ;
		return m;
}

Matrix matrix_mult(Matrix a,Matrix b){
    int i,j,k;
    Matrix res;
    res.nlins = a.nlins;
    res.ncols = b.ncols;
    res.values = calloc(res.nlins * res.ncols, sizeof(double));
    if(a.ncols == b.nlins){
        for(i = 0;i<a.nlins;i++){
            for(j = 0;j<b.ncols;j++){
                for(k =0;k<b.nlins;k++){
                    res.values[i*res.ncols + j] += a.values[i*a.ncols + k] * b.values[k*b.ncols + j];
                }
              
            }
        }
      return res;  
    }else{
        printf("ERRO: O numero de colunas da matriz A deve ser igual ao numero de linhas da matriz B\n");
        return matrix_nul;
    }
}
    
    
Matrix matrix_soma(Matrix a, Matrix b){
    Matrix res = matrix_nul;
    res.nlins = a.nlins;
    res.ncols = a.ncols;
    res.values = calloc(res.nlins * res.ncols, sizeof(double));
	if(a.nlins == b.nlins && a.ncols == b.ncols) {
		for(int i=0; i<res.nlins; i++)
			for(int j=0; j<res.ncols; j++)
				res.values[i*res.ncols + j] = a.values[i*a.ncols + j] + b.values[i*b.ncols + j];
	
	    return res;
	}
	else{
        printf("ERRO: As matrizes devem ter o mesmo tamanho, o mesmo número de linhas e colunas\n");
        return matrix_nul;
    }
}
Matrix matrix_sub(Matrix a, Matrix b){
    Matrix res = matrix_nul;
    res.nlins = a.nlins;
    res.ncols = a.ncols;
    res.values = calloc(res.nlins * res.ncols, sizeof(double));
	if(a.nlins == b.nlins && a.ncols == b.ncols) {
		for(int i=0; i<res.nlins; i++)
			for(int j=0; j<res.ncols; j++)
				res.values[i*res.ncols + j] = a.values[i*a.ncols + j] - b.values[i*b.ncols + j];
	
	   
	}
     return res;
}
double matrix_det(Matrix m){

    int i,j,k;
    double temp;
    int count=0;
    double a;
    double pivo= 0;
    if(m.nlins == m.ncols){
        for(i = 0; i < m.nlins - 1; i++)
    {
        if(m.values[i*m.ncols + i]  == 0)
        {
            for(k = i; k < m.nlins; k++)
            {
                if(m.values[k*m.ncols + i]  != 0)
                {
                    for(j = 0; j < m.nlins; j++)
                    {
                        temp = m.values[i*m.ncols + j] ;
                        m.values[i*m.ncols + j] = m.values[k*m.ncols + j] ;
                        m.values[k*m.ncols + j]  = temp;
                    }
                    k = m.nlins;
                }
            }
            count++;
        }

        if(m.values[i*m.ncols + i]  != 0)
        {
            for(k = i + 1; k < m.nlins; k++)
            {
                pivo = -1.0 * m.values[k*m.ncols + i]  /  m.values[i*m.ncols + i] ;
                for(j = i; j < m.nlins; j++)
                {
                    m.values[k*m.ncols + j]  = m.values[k*m.ncols + j]  + (pivo * m.values[i*m.ncols + j] );
                }
            }
        }
    }
    }else{
        printf("ERRO: A matrix deve ser quadrada\n");
        return 0;
    }
    temp = 1.0;
    for(i = 0; i < m.nlins; i++)
        temp *= m.values[i*m.ncols + i] ;
    

    if(count % 2 == 0)
        return temp;
    else{
        a = -1.0 * temp;
        return a ;
    }

    return 0;
}
double fx(double d){return d;}
Matrix matrix_integral(double a, double b, Matrix x){
    /*Intgegração de matrix*/
    FX_ *f_x = fx;
    Matrix m = matrix_nul;
	m.values = malloc(x.nlins * x.ncols * sizeof(double));
	if(m.values) {
		m.nlins = x.nlins;
		m.ncols = x.ncols;
		for(int i=0; i<x.nlins; i++)
			for(int j=0; j<x.ncols; j++){
                   m.values[i*m.ncols + j] = x.values[i*m.ncols + j]*integral_Trapezio(a,b,f_x);}
				
	
    }
        return m;
}
