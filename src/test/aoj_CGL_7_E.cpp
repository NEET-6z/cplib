// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
// competitive-verifier: ERROR 1e-6
#include "../geometry/intersect.hpp"

int main(){
    Circle a, b;
    cin>>a.o>>a.r>>b.o>>b.r;

    pair<P, P> ret=crosspoint_cc(a, b);
    cout<<ret.first.real()<<" "<<ret.first.imag()<<" ";
    cout<<ret.second.real()<<" "<<ret.second.imag()<<"\n";
}