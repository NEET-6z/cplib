#include "../template.hpp"

using S=long double;
using ld = long double;
using P = complex<ld>;
const ld EPS = 1e-12;
const ld PI = acos(-1.0L);

istream& operator>>(istream& is, complex<S>& p) {
    S x,y;is>>x>>y;
    p=complex<S>(x, y);
    return is;
}
S sqr(S a){return a*a;}
int sign(S a){return a>0?1:a<0?-1:0;}
bool eq(S a,S b){return abs(a-b)<=EPS;}
S dot(P a, P b) { return (conj(a) * b).real(); }
S cross(P a, P b) { return (conj(a) * b).imag(); }
P rotate(P p, ld r) { return p * polar(ld(1), r); }  // P(cos(r),sin(r))*p
int sign(ld r) {
    if(EPS < r) return 1;
    if(r < -EPS) return -1;
    return 0;
}
bool eq(ld a, ld b) { return (sign(a - b) == 0); }

int ccw(P b, P c){
    if(cross(b, c) > EPS) return 1;  // counter-clockwise(反時計)
    if(cross(b, c) < -EPS) return -1;  // clockwise(時計)
    if(dot(b, c) < -EPS) return 2;  // c-a-b
    if(norm(b) < norm(c)) return -2;  // a-b-c
    return 0;  // a=c=b
}

int ccw(P a, P b, P c) {
    b-=a;c-=a;
    return ccw(b, c);
}

P unitvector(P a) { return a / abs(a); }
P normalvector(P a) { return a * P(0, 1); }  //90度回転　法線ベクトル
ld radtodeg(ld rad) { return rad * 180 / PI; }
ld degtorad(ld deg) { return deg * PI / 180; }
ld angle(P a, P b) { return atan2l(cross(a, b), dot(a, b)); }  //aからbへの角度rad(=b/a)

// ld arg(const P&p){return atan2l(p.imag(), p.real());}

bool operator<(P a, P b) {
    if(sign(a.real() - b.real())) return sign(a.real() - b.real()) < 0;
    return sign(a.imag() - b.imag()) < 0;
}

int argtype(P p) {
    if(abs(p) == 0) return 0;
    if(p.imag() > 0 || (p.imag() == 0 && p.real() > 0)) return 1;
    return 2;
}
bool arglt(P a, P b) {
    if(argtype(a) != argtype(b)) return argtype(a) < argtype(b);
    S c = cross(a, b);
    if(abs(c) > EPS) return c > EPS;
    return norm(a) < norm(b);
}
bool arglt_direct(const P &p, const P &q) {
    return (abs(arg(p) - arg(q)) > EPS ? arg(p) < arg(q) : norm(p) < norm(q));
}

struct Line {
    P a, b;
    Line(P a=P(), P b=P()): a(a), b(b) {}
    Line(ld A, ld B, ld C) {  // Ax + By = C
        if(eq(A, 0)) a = P(0, C / B), b = P(1, C / B);
        else if(eq(B, 0)) b = P(C / A, 0), b = P(C / A, 1);
        else a = P(0, C / B), b = P(C / A, 0);
    }
};
struct Circle {
    P o;
    S r;
    Circle(const P& o=P(),const S& r=0):o(o),r(r){}
};

P vec(Line s){return s.b-s.a;}
bool point_on_segment(Line &l, P &p) {
    P v = l.b - l.a;
    return dot(p - l.a, v) > -EPS && dot(p - l.b, v) < EPS;
}
P projection(const Line &s, const P &p) {
    P v = s.b - s.a;
    return s.a + v * dot(p - s.a, v) / norm(v);
}
P reflection(const Line &l, const P &p) { return projection(l, p) * S(2) - p; }