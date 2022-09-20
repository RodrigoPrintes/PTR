#include "jitter.h"
#include <stdlib.h>
#include <stdio.h>

#define VALUE(j,i,v)(j.jitterRef[i]= v)


static Jitter jitters;


/// @brief   setJitterModelRef(t, ts1.tv_nsec,tm, &i , T);

void jitter_init(){
   
    jitters.iRef = 0;
    jitters.iModRef = 0;
    jitters.iControl = 0;
    jitters.iLinear = 0;
    jitters.iRobo = 0;
   
}

double *getJitter_Ref(){
   
    return jitters.jitterRef;
   
}

double *getT_ref(){
    return jitters.Tref;
}

double setJitter_Ref(double t, double ts1, double tm,  int *i , double T){
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

double setJitter_ModelRef(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
  
    if(t > 0 ){
        jitters.Tmod[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Tmod[(*i)] ;
        jitters.jitterModRef[(*i)] = jitter( jitters.Tmod[(*i)], T);
       
        jitters.iModRef = (*i);
        (*i)++;
    }
    return tt;

}

double *getJitter_ModRef(){
   
    return jitters.jitterModRef;
   
}

double *getTModref(){
    return jitters.Tmod;
}


double setJitter_Control(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
    if(t > 0 ){
        jitters.Tcontrol[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Tcontrol[(*i)] ;
        jitters.jitterControl[(*i)] = jitter( jitters.Tcontrol[(*i)], T);
       
        jitters.iControl = (*i);
        (*i)++;
    }
    return tt;

}

double *getJitter_Control(){
   
    return jitters.jitterControl;
   
}

double *getT_Control(){
    return jitters.Tcontrol;
}


double setJitter_Linear(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
    if(t > 0 ){
        jitters.Tlinear[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Tlinear[(*i)] ;
        jitters.jitterLinear[(*i)] = jitter( jitters.Tlinear[(*i)], T);
       
        jitters.iLinear = (*i);
        (*i)++;
    }
    return tt;

}

double *getJitter_Linear(){
   
    return jitters.jitterLinear;
   
}

double *getT_Linear(){
    return jitters.Tlinear;
}


double setJitter_Robo(double t, double ts1, double tm,  int *i , double T){
    double tt = 0;
    if(t > 0 ){    

        jitters.Trobo[(*i)] = latencia(ts1, tm);
        tt+=   jitters.Trobo[(*i)] ;
        jitters.jitterRobo[(*i)] = jitter( jitters.Trobo[(*i)], T);
       
        jitters.iRobo = (*i);
        (*i)++;
    }
    return tt;

}

double *getJitter_Robo(){
   
    return jitters.jitterRobo;
   
}

double *getT_Robo(){
    return jitters.Trobo;
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

