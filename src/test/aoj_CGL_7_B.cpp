// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_B
// competitive-verifier: ERROR 1e-6
#include "../geometry/circle.hpp"


int main(){
    P a, b, c;
    cin>>a>>b>>c;
    Circle d=incircle(a, b, c);
    cout<<d.o.real()<<" "<<d.o.imag()<<"\n"<<d.r<<"\n";
}