#ifndef _JITTER_H
#define _JITTER_H


typedef struct Jitter
{
    /* data */
    double jitterRef[400];
    int iRef ;
    double jitterModRef[400];
    int iModRef ;
    double jitterControl[400];
    int iControl;
    double jitterLinear[400];
    int iLinear;
    double jitterRobo[400];
    int iRobo;
} Jitter;

void jitterRef(int v);
#endif