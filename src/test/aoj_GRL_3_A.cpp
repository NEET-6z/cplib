#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=ja"
#include "../graph/lowlink.hpp"

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<int>> G(N);
    rep(i,M){
        int s,t;
        cin>>s>>t;
        G[s].push_back(t);
        G[t].push_back(s);
    }
    LowLink LL(G);
    rep(i,N)if(LL.isa[i])cout<<i<<"\n";
}