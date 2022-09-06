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

Matrix robo_ModeloRef(Matrix ref, double t){
    // gera a matrix de entrada ?? reff
    // cospe ym e outra ym_DET
    /*
        *
        * Ym = [ymx ymy]T
        * Ym_det = [y_detmx y_detmy]T
        * 
    */


}