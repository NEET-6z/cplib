// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A
#include "../geometry/circle.hpp"


int main(){
    int a, b, c, d, e, f;
    cin>>a>>b>>c>>d>>e>>f;
    cout<<count_tangent(Circle(P(a, b), c), Circle(P(d, e), f))<<"\n";
}
