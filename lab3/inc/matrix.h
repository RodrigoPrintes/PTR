/*
    A biblioteca Matrix
*/

#define MAX_NROWS 5
#define MAX_NCOLS 5


struct Matrix {
    int nlins;
    int ncols;
    double values[MAX_NROWS][MAX_NCOLS];
};

Matrix matrix_nul(void);
Matrix matrix_zeros(int nlins, int ncols);
