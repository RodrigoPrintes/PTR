#include "robo_xdet.h"
#include "robo_y.h"

Matrix y_out(Matrix x){
  return robo_y(x);
}