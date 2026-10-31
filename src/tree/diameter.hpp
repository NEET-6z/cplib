#include "../template.hpp"

pair<int, pair<int, int>> get_diameter(vector<vector<int>> G){
    pair<int, pair<int, int>> res;
    int s=0;
    int ma;
    rep(i, 2){
        ma=-1;
        auto dfs=[&](auto dfs, int v, int p, int h)->void {
            if(ma<h){
                ma=h;
                s=v;
            }
            for(int e: G[v]){
                if(e==p) continue;
                dfs(dfs, e, v, h+1);
            }
        };
        dfs(dfs, s, -1, 0);
        res.se.fi=s;
        swap(res.se.fi, res.se.se);
    }
    res.fi=ma;
    return res;
};