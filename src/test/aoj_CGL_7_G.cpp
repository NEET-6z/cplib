// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G
// competitive-verifier: ERROR 1e-5
#include "../geometry/circle.hpp"

int main(){
    Circle a, b;
    cin>>a.o>>a.r>>b.o>>b.r;
    vector<Line> ret=tangent(a, b);
    for(Line l:ret){
        cout<<l.a.real()<<" "<<l.a.imag()<<"\n";
    }
}
