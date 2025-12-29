#include "../template.hpp"


using ld=long double;
using P=complex<ld>;
const ld EPS=1e-12;
const ld PI=acos(-1.0L);

ld dot(P a, P b){return (conj(a)*b).real();}
ld cross(P a, P b){return (conj(a)*b).imag();}
P rotate(P p, ld r){
    return p*polar(1.0L, r);
}
int sign(ld r){
    if(EPS<r) return 1;
    if(r<-EPS) return -1;
    return 0;
}
bool eq(ld a, ld b){
    return (sign(a-b)==0);
}

int ccw(P a, P b, P c){
    b-=a;c-=a;
    if (cross(b, c)>EPS) return 1; // counter-clockwise(反時計)
    if (cross(b, c)<-EPS) return -1; // clockwise(時計)
    if (dot(b, c)<-EPS) return 2; // c-a-b
    if (norm(b)<norm(c)) return -2; // a-b-c
    return 0; // a-c-b
}

P unitvector(P a){return a/abs(a);}
P normalvector(P a){return a*P(0, 1);}
ld radtodeg(ld rad){return rad*180/PI;}
ld degtorad(ld deg){return deg*PI/180;}
ld angle(P a, P b){return atan2l(cross(a,b), dot(a,b));}

bool operator<(P a, P b){
    if(sign(a.real()-b.real())) return sign(a.real()-b.real())<0;
    return sign(a.imag()-b.imag())<0;
}
