// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
// competitive-verifier: ERROR 1e-6
#include "../geometry/intersect.hpp"

int main(){
    Circle c;
    cin>>c.o>>c.r;
    int Q;
    cin>>Q;
    while(Q--){
        Line l;
        cin>>l.a>>l.b;
        pair<P, P> ret=crosspoint_cl(c, l);
        cout<<ret.first.real()<<" "<<ret.first.imag()<<" ";
        cout<<ret.second.real()<<" "<<ret.second.imag()<<"\n";
    }
}
