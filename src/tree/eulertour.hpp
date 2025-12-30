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

template<class Edge> pair<vector<Edge>,vector<int>> vtetv(vector<vector<Edge>> G,int root=0){
    vector<int> etv(si(G)-1);
    vector<Edge> vte(si(G));
    auto dfs=[&](auto dfs,int v,int p) -> void {
        for(Edge e: G[v]){
            if(e.to==p) continue;
            dfs(dfs,e.to,v);
            int to=e.to;
            e.to=p;
            vte[to]=e;
            etv[e.id]=to;
        }
    };
    dfs(dfs,root,-1);
    return make_pair(vte,etv);
}
template<class Edge> vector<vector<int>> Gint(vector<vector<Edge>>& G){
    vector<vector<int>> H(si(G));
    rep(i,si(G)) for(Edge& e: G[i]) H[i].push_back(e.to);
    return H;
}