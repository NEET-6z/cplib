// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F
// competitive-verifier: ERROR 1e-5
#include "../geometry/circle.hpp"

int main(){
    P p;
    cin>>p;
    Circle a;
    cin>>a.o>>a.r;

    pair<P, P> ret=tangent_points(a, p);
    cout<<ret.first.real()<<" "<<ret.first.imag()<<"\n";
    cout<<ret.second.real()<<" "<<ret.second.imag()<<"\n";
}

