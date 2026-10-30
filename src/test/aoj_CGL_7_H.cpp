// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
// competitive-verifier: ERROR 1e-5
#include "../geometry/circle.hpp"

int main(){
    int N, R;
    cin>>N>>R;
    Circle C(P(0, 0), R);
    vector<P> A(N);
    rep(i, N) cin>>A[i];

    cout<<area(A, C)<<"\n";
}
