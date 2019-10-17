#ifndef __mrp_cone_phase_h__
#define __mrp_cone_phase_h__

#include <math.h>

#define Pi M_PI
#define Pi2 (M_PI*M_PI)
#define Pi3 (M_PI*M_PI*M_PI)

float pdf(float theta; float a; float b){
    if(theta<a)
        return 1;
    if(theta>a+b)
        return 0;
    float c = cos((theta-a)*Pi/(2*b));
    return c*c;
}

// Normalized PDF
float npdf(float theta; float a; float b){
    if(theta<a){
        if(a>=Pi || ((a+b)<Pi && b<=0))
            return 1/(2*Pi - 2*Pi*cos(a));
        if(a+b<Pi){
            return ((b-Pi)*(b+Pi)) / (2*(b-Pi)*Pi*(b+Pi) + Pi3*(cos(a) + cos(a+b)));
        }
        return (b*b - Pi2)/(3*b*b*Pi - 3*Pi3 + Pi3*cos(a) + b*b*Pi*cos(((a-Pi)*Pi)/b));
    }
    if(a==0 && theta<=b && b>0){
        float _cos = cos((Pi*theta)/(2*b));
        return ((b-Pi)*(b+Pi)*_cos*_cos)/(2*b*b*Pi - Pi3 + Pi3*cos(b));
    }
    if( theta <= a+b && (a>=Pi || (a>0 && a+b < Pi && b<=0))) { // seems to be rare 
        return (1 + cos((a*Pi-Pi*theta)/b))/(4*Pi - 4*Pi*cos(a));
    }
    if( theta <= a+b && a>0 && a+b<Pi && b>0){
        float _cos = cos((Pi*(theta-a))/(2*b));
        return ((b-Pi)*(b+Pi)*_cos*_cos) / (2*(b-Pi)*Pi*(b+Pi) +  Pi3*(cos(a) + cos(a+b)));
    }
    if( a > 0 && a < Pi && a + b >= Pi){
        float _cos = cos((Pi*(theta-a))/(2*b));
        return ((b-Pi)*(b+Pi)*_cos*_cos)/(Pi*(3*(b-Pi)*(b+Pi) + Pi2*cos(a) + b*b*cos(((a-Pi)*Pi)/b)));
    }
    if( theta <= a+b ){
        return ((-(b*b)+Pi2)*(1+cos((Pi*(theta-a))/b))) / (-6*b*b*Pi + 4*Pi3 - 2*b*b*Pi*cos(Pi2/b));
    }
    return 0;
}

// CDF of azimuthal part
float cdf_s(float theta; float a; float b){
    if(theta>a+b)
        return 1;
    if(theta<=0)
        return 0;
    if(a>=Pi){    
        float sin_half_th=sin(theta/2);
        return sin_half_th*sin_half_th;
    }
    float b2 = b*b;
    float costh = cos(theta);
    if(theta<=a){
        if(a+b<Pi) {
            return (2*(Pi2 - b2)*(costh - 1))/(Pi2*(cos(a+b) + cos(a)) + 2*(b-Pi)*(b+Pi));
        }else{
            return (2*(Pi-b)*(b+Pi)*(costh - 1))/(b2*cos((Pi*(a-Pi))/b) + Pi2*cos(a) + 3*(b-Pi)*(b+Pi));
        }
    }else{
        float sinth = sin(theta);
        if(a>0){
            if(a+b<Pi) {
                return (b2*costh*(-cos((Pi*(a-theta))/b)) + Pi*b*sinth*sin((Pi*(a-theta))/b) + 
                       Pi2*cos(a) + (Pi-b)*(b+Pi)*(costh - 2))/(Pi2*(cos(a+b) + cos(a)) + 2*(b-Pi)*(b+Pi));
            }
            return (b2*costh*(-cos((Pi*(a-theta))/b)) + Pi*b*sinth*sin((Pi*(a-theta))/b) + 
                   Pi2*cos(a) + (Pi-b)*(b+Pi)*(costh - 2))/(b2*cos((Pi*(a-Pi))/b) + Pi2*cos(a) + 3*(b-Pi)*(b+Pi));

        }
        return (costh*(b2*cos((Pi*theta)/b) + b2 - Pi2) - 2*b2 + Pi*b*sinth*sin((Pi*theta)/b) + Pi2)/(-(2*b2) - Pi2*cos(b) + Pi2);

    }
    return 0.5;
}

// Invert CDF of azimuthal part
float solve_cdf_s(float psi; float a; float b; float eps){
// optimized for increasing function to the right
    if(psi==0) return 0;
    
    float left = 0;
    float right = min(Pi,a+b);
    
    float x=left;
    float target=psi;

    float error = 1;
    int max_steps = 100;
    int step = 0;
    while(step<max_steps){
        step+=1;
        x = (left+right)*0.5;
        float res = cdf_s(x, a, b);
        float deviation = target-res;
        error = abs(deviation);
        if (error<eps) break;     
        if (deviation<0){
            right = x;
        }else{
            left = x;
        }
    }
    
    return x;
}

#endif
