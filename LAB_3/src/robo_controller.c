#include "matrix.h"


Matrix controller_v(Matrix y,Matrix Ym, Matrix Ym_det,double alpha1, double alpha2){
     Matrix v;

    v.ncols= 1;
    v.nlins= 2;

    matrix_value(v, 0,0, matrix_getValue(Ym_det,0,0)+alpha1*(matrix_getValue(Ym,0,0) - matrix_getValue(y,0,0)));
    matrix_value(v, 0,0, matrix_getValue(Ym_det,0,1)+alpha2*(matrix_getValue(Ym,0,1) - matrix_getValue(y,0,1)));
    
    return v;
}



   

 
