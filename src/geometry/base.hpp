#pragma once
#include "../template.hpp"

using S=long double;
using ld=long double;
using P=complex<ld>;
const ld EPS=1e-12;
const ld PI=acos(-1.0L);

int sign(S a){return a>EPS?1:a<-EPS?-1:0;}
bool eq(S a, S b){return (sign(a-b)==0);}
S sqr(S a){return a*a;}
ld radtodeg(ld rad){return rad*180/PI;}
ld degtorad(ld deg){return deg*PI/180;}
ld rad2pi(ld rad){
    if(rad<0.0L){
        rad+=2.0L*PI;
    }
    return rad;
}
namespace std {
bool operator<(const P& a, const P& b){
    return a.real()!=b.real()?a.real()<b.real():a.imag()<b.imag();
}
}
struct Circle {
    P o;
    S r;
    Circle(const P& o=P(), const S& r=0):o(o), r(r){}
};
struct Line {
    P a, b;
    Line(const P& a=P(), const P& b=P()):a(a), b(b){}
    Line(ld A, ld B, ld C){// Ax + By = C
        assert(A!=0||B!=0);
        if(eq(A, 0)) a=P(0, C/B), b=P(1, C/B);
        else if(eq(B, 0)) a=P(C/A, 0), b=P(C/A, 1);
        else a=P(0, C/B), b=P(C/A, 0);
    }
};
istream& operator>>(istream& is, complex<S>& p){
    S x, y;is>>x>>y;
    p=complex<S>(x, y);
    return is;
}

S dot(const P& a, const P& b){return (conj(a)*b).real();}
S cross(const P& a, const P& b){return (conj(a)*b).imag();}
P rotate(const P& p, ld r){return p*polar(ld(1), r);} // P(cos(r),sin(r))*p
P vec(const Line& s){return s.b-s.a;}
P unitvector(const P& a){return a/abs(a);}
P normalvector(const P& a){return a*P(0, 1);}//90度回転　法線ベクトル
ld angle(const P& a, const P& b){return atan2l(cross(a, b), dot(a, b));}//aからbへの角度rad(=b/a)
// ld arg(const P&p){return atan2l(p.imag(), p.real());}
S angle_diff(const P& a, const P& b){   //0~π
    S d=fabsl(arg(a)-arg(b));
    return min(d, 2*PI-d);
}
P projection(const Line& s, const P& p){
    P v=vec(s);
    return s.a+v*dot(p-s.a, v)/norm(v);
}
P reflection(const Line& l, const P& p){
    return projection(l, p)*S(2)-p;
}

int ccw(const P& b, const P& c){
    if(cross(b, c)>EPS) return 1;    // counter-clockwise(反時計)
    if(cross(b, c)<-EPS) return -1;    // clockwise(時計)
    if(dot(b, c)<0) return 2;    // c-a-b
    if(norm(b)<norm(c)) return -2;    // a-b-c
    return 0;  // a=c=b
}

int ccw(const P& a, const P& b, const P& c){
    return ccw(b-a, c-a);
}

int argtype(const P& p){
    if(norm(p)==0) return 0;
    if(p.imag()>0||(p.imag()==0&&p.real()>0)) return 1;
    return 2;
}

bool arglt(const P& a, const P& b){
    if(argtype(a)!=argtype(b)) return argtype(a)<argtype(b);
    S c=cross(a, b);
    if(abs(c)>EPS) return c>EPS;
    return norm(a)<norm(b);
}
bool arg_direct(const P& a, const P& b){
    return atan2(a.imag(), a.real())<atan2(b.imag(), b.real());
}