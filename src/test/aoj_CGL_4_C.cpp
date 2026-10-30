// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
// competitive-verifier: ERROR 1e-5
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
        int a, b, c, d;
        cin>>a>>b>>c>>d;
        Line l(P(a, b), P(c, d));
        vector<P> C=convex_cut(A, l);
        cout<<poly_area(C)<<"\n";
    }
}
