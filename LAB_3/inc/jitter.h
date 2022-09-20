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

void jitter_init();
double *getJitter_Ref();
double *getT_ref();
double setJitter_Ref(double t, double ts1, double tm,  int *i , double T);
double setJitter_ModelRef(double t, double ts1, double tm,  int *i , double T);
double *getJitter_ModRef();
double *getTModref();
double setJitter_Control(double t, double ts1, double tm,  int *i , double T);
double *getJitter_Control();
double *getT_Control();
double setJitter_Linear(double t, double ts1, double tm,  int *i , double T);
double *getJitter_Linear();
double *getT_Linear();
double setJitter_Robo(double t, double ts1, double tm,  int *i , double T);
double *getJitter_Robo();
double *getT_Robo();
double latencia (int tempo1, double tempo2);

double jitter(double resp, double t);



#endif