// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0356
// competitive-verifier: ERROR 1e-6
#include "../geometry/poly.hpp"


int main(){
    int N, R;
    cin>>N>>R;

    vector<vector<P>> A(N+1);
    rep(i, N){
        int x, w, h;
        cin>>x>>w>>h;
        A[i]={P(x, 0), P(x+w, 0), P(x+w, h), P(x, h)};
    }
    A[N]={P(-200, -200), P(200, -200), P(200, 0), P(-200, 0)};

    S ok=300;
    S ng=0;
    rep(_, 1000){
        S m=(ok+ng)/2;
        Circle c(P(0, m), R);
        ld wa=0;
        rep(i, N+1) wa+=area(A[i], c);
        if(wa*2<=R*R*PI) ok=m;
        else ng=m;
    }

    cout<<ok<<"\n";
}