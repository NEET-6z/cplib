// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
#include "../math/monge/min_plus_convolution.hpp"

int main(){
    int N,M;
    cin>>N>>M;
    vector<int> A(N),B(M);
    rep(i,N)cin>>A[i];
    rep(i,M)cin>>B[i];
    vector<int> C=concave_min_plus_convolution(A,B);
    rep(i,N+M-1)cout<<C[i]<<" \n"[i==N+M-2];
}