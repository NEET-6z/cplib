#pragma once
#include "template.hpp"

inline vector<int> topological_sort(vector<vector<int>> g){
    vector<int> in(si(g)),ret;
    for(auto &&v: g) for(auto&& e: v) in[e]++;
    queue<int> q;
    rep(i,si(g)) if(in[i]==0) q.push(i);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        ret.push_back(p);
        for(int u:g[p]) if(--in[u]==0) q.push(u);
    }
    return ret;
}