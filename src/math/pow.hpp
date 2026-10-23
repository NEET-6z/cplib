#pragma once
#include "../template.hpp"

template<class T, integral I>
T pow(T b, I k){
    T r=1;
    for(;k;k>>=1, b*=b) if(k&1) r*=b;
    return r;
}
long mpow(long a, long n, long mod){long r=1;for(;n;n/=2, a=a*a%mod) if(n%2) r=r*a%mod;return r;}
long minv(long a, long mod){return a<=1?a:mod-mod/a*minv(mod%a, mod)%mod;}
