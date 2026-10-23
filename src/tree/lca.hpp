#include "../template.hpp"
#include "../structure/sparsetable.hpp"

struct LCA {
    vector<vector<int>> G;
    int N;
    vector<int> in, dep, ord;
    SparseTable<pair<int, int>> st;
    LCA(vector<vector<int>> G_, int root=0):G(G_), N(si(G)), in(N), dep(N){
        dep[root]=0;
        dfs(root, -1);
        vector<pair<int, int>> a(si(ord));
        rep(i, si(ord)) a[i]=make_pair(dep[ord[i]], ord[i]);
        st=SparseTable<pair<int, int>>(a);
    }
    void dfs(int v, int p){
        in[v]=si(ord);
        ord.push_back(v);
        for(auto& e: G[v]){
            if(e==p) continue;
            dep[e]=dep[v]+1;
            dfs(e, v);
            ord.push_back(v);
        }
    }
    int lca(int u, int v){
        if(in[u]>in[v]) swap(u, v);
        return st.prod(in[u], in[v]+1).se;
    }
};