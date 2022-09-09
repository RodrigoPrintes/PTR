#include "robo_xdet.h"
#include "robo_y.h"


/*Recebe u da linearização e cospe y e x
-> (xc,yc) posição do centro de massa do robo e teta a sua orientação
*/
Matrix x(double xc, double yc, double teta){
    Matrix x; x.ncols = 1; x.nlins = 3;

    matrix_value(x, 0, 0, xc);
    matrix_value(x, 0, 1, yc);
    matrix_value(x, 0, 2, teta);

    return x;
}
// Matrix integral_xdet(Matrix x, Matrix u )
//??????

/*Entrada do sistema achar um lugar adequedo para colocar
-> implementando aqui por comodidade
-> v = velocidade linear do robo
-> w = velocidade angular do sistema
*/

Matrix u(double v, double w){
    Matrix u ; u.ncols = 1 ; u.nlins  = 3;

    matrix_value(u,0,0,v);
    matrix_value(u,0,1,w);
}

Matrix y(Matrix x){
    /*
        * Cospe a saida
        *
        * 
    */
    return robo_y(x);
}
Matrix x_point(Matrix x, Matrix u){
    return robo_xdet(x,u);
}