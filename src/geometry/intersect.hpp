#pragma once
#include "base.hpp"

bool is_orthogonal(Line a, Line b){
    return eq(dot(vec(a),vec(b)),0);
}
bool is_parallel(Line a, Line b){
    return eq(cross(vec(a),vec(b)),0);
} 

bool intersect_sp(Line s,P p){return eq(ccw(s.a,s.b,p),0);}
bool intersect_ss(Line s, Line t) {
    return ccw(s.a,s.b,t.a)*ccw(s.a,s.b,t.b)<=0&&ccw(t.a,t.b,s.a)*ccw(t.a,t.b,s.b)<=0;
}
bool intersect_lp(Line s,P p){return eq(cross(vec(s),p-s.a),0);}
bool intersect_ls(Line s, Line t){
	return sign(cross(vec(s),t.a-s.a))*sign(cross(vec(s),t.b-s.a))<=0;
}
bool intersect_ll(Line s,Line t){return !is_parallel(s,t)||intersect_lp(s,t.a);}
    
bool intersect_sp(Line s,P p){return eq(ccw(s.a,s.b,p),0);}
int intersect_cs(const Circle&c,const Line&s){
	P h=projection(s,c.o);
	S d1=abs(c.o-s.a),d2=abs(c.o-s.b);
	return abs(c.o-h)>c.r+EPS?0
		:d1<c.r-EPS&&d2<c.r-EPS?0
		:(d1<c.r-EPS&&d2>c.r-EPS)||(d1>c.r-EPS&&d2<c.r-EPS)?1
		:intersect_sp(s,h)?eq(abs(c.o-h),c.r)?1:2
		:0;
}
int contain_cp(const Circle&c,const P&p){
	S d=abs(c.o-p);
	return eq(d,c.r)?1:d<c.r?2:0;
}
int contain_cs(const Circle&c,const Line&s){
	S d1=abs(c.o-s.a),d2=abs(c.o-s.b);
	return d1<c.r+EPS&&d2<c.r+EPS?eq(d1,c.r)||eq(d2,c.r)?1:2:0;
}

P crosspoint_ll(Line s, Line t) {
    S d1=cross(vec(s),t.a-s.a);
    S d2=-cross(vec(s),t.b-s.a);
    return t.a+vec(t)*(d1/(d1+d2));
}
pair<P,P> crosspoint_cl(const Circle&c,const Line&s){
	P h=projection(s,c.o);
	P e=vec(s)/abs(vec(s))*sqrt(c.r*c.r-norm(h-c.o));	
	return minmax(h-e,h+e, [](P x, P y){return x < y;});
}
pair<P,P> crosspoint_cs(const Circle&c,const Line&s){
	pair<P,P>p=crosspoint_cl(c,s);
	return intersect_cs(c,s)==2?p
		:intersect_sp(s,p.first)?make_pair(p.first,p.first)
		:make_pair(p.second,p.second);
}
pair<P,P> crosspoint_cc(const Circle&a,const Circle&b){
	S d=abs(a.o-b.o);
	S alpha=acos((a.r*a.r+d*d-b.r*b.r)/(2*a.r*d));
	S theta=arg(b.o-a.o);
	return minmax(a.o+polar(a.r,theta+alpha),a.o+polar(a.r,theta-alpha),[&](P a,P b){return a<b;});
}

S distance_pp(const P&a,const P&b){return abs(a-b);}
S distance_sp(Line&s, P&p){
	return distance_pp(p,
		dot(vec(s),p-s.a)<0?s.a
		:dot(-vec(s),p-s.b)<0?s.b
		:projection(s,p)
	);
}
S distance_ss(Line&s,Line&t){
	return intersect_ss(s,t)?S(0):min({
		distance_sp(s,t.a),distance_sp(s,t.b),
		distance_sp(t,s.a),distance_sp(t,s.b)
	});
}


