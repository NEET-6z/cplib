// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C
// competitive-verifier: ERROR 1e-6
#include "../geometry/circle.hpp"


int main(){
    P a, b, c;
    cin>>a>>b>>c;
    Circle d=circumcircle(a, b, c);
    cout<<d.o.real()<<" "<<d.o.imag()<<" "<<d.r<<"\n";
}