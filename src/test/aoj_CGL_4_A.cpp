// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
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
    vector<P> B=convex_hull(A, false);
    cout<<B.size()<<"\n";
    for(P& p:B){
        cout<<p.real()<<" "<<p.imag()<<"\n";
    }
}
