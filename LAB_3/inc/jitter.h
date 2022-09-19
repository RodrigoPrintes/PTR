#ifndef _JITTER_H
#define _JITTER_H

#define jitter(j, i, v) (j.jitterRef[i]=v)
typedef struct Jitter
{
    /* data */
    double jitterRef[400];
    double jitterModRef[400];
    double jitterControl[400];
    double jitterLinear[400];
    double jitterRobo[400];
} Jitter;

#endif