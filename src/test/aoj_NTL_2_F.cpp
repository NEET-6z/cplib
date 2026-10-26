// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_2_F

#include "../math/modint.hpp"
#include "../math/convolution.hpp"

using mint=modint<>;
int main(){
    string S, T;cin>>S>>T;
    bool f=0;
    if(S[0]=='-') f^=1, S.erase(S.begin());
    if(T[0]=='-') f^=1, T.erase(T.begin());
    if(S=="0"||T=="0"){
        cout<<0<<"\n";
        return 0;
    }
    if(f) cout<<"-";

    int N=S.size(), M=T.size();
    vector<mint> A(N), B(M);
    rep(i, N) A[N-i-1]=S[i]-'0';
    rep(i, M) B[M-i-1]=T[i]-'0';
    vector<mint> C=convolution(A, B);
    vector<int> D;
    rep(i, C.size()) D.push_back(C[i].val());
    rep(i, C.size()){
        long a=D[i]/10;
        D[i]%=10;
        if(a){
            if(i+1==D.size()) D.push_back(0);
            D[i+1]+=a;
        }
    }
    reverse(D.begin(), D.end());
    for(long e:D) cout<<e;
    cout<<"\n";
}

