#pragma once
#include "base.hpp"

S distance_lp(const Line&, const P&);
S distance_sp(const Line&, const P&);

bool is_orthogonal(const Line& a, const Line& b){
    return eq(dot(vec(a), vec(b)), 0);
}
bool is_parallel(const Line& a, const Line& b){
    return eq(cross(vec(a), vec(b)), 0);
}

bool intersect_lp(const Line& s, const P& p){return eq(cross(vec(s), p-s.a), 0);}
bool intersect_ll(const Line& s, const Line& t){return !is_parallel(s, t)||intersect_lp(s, t.a);}
bool intersect_sp(const Line& s, const P& p){return eq(ccw(s.a, s.b, p), 0);}
int intersect_ss(const Line& s, const Line& t){
    int a=ccw(s.a, s.b, t.a)*ccw(s.a, s.b, t.b);
    int b=ccw(t.a, t.b, s.a)*ccw(t.a, t.b, s.b);
    if(a==-1&&b==-1) return 2; //4本に分かれるか
    if(a<=0&&b<=0) return 1; //触れるか
    return 0;
}
int intersect_ls(const Line& l, const Line& s){
    int a=ccw(l.a, l.b, s.a)*ccw(l.a, l.b, s.b);
    if(a==-1) return 2; //4本に分かれるか
    if(a!=1) return 1; //触れるか
    return 0;
}
bool intersect_cp(const Circle& c, const P& p){return eq(abs(c.o-p), c.r);}
int intersect_cl(const Circle& c, const Line& s){
    S d=distance_lp(s, c.o);
    return sign(c.r-d)+1;
}
int intersect_cs(const Circle& c, const Line& s){
    S dmin=distance_sp(s, c.o);
    S d1=abs(c.o-s.a), d2=abs(c.o-s.b);
    S dmax=max(d1, d2);
    if(dmin>c.r+EPS||dmax<c.r-EPS) return 0;
    if(eq(dmin, c.r)) return 1;
    return (d1>c.r-EPS)+(d2>c.r-EPS); //交点の数
}

int contain_cp(const Circle& c, const P& p){ // 0:外,1:円周上,2:内
    S d=abs(c.o-p);
    return sign(c.r-d)+1;
}
int contain_cs(const Circle& c, const Line& s){ // 0:外,1:円周上,2:内
    S d1=abs(c.o-s.a), d2=abs(c.o-s.b);
    return d1<c.r+EPS&&d2<c.r+EPS?(eq(d1,c.r)||eq(d2,c.r)?1:2):0;
}

P crosspoint_ll(const Line& s, const Line& t){
    assert(!is_parallel(s, t));
    S d1=cross(vec(s), t.a-s.a);
    S d2=-cross(vec(s), t.b-s.a);
    return t.a+vec(t)*(d1/(d1+d2));
}
pair<P, P> crosspoint_cl(const Circle& c, const Line& s){
    P h=projection(s, c.o);
    P e=unitvector(vec(s))*sqrt(max<S>(0, sqr(c.r)-norm(h-c.o)));
    return minmax(h-e, h+e, [](const P& a,const P& b){return a<b;});
}
pair<P, P> crosspoint_cs(const Circle& c, const Line& s){
    auto [p, q]=crosspoint_cl(c, s);
    bool f=eq(distance_sp(s, p), 0), g=eq(distance_sp(s, q), 0);
    return f&&g?make_pair(p, q):f?make_pair(p, p):make_pair(q, q);
}
pair<P, P> crosspoint_cc(const Circle& a, const Circle& b){
    S d=abs(a.o-b.o);
    S alpha=acos((sqr(a.r)+sqr(d)-sqr(b.r))/(2*a.r*d));
    S theta=arg(b.o-a.o);
    return minmax(a.o+polar(a.r,theta+alpha),a.o+polar(a.r,theta-alpha), [](const P& a,const P& b){return a<b;});
}

S distance_lp(const Line& s, const P& p){return abs(p-projection(s, p));}
S distance_sp(const Line& s, const P& p){
    return abs(p-dot(vec(s), p-s.a)<0?s.a:dot(-vec(s), p-s.b)<0?s.b:projection(s, p));
}
S distance_ss(const Line& s, const Line& t){
    return intersect_ss(s, t)?S(0):min({
        distance_sp(s, t.a), distance_sp(s, t.b),
        distance_sp(t, s.a), distance_sp(t, s.b)
    });
}

S distance_ls(const Line& s, const Line& t){
    return intersect_ls(s, t)?S(0):min(distance_lp(s, t.a), distance_lp(s, t.b));
}

S distance_cp(const Circle& c, const P& p){return abs(abs(c.o-p)-c.r);} //円周
S distance_cl(const Circle& c, const Line& s){return max(distance_lp(s, c.o)-c.r, S(0));} //円盤
S distance_cs(const Circle& c, const Line& s){ //円周
    return intersect_cs(c, s)?S(0):contain_cs(c, s)?c.r-max(abs(c.o-s.a), abs(c.o-s.b)):distance_sp(s, c.o)-c.r;
}
S distance_cc(const Circle& a, const Circle& b){
    S d=abs(a.o-b.o);
    return max(d-a.r-b.r, S(0)); //円周上ならmax({...,abs(a.r-b.r)-d})
}