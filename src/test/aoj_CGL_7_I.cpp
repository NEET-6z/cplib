// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_I
// competitive-verifier: ERROR 1e-6
#include "../geometry/circle.hpp"

int main(){
    Circle a, b;
    cin>>a.o>>a.r>>b.o>>b.r;
    cout<<area(a, b)<<"\n";
}
