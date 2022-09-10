/*
    Implementação de Matrix
*/

#include "matrix.h"

Matrix matrix_nul(void) {
    Matrix m = {0};
    return m;
}

Matrix matrix_zeros(int nlins, int ncols) {
    Matrix m = {0};
    m.nlins = nlins;
    m.ncols = ncols;
    return m;
}

