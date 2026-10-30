// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
// competitive-verifier: ERROR 1e-6
#include "../geometry/poly.hpp"


int main(){
    int N;
    cin>>N;
    vector<P> A(N);
    rep(i, N){
        ld x, y;
        cin>>x>>y;
        A[i]=P(x, y);
    }
    S md=convex_diamenter(A);
    cout<<sqrtl(md)<<"\n";

}