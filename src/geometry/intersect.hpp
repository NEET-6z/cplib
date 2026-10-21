#include "base.hpp"

bool intersect_ss(Line &s, Line &t) {
    return ccw(s.a,s.b,t.a)*ccw(s.a,s.b,t.b)<=0&&ccw(t.a,t.b,s.a)*ccw(t.a,t.b,s.b)<=0;
}

P crosspoint_ll(Line&s, Line&t) {
    S d1=cross(vec(s),t.a-s.a);
    S d2=-cross(vec(s),t.b-s.a);
    return t.a+vec(t)*(d1/(d1+d2));
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