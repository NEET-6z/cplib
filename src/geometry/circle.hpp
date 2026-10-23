#pragma once
#include "intersect.hpp"

// 外接円
Circle circumcircle(P a, P b, P c){
    S A = norm(b-c), B = norm(c-a), C = norm(a-b);
    P o = (A*(B+C-A)*a+B*(C+A-B)*b+C*(A+B-C)*c)/(4*cross(b-a, c-a)*cross(b-a, c-a));
    return {o, abs(o-a)};
}

// 内接円
Circle incircle(P a, P b, P c){
    S A = abs(b-c), B = abs(c-a), C = abs(a-b);
    P o = (A*a+B*b+C*c)/(A+B+C);
    return {o, abs(cross(b-a, c-a))/(A+B+C)};
}

// 傍接円（辺 p2-p3 に対する傍接円）
Circle excircle(P p1, P p2, P p3){
    S d1 = abs(p2-p3);
    S d2 = abs(p3-p1);
    S d3 = abs(p1-p2);
    S sum = -d1+d2+d3;
    P c = (-d1*p1+d2*p2+d3*p3)/sum;
    S area2 = abs(imag(conj(p2-p1)*(p3-p1)));
    S r = area2/sum;

    return {c, r};
}
int count_tangent(const Circle& a, const Circle& b){
    S d = norm(a.o-b.o);
    return sign(d-sqr(a.r+b.r))==0?3:sign(d-sqr(a.r+b.r))==1?4:sign(d-sqr(a.r-b.r))==0?1:sign(d-sqr(a.r-b.r))==1?2:0;
}
bool intersect_cc(const Circle& a, const Circle& b){
    int c = count_tangent(a, b);
    return 1<=c&&c<=3;
}
pair<P, P> tangent_points(Circle c, P p){ //接線の接点
    P v = p-c.o;
    S d2 = norm(v);
    S a = c.r*c.r/d2;
    S b = c.r*sqrtl(d2-c.r*c.r)/d2;
    P t1 = c.o+v*a+normalvector(v)*b;
    P t2 = c.o+v*a-normalvector(v)*b;
    return minmax(t1, t2, [&](P a, P b){return a<b;});
}
vector<Line> tangent(const Circle& a, const Circle& b){ //接線のaに対する接点
    vector<Line>ret;
    S g = abs(a.o-b.o);
    if(eq(g, 0)) return ret;
    P u = (b.o-a.o)/g;
    P v = normalvector(u);
    for(S s:{-1, 1}){
        S h = (a.r+b.r*s)/g;
        if(eq(h*h, 1)) ret.emplace_back(a.o+(h>0?u:-u)*a.r, a.o+(h>0?u:-u)*a.r+v);
        else if(1-h*h>0){
            P U = u*h, V = v*sqrtl(1-h*h);
            ret.emplace_back(a.o+(U+V)*a.r, b.o-(U+V)*b.r*s);
            ret.emplace_back(a.o+(U-V)*a.r, b.o-(U-V)*b.r*s);
        }
    }
    sort(ret.begin(), ret.end(), [&](Line a, Line b){return a.a<b.a;});
    return ret;
}

S area(const vector<P>& p, const Circle& c){
    S ret = 0;
    int n = p.size();
    rep(i, n){
        Line s(p[i], p[(i+1)%n]);
        if(contain_cs(c, s)) ret += cross(s.a-c.o, s.b-c.o);
        else if(!intersect_cs(c, s)){
            S a = arg(s.b-c.o)-arg(s.a-c.o);
            if(a>PI) a -= 2*PI;
            if(a<-PI) a += 2*PI;
            ret += c.r*c.r*a;
        }
        else{
            pair<P, P> x = crosspoint_cs(c, s);
            P tmp[4] = {s.a, x.first, x.second, s.b};
            if(intersect_cs(c, Line(s.a, x.first))==2) swap(tmp[1], tmp[2]);
            for(int j = 0;j<3;j++){
                Line t(tmp[j], tmp[j+1]);
                if(contain_cs(c, t)) ret += cross(t.a-c.o, t.b-c.o);
                else{
                    S a = arg(t.b-c.o)-arg(t.a-c.o);
                    if(a>PI) a -= 2*PI;
                    if(a<-PI) a += 2*PI;
                    ret += c.r*c.r*a;
                }
            }
        }
    }
    return ret/2;
}
S area(const Circle& c){return PI*c.r*c.r;}
S area(const Circle& a, const Circle& b){
    int c = count_tangent(a, b);
    if(c>=3) return 0;
    else if(c<=1) return area(a.r<b.r?a:b);
    else{
        S d = abs(a.o-b.o);
        S ret = 0;
        {
            S alpha = acos((a.r*a.r+d*d-b.r*b.r)/(2*a.r*d));
            ret += alpha*a.r*a.r;
            ret -= sin(alpha*2)*a.r*a.r/2;
        }
        {
            S alpha = acos((b.r*b.r+d*d-a.r*a.r)/(2*b.r*d));
            ret += alpha*b.r*b.r;
            ret -= sin(alpha*2)*b.r*b.r/2;
        }
        return ret;
    }
}


template <class iter>
Circle min_ball(iter left, iter right, int seed = time(0)){ //最小包含円
    const int n = right-left;
    assert(n>=1);
    if(n==1) return {*left, S(0)};

    mt19937 mt(seed);
    shuffle(left, right, mt);

    iter ps = left;
    auto make_circle_3 = [](const P& a, const P& b, const P& c)->Circle {
        S A = norm(b-c), B = norm(c-a), C = norm(a-b), D = cross(b-a, c-a);
        P p = (A*(B+C-A)*a+B*(C+A-B)*b+C*(A+B-C)*c)/(4*D*D);
        S r2 = norm(p-a);
        return Circle{p, r2};
    };

    auto make_circle_2 = [](const P& a, const P& b)->Circle {
        P c = (a+b)/(S)2;
        S r2 = norm(a-c);
        return Circle(c, r2);
    };

    auto in_circle = [](const P& a, const Circle& c)->bool {
        return norm(a-c.o)<=c.r+EPS;
    };

    Circle c = make_circle_2(ps[0], ps[1]);

    for(int i = 2;i<n;++i){
        if(!in_circle(ps[i], c)){
            c = make_circle_2(ps[0], ps[i]);
            for(int j = 1;j<i;++j){
                if(!in_circle(ps[j], c)){
                    c = make_circle_2(ps[i], ps[j]);
                    for(int k = 0;k<j;++k){
                        if(!in_circle(ps[k], c)){
                            c = make_circle_3(ps[i], ps[j], ps[k]);
                        }
                    }
                }
            }
        }
    }
    c.r = sqrt(c.r);
    return c;
}
