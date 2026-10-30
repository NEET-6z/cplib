// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_B
// competitive-verifier: ERROR 1e-6
#include "../geometry/circle.hpp"


int main(){
    int N;
    cin>>N;
    vector<P> A(N);
    rep(i, N) cin>>A[i];

    Circle C=min_ball(A.begin(), A.end());
    cout<<C.o.real()<<" "<<C.o.imag()<<" "<<C.r<<"\n";

}