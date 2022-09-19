#include "jitter.h"
#include <stdlib.h>

#define VALUE(j,i,v)(j.jitterRef[i]= v)


static Jitter jitters;

void jitter_init(){
    jitters.iRef = 0;
    jitters.iModRef = 0;
    jitters.iControl = 0;
    jitters.iLinear = 0;
    jitters.iRobo = 0;

    
}

double *getJitterRef(){
   
    return jitters.jitterRef;
   
}

double *getTref(){
    return jitters.Tref;
}

double setJitterRef(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
    if(t > 0 ){
        jitters.Tref[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Tref[(*i)] ;
        jitters.jitterRef[(*i)] = jitter( jitters.Tref[(*i)], T);
       
        jitters.iRef = (*i);
        (*i)++;
    }
    return tt;

}

double setJitterModelRef(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
    if(t > 0 ){
        jitters.Tref[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Tref[(*i)] ;
        jitters.jitterRef[(*i)] = jitter( jitters.Tref[(*i)], T);
       
        jitters.iRef = (*i);
        (*i)++;
    }
    return tt;

}

double *getJitterModRef(){
   
    return jitters.jitterModRef;
   
}

double *getTModref(){
    return jitters.Tmod;
}


double setJitterControl(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
    if(t > 0 ){
        jitters.Tref[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Tref[(*i)] ;
        jitters.jitterRef[(*i)] = jitter( jitters.Tref[(*i)], T);
       
        jitters.iRef = (*i);
        (*i)++;
    }
    return tt;

}

double *getJitterControl(){
   
    return jitters.jitterControl;
   
}

double *getTControl(){
    return jitters.Tcontrol;
}

double latencia (int tempo1, double tempo2){
        double t, resp;

        t  = (double)tempo1/1000000;
        resp= t - tempo2;

        if( resp < 0 )
            resp += 1000;
        
        return resp;
}

double jitter(double resp, double t){
    return resp - t;
}

