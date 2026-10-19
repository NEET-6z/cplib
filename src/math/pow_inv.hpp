#include "../template.hpp"

long mpow(long a,long n){long r=1;for(;n;n/=2,a=a*a%mod) if(n%2) r=r*a%mod;return r;}
long minv(long a){return a<=1?a:mod-mod/a*minv(mod%a)%mod;}