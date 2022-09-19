#ifndef _JITTER_H
#define _JITTER_H

#define tMax 14000

typedef struct Jitter
{
    /* data */
    double jitterRef[tMax/50 - 1];
    double Tref[tMax/50 - 1];
    int iRef ;

    double jitterModRef[tMax/30 - 1];
    double Tmod[tMax/30 - 1];
    int iModRef ;

    double jitterControl[tMax/30 - 1];
    double Tcontrol[tMax/30 - 1];
    int iControl;

    double jitterLinear[tMax/20 - 1];
    double Tlinear[tMax/20 - 1];
    int iLinear;

    double jitterRobo[tMax/10 - 1];
    double Trobo[tMax/10 - 1];
    int iRobo;
} Jitter;

double jitter(double resp, double t);
double latencia (int tempo1, double tempo2);
double setJitterRef(double t, double ts1, double tm,  int *i , double T);
double *getTref();
double *getJitterRef();
void jitter_init();

#endif