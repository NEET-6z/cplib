#pragma once
#include "../template.hpp"
pair<bool,vector<int>> is_bipartite(vector<vector<int>> &G){
    int N=si(G);
    vector<int> color(N,-1);
    bool isb=1;
    auto dfs=[&](auto dfs,int v) {
        for(int e: G[v]){
            if(~color[e]){
                isb&=(color[v]!=color[e]);
            }
            else {
                color[e]=color[v]^1;
                dfs(dfs,e);
            }
        }
    } rep(i,N){
        if(~color[i]) continue;
        color[i]=0;
        dfs(dfs,i);
    }
    return {isb,color};
}