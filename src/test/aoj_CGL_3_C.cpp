// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
#include "../geometry/poly.hpp"


int main(){
    int N;
    cin>>N;
    vector<P> A(N);
    rep(i, N){
        int x, y;
        cin>>x>>y;
        A[i]=P(x, y);
    }
    int Q;
    cin>>Q;
    while(Q--){
        int x, y;
        cin>>x>>y;
        cout<<poly_contains(A, P(x, y))<<"\n";
    }
}
