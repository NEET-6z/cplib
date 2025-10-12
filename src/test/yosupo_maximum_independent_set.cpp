#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "../graph/maximal_independent_set.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,M;
    cin>>N>>M;
    vector<BS> G(N);
    rep(i,M){
        int u,v;
        cin>>u>>v;
        G[u][v]=G[v][u]=1;
    }
    BS ret=maximal_independent_set(G);
    cout<<ret.count()<<"\n";
    rep(i,N) if(ret[i]) cout<<i<<" ";
    cout<<"\n";
}