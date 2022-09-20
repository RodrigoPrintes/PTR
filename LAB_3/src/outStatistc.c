#include "outStatistic.h"
#include <stdio.h>
#include <string.h>

#include <stdlib.h> 
#include <math.h>
#include "jitter.h"

double media(double *v, double T){
    double s = 0;

    for(int i = 0; i < tMax /T;i++)
        s += v[i];
    

    return (s/(tMax/T));
}

double media_max_or_min(double *v,double T, int m){
    
    double min = v[0];
    double max = v[0];

    for(int i = 0; i < (tMax/T-1); i++){
        if(min > v[i])
            min = v[i];
        
        if(max < v[i])
            max = v[i];
        
    }
    if(m == 0)
        return min;

    else
        return max;
    
}

double variancia_or_desvioP(double *v,double T, int m){
    double var = 0;
    double m_v = media(v,T);

    for(int i = 1; i < tMax/T;i++)
        var += pow((v[i]-m_v),2);
    
    var = var/(tMax/T);

    if(m == 0)
        return var;
    else
        return sqrt(var);
}


void metrica(){

    double mediaJRef, mediaTRef, mediaJMRef,mediaTMRef, mediaJCtrl,mediaTCtrl,mediaJLin, mediaTLin, mediaJRob,mediaTRob,
     varJRef, varTRef, varJMRef, varTMRef, varJCtrl, varTCtrl, varJLin, varTLin, varJRob, varTRob,
     desvpJRef,desvpTRef, desvpJMRef, desvpTMRef,desvpJCtrl,desvpTCtrl, desvpJLin, desvpTLin, desvpJRob, desvpTRob,
     maxJRef, maxTRef, maxJMRef, maxTMRef, maxJCtrl, maxTCtrl, maxJLin, maxTLin, maxJRob, maxTRob,
     minJRef, minTRef, minJMRef, minTMRef, minJCtrl, minTCtrl, minJLin, minTLin, minJRob, minTRob;

    mediaJRef = media( getJitter_Ref(), 50); varJRef = variancia_or_desvioP( getJitter_Ref(), 50, 0); desvpJRef = variancia_or_desvioP( getJitter_Ref(), 50, 1); 
    maxJRef = media_max_or_min( getJitter_Ref(), 50, 1); minJRef =  media_max_or_min(getJitter_Ref(), 50, 0);
    mediaTRef = media(getT_ref(), 50); varTRef = variancia_or_desvioP(getT_ref(), 50, 0); desvpTRef = variancia_or_desvioP(getT_ref(), 50, 1); 
    maxTRef = media_max_or_min(getT_ref(), 50, 1); minTRef =  media_max_or_min(getT_ref(), 50, 0);

    mediaJMRef = media(getJitter_ModRef(), 30); varJMRef = variancia_or_desvioP(getJitter_ModRef(), 30, 0); desvpJMRef = variancia_or_desvioP(getJitter_ModRef(), 30, 1); 
    maxJMRef = media_max_or_min(getJitter_ModRef(), 30, 1);minJMRef =  media_max_or_min(getJitter_ModRef(), 30, 0);
    mediaTMRef = media(getTModref(), 30); varTMRef = variancia_or_desvioP(getTModref(), 30, 0); desvpTMRef = variancia_or_desvioP(getTModref(), 30, 1); 
    maxTMRef = media_max_or_min(getTModref(), 30, 1);minTMRef =  media_max_or_min(getTModref(), 30, 0);

    mediaJCtrl = media(getJitter_Control(), 30); varJCtrl = variancia_or_desvioP(getJitter_Control(), 30, 0); desvpJCtrl = variancia_or_desvioP(getJitter_Control(), 30, 1); 
    maxJCtrl = media_max_or_min(getJitter_Control(), 30, 1); minJCtrl =  media_max_or_min(getJitter_Control(), 30, 0);
    mediaTCtrl = media(getT_Control(), 30); varTCtrl = variancia_or_desvioP(getT_Control(), 30, 0); desvpTCtrl = variancia_or_desvioP(getT_Control(), 30, 1); 
    maxTCtrl = media_max_or_min(getT_Control(), 30, 1); minTCtrl =  media_max_or_min(getT_Control(), 30, 0);

    mediaJLin = media(getJitter_Linear(), 20); varJLin = variancia_or_desvioP(getJitter_Linear(), 20, 0); desvpJLin = variancia_or_desvioP(getJitter_Linear(), 20, 1); 
    maxJLin = media_max_or_min(getJitter_Linear(), 20, 1); minJLin =  media_max_or_min(getJitter_Linear(), 20, 0);
    mediaTLin = media(getT_Linear(), 20); varTLin = variancia_or_desvioP(getT_Linear(), 20, 0); desvpTLin = variancia_or_desvioP(getT_Linear(), 20, 1); 
    maxTLin = media_max_or_min(getT_Linear(), 20, 1); minTLin =  media_max_or_min(getT_Linear(), 20, 0);

    mediaJRob = media(getJitter_Robo(), 10); varJRob = variancia_or_desvioP(getJitter_Robo(), 10, 0); desvpJRob = variancia_or_desvioP(getJitter_Robo(), 10, 1); 
    maxJRob = media_max_or_min(getJitter_Robo(), 10, 1); minJRob =  media_max_or_min(getJitter_Robo(), 10, 0);
    mediaTRob = media(getT_Robo(), 10); varTRob = variancia_or_desvioP(getT_Robo(), 10, 0); desvpTRob = variancia_or_desvioP(getT_Robo(), 10, 1); 
    maxTRob = media_max_or_min(getT_Robo(), 10, 1); minTRob =  media_max_or_min(getT_Robo(), 10, 0);


    FILE *pfileS;

    pfileS = fopen("estatistic.txt","wt");

    fprintf(pfileS,"\tJRef\tJMRef\tJCtrl\tJLin\tJRob\n");
    fprintf(pfileS,"Médias: %lf\t%lf\t%lf\t%lf\t%lf\n",mediaJRef,mediaJMRef,mediaJCtrl,mediaJLin,mediaJRob);
    fprintf(pfileS,"Variancias: %f\t%f\t%f\t%f\t%f\n",varJRef,varJMRef,varJCtrl,varJLin,varJRob);
    fprintf(pfileS,"DP: %lf\t%lf\t%lf\t%lf\t%lf\n",desvpJRef,desvpJMRef,desvpJCtrl,desvpJLin,desvpJRob);
    fprintf(pfileS,"Máximo: %lf\t%lf\t%lf\t%lf\t%lf\n",maxJRef,maxJMRef,maxJCtrl,maxJLin,maxJRob);
    fprintf(pfileS,"Mínimo: %lf\t%lf\t%lf\t%lf\t%lf\n\n",minJRef,minJMRef,minJCtrl,minJLin,minJRob);
    fprintf(pfileS,"\tTRef\tTMRef\tTCtrl\tTLin\tTRob\n");
    fprintf(pfileS,"Médias: %lf\t%lf\t%lf\t%lf\t%lf\n",mediaTRef,mediaTMRef,mediaTCtrl,mediaTLin,mediaTRob);
    fprintf(pfileS,"Variancias: %lf\t%lf\t%lf\t%lf\t%lf\n",varTRef,varTMRef,varTCtrl,varTLin,varTRob);
    fprintf(pfileS,"DP: %lf\t%lf\t%lf\t%lf\t%lf\n",desvpTRef,desvpTMRef,desvpTCtrl,desvpTLin,desvpTRob);
    fprintf(pfileS,"Máximo: %lf\t%lf\t%lf\t%lf\t%lf\n",maxTRef,maxTMRef,maxTCtrl,maxTLin,maxTRob);
    fprintf(pfileS,"Mínimo: %lf\t%lf\t%lf\t%lf\t%lf\n\n",minTRef,minTMRef,minTCtrl,minTLin,minTRob);
   

    fclose(pfileS);
}