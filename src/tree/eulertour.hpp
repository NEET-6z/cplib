#include "../template.hpp"

pair<vector<int>,vector<int>> ET(vector<vector<int>> G,int root=0){
    vector<int> in(si(G)),out(si(G));
    int now=0;
    auto dfs=[&](auto dfs,int v,int p) -> void {
        in[v]=now++;
        for(int e: G[v])
            if(e!=p) dfs(dfs,e,v);
        out[v]=now++;
    };
    dfs(dfs,root,-1);
    return make_pair(in,out);
}

pair<vector<int>,vector<int>> vtetv(vector<pair<int,int>> es,int root=0){
    int N=si(es)+1;
    vector<vector<pair<int,int>>> G(N);
    rep(i,N-1) G[es[i].fi].emplace_back(es[i].se,i),G[es[i].se].emplace_back(es[i].fi,i);
    vector<int> etv(N-1);
    vector<int> vte(N);
    auto dfs=[&](auto dfs,int v,int p) -> void {
        for(auto [e,id]: G[v]){
            if(e==p) continue;
            dfs(dfs,e,v);
            vte[e]=id;
            etv[id]=e;
        }
    };
    dfs(dfs,root,-1);
    return make_pair(vte,etv);
}