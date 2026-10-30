// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
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
    ld ans=poly_area(A);
    cout<<setprecision(1)<<ans<<"\n";
}