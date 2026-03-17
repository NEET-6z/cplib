#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"
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
    rep(i,N)sort(all(G[i]));
    LowLink LL(G);
    rep(i,N)for(int j: G[i])if(i<j){
        if(LL.is_bridge(i,j)){
            cout<<i<<" "<<j<<"\n";
        }
    }
}