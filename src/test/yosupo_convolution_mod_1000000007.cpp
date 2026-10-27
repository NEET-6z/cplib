// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod_1000000007
#include "../math/convolution_arbitrary.hpp"

int main(){
    int N, M;
    cin>>N>>M;
    vector<long> A(N), B(M);
    rep(i, N) cin>>A[i];
    rep(i, M) cin>>B[i];
    vector<long> C=convolution_arbitrary(A, B, 1000000007);
    rep(i, N+M-1) cout<<C[i]<<" \n"[i+1==N+M-1];
}