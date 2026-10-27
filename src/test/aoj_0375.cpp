// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0375
#include "../geometry/poly.hpp"


int main(){
    P S, G;
    cin>>S>>G;
    int N;
    cin>>N;
    vector<P> A(N);
    rep(i, N) cin>>A[i];

    vector<ld> d(N, 1e9);
    rep(i, N) if(intersect_poly_segment(A, Line(S, A[i]))<=1) d[i]=abs(S-A[i]);
    rep(i, N*2) d[(i+1)%N]=min(d[(i+1)%N], d[i%N]+abs(A[i%N]-A[(i+1)%N]));
    for(int i=N*2;i--;) d[i%N]=min(d[i%N], d[(i+1)%N]+abs(A[i%N]-A[(i+1)%N]));
    ld ans=1e9;
    rep(i, N) if(intersect_poly_segment(A, Line(G, A[i]))<=1) ans=min(ans, d[i]+abs(G-A[i]));
    if(intersect_poly_segment(A, Line(S, G))<=1){
        rep(i, N){
            Line l{A[i], A[(i+1)%N]};
            if(ccw(l.a, l.b, S)!=ccw(l.a, l.b, G)) continue;
            P q=reflection(l, G);
            if(!intersect_ss(Line(S, q), l)) continue;
            ans=min(ans, abs(q-S));
        }
    }
    cout<<fixed<<setprecision(15);
    cout<<ans<<"\n";

}
