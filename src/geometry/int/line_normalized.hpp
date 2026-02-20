#include "../../template.hpp"

array<long,3> line_normalized(long sy,long sx,long ty,long tx){
    long a=sy-ty;
    long b=tx-sx;
    long c=-(sx*a+sy*b);
    long g=gcd(gcd(a,b),c);
    if(a<0) g*=-1;
    a/=g,b/=g,c/=g;
    return {a,b,c};
}