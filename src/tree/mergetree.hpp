#include "../template.hpp"
#include "../dsu/dsu.hpp"

struct merge_process {
    int n;
    vector<vector<int>> g;
    vector<int> par;
    dsu uf;
    int aux=0;
    merge_process(int n_):n(n_), g(2*n-1), par(2*n-1), uf(n){
        iota(all(par), 0);
    }
    void merge(int a, int b){
        a=uf.leader(a), b=uf.leader(b);
        if(a==b) return;
        g[aux].emplace_back(par[a]);
        g[aux].emplace_back(par[b]);
        par[uf.merge(a, b)]=aux++;
    }
    pair<vector<vector<int>>, vector<int>> build(){
        for(int i=n;i<2*n-1;i++) for(int j: g[i]) par[j]=i;
        return {g, par};
    }
};