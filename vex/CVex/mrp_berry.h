#ifndef __mrp_berry_h__
#define __mrp_berry_h__

#include "mrp_fresnel.h"

float Berry(float NdotH; float a)
{
    float a2 = a*a;
    float a2m1 = a2-1;
    float mu2 = NdotH*NdotH;
    float denom = 1 + a2m1*mu2;

    if(a==1)
        return 1 / PI;

    return a2m1 / (2*PI*log(a)*denom);
}

float smithL_Berry(float c; float a)
{
    if(c==1)
        return 1e-10; //zero
    if(c==0)
        return 1e10; //infinity
    float a2 = a*a;
    float c2 = c*c;

    
    float mu = c/sqrt(1-c2);
    float mu2 = mu*mu;
    
    float q1 = mu*sqrt(1+1/mu2);

    if(a==1){
        return 1/(2*mu2+2*q1*mu);
    }
    
    float q2 = a*sqrt(1+mu2/a2);

    return (q2 - q1 + mu*(-log(q2+mu)+log(q1+mu))) / (2*mu*log(a));
}


float smithG_Berry_Full(vector L; vector V; vector N; float NdotL; float NdotV; float a)
{
    float L_L = smithL_Berry(NdotL, a);
    float L_V = smithL_Berry(NdotV, a);
    float phi = acos( dot( V-N*NdotV, L-N*NdotL ));
    float lambda = 4.41*phi / (4.41*phi+1);
    return 1/(1+max(L_L,L_V)+lambda*min(L_L,L_V));
}

#endif
