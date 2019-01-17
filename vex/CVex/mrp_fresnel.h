#ifndef __mrp_fresnel_h__
#define __mrp_fresnel_h__

#include <ggx_utils.h>

float FresnelReflect(float CosThI; float ior) // ior is nu_i/nu_t
{
   float c = abs(CosThI);
   float g2 = 1/(ior*ior) + c*c - 1;
   if(g2<0) // Total internal reflection
       return 1;
   float g = sqrt(g2);
   return clamp(0.5 * sqr(g-c) / sqr(g+c) * (1 + sqr(c*(g+c)-1) / sqr(c*(g-c)+1)),0,1);
}

float SchlickFresnel(float u)
{
    float m = clamp(1.0-u, 0.0, 1.0);
    float m2 = m*m;
    return m2*m2*m; // pow(m,5)
}

#endif
