#pragma once
#include "../template.hpp"

using ld=long double;
using S=long;
struct P {
    S x,y;
    P(){}
    P(S x,S y):x(x),y(y){}
    //auto operator<=>(const P& o) const = default;
    bool operator==(const P&o)const {return x==o.x&&y==o.y;}
    bool operator<(const P& o)const {
        if(x!=o.x) return x<o.x;
        return y<o.y;
    }
    P operator-(){
        P res(*this);
        res.x*=-1;
        res.y*=-1;
        return res;
    }
    P operator+(const P& o) const {return P(x+o.x,y+o.y);}
    P& operator+=(const P& o){return *this=*this+o;}
    P operator-(const P& o) const {return P(x-o.x,y-o.y);}
    P& operator-=(const P& o){return *this=*this-o;}
    P operator*(S k) const {return P(x*k,y*k);}
    P& operator*=(S k){return *this=*this*k;}
    P operator/(S k) const {return P(x/k,y/k);}
    P& operator/=(S k){return *this=*this/k;}
    S real()const {return x;}
    S imag()const {return y;}
    friend istream& operator>>(istream& is,P& p){
        return is>>p.x>>p.y;
    }
};
int sign(S a){return a>0?1:a<0?-1:0;}
bool eq(S a,S b){return abs(a-b)==0;}
S sqr(S a){return a*a;}

struct Line {
    P a,b;
    Line(const P& a=P(),const P& b=P()):a(a),b(b){}
};
struct Circle {
    P o;
    S r;
    Circle(const P& o=P(),const S& r=0):o(o),r(r){}
};


S dot(P a,P b){return a.x*b.x+a.y*b.y;}
S cross(P a,P b){return a.x*b.y-a.y*b.x;}
S norm(P a){return dot(a,a);}
ld abs(P a){return sqrt(norm(a));}
P vec(Line s){return s.b-s.a;}
ld arg(const P&p){return atan2l(p.imag(),p.real());}
//P polar(S r,ld theta){return P(r*cosl(theta),r*sinl(theta));}
P conj(P a){return P(a.x,-a.y);}
P normalvector(P a){return P(-a.y,a.x);}
P projection(const Line &s,const P &p){
    P v=vec(s);
    return s.a+v*dot(p-s.a,v)/norm(v); //※float
}
P reflection(const Line &l,const P &p){
    return projection(l,p)*S(2)-p;
}

int ccw(P b,P c){
    if(cross(b,c)>0) return 1;  // counter-clockwise(反時計)
    if(cross(b,c)<0) return -1;  // clockwise(時計)
    if(dot(b,c)<0) return 2;  // c-a-b
    if(norm(b)<norm(c)) return -2; // a-b-c
    return 0; // a=c=b
}
int ccw(P a,P b,P c){
    b-=a;c-=a;
    return ccw(b,c);
}

int argtype(P p){
    if(norm(p)==0) return 0;
    if(p.y>0||(p.y==0&&p.x>0)) return 1;
    return 2;
}

bool arglt(P a,P b){  //xの正軸から反時計回り
    if(argtype(a)!=argtype(b)) return argtype(a)<argtype(b);
    S c=cross(a,b);
    if(c!=0) return c>0;
    return norm(a)<norm(b);
}


P multiply(P a,P b){return P(dot(a,conj(b)),cross(conj(a),b));}
pair<P,S> divide(P a,P b){ //※
    return make_pair(multiply(a,conj(b)),norm(b));
    // return P(dot(b,a), cross(b,a))/norm(b);
}

S parallel_norm(P a,P d){ //※int
    S g=gcd(d.imag(),d.real());
    d/=g;
    if(d.imag()<0) d=-d;
    if(d.real()<0) d=-d;
    return -d.imag()*a.real()+d.real()*a.imag();
}

array<S,3> line_norm(P a,P b){ //※int
    S dy=a.imag()-b.imag();
    S dx=b.real()-a.real();
    S c=-(a.real()*dy+a.imag()*dx);
    S g=gcd(gcd(dy,dx),c);
    if(dy<0) g*=-1;
    dy/=g,dx/=g,c/=g;
    return {dy,dx,c};
}

optional<P> parall_cross(P a1,P a2,P b1,P b2){ //※縦/横
    long x1=a1.x,y1=a1.y;
    long x2=a2.x,y2=a2.y;
    long x3=b1.x,y3=b1.y;
    long x4=b2.x,y4=b2.y;
    auto [ax0,ax1]=minmax(x1,x2);
    auto [ay0,ay1]=minmax(y1,y2);
    auto [bx0,bx1]=minmax(x3,x4);
    auto [by0,by1]=minmax(y3,y4);
    long ix0=max(ax0,bx0),ix1=min(ax1,bx1);
    long iy0=max(ay0,by0),iy1=min(ay1,by1);
    if(ix0>ix1||iy0>iy1) return nullopt;
    return {P(ix0,iy0)};
}