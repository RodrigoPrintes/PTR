#include <math.h>
#include "matrix.h"

double x_ref(double t){
    if( t < 0 && t > 4*M_PI)
        return 0;   

    else if(t>=0 && t < 2*M_PI)
        return 0.5 - 0.5*cos(t);

    else    
        return -0.5+cos(t) ;
}

double y_ref(double t){

    if( t < 0 && t > 4*M_PI)
        return 0;  

    else if(t>=0 && t < 2*M_PI)
        return 0.5*sin(t);

    else    
        return -0.5*sin(t) ;
}
Matrix robo_ref(double t){
    Matrix ref;
    ref.ncols = 2;
    ref.nlins = 1;

    matrix_value(ref,0,0, x_ref(t));
    matrix_value(ref,0,1, y_ref(t));
    return matrix_transposta(ref);

}

Matrix robo_ModeloRef(Matrix ref, double t, double alpha1, double alpha2, Matrix Ym){
  
    Matrix ym_det; ym_det.ncols = 2; ym_det.nlins  = 1;

    matrix_value(ym_det, 0, 0, alpha1*(matrix_getValue(ref,0,0)-matrix_getValue(Ym,0,0)));
    matrix_value(ym_det, 0, 1, alpha2*(matrix_getValue(ref,0,1)-matrix_getValue(Ym,0,1)));

    return matrix_transposta(ym_det); 
}

Matrix robo_ym(Matrix ym_det, double limInf, double limSup){

   return matrix_integral(ym_det,limInf,limSup);
}



