#include "../template.hpp"

using ld=long double;
using P=complex<ld>;
const ld EPS=1e-12;
const ld PI=acos(-1.0L);

ld dot(P a,P b){return (conj(a)*b).real();}
ld cross(P a,P b){return (conj(a)*b).imag();}
P rotate(P p,ld r){return p*polar(ld(1),r);}        // P(cos(r),sin(r))*p
int sign(ld r){
    if(EPS<r) return 1;
    if(r<-EPS) return -1;
    return 0;
}
bool eq(ld a,ld b){return (sign(a-b)==0);}

int ccw(P a,P b,P c){
    b-=a;
    c-=a;
    if(cross(b,c)>EPS) return 1;     // counter-clockwise(反時計)
    if(cross(b,c)<-EPS) return -1;     // clockwise(時計)
    if(dot(b,c)<-EPS) return 2;     // c-a-b
    if(norm(b)<norm(c)) return -2;    // a-b-c
    return 0;  // a-c-b
}

P unitvector(P a){return a/abs(a);}
P normalvector(P a){return a*P(0,1);}       //90度回転　法線ベクトル
ld radtodeg(ld rad){return rad*180/PI;}
ld degtorad(ld deg){return deg*PI/180;}
ld angle(P a,P b){return atan2l(cross(a,b),dot(a,b));}         //aからbへの角度(=b/a)

// ld arg(const P&p){return atan2l(p.imag(), p.real());}

bool operator<(P a,P b){
    if(sign(a.real()-b.real())) return sign(a.real()-b.real())<0;
    return sign(a.imag()-b.imag())<0;
}


int argtype(P p){
    if (abs(p)==0) return 0;
    if (p.y>0||(p.y==0&&p.x>0)) return 1;
    return 2;
}
bool arglt(P a, P b){
    if(argtype(a)!=argtype(b))return argtype(a)<argtype(b);
    ld c=cross(a,b);
	if(abs(c)>EPS) return c>EPS;
	return norm(a)<norm(b);
}
bool arglt_direct(const P &p,const P &q){
    return (abs(arg(p)-arg(q))>EPS?arg(p)<arg(q):norm(p)<norm(q));
}

struct Line {
    P p1,p2;
    Line(P p1_=P(),P p2_=P()):p1(p1_),p2(p2_){}
};
bool point_on_segment(P &p,Line &l){
    P v=l.p2-l.p1;
    return dot(p-l.p1,v)>-EPS&&dot(p-l.p2,v)<EPS;
}
P projection(const Line &s,const P &p){
    P v=s.p2-s.p1;
    return s.p1+v*dot(p-s.p1,v)/norm(v);
}
P reflection(const Line &l,const P &p){return projection(l,p)*ld(2)-p;}