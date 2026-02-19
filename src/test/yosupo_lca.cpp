#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../tree/lca.hpp"

int main(){
    int N,Q;
    cin>>N>>Q;
    vector<vector<int>> G(N);
    rep(i,N-1){
        int p;
        cin>>p;
        G[p].push_back(i+1);
    }
    LCA lca(G);
    while(Q--){
        int u,v;
        cin>>u>>v;
        cout<<lca.lca(u,v)<<"\n";
    }
}