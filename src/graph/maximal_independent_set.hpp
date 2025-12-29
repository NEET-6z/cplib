#pragma once
#include "../template.hpp"
using BS=bitset<40>;
BS maximal_independent_set(vector<BS> g, BS d=0){
    int n=si(g);
    BS ret=0;
    int v=-1;
    int md=-1;
    rep(i, n) if(!d[i]){
        if(g[i].count()<=1){
            v=i;
            break;
        }
        if(chmax(md, (int)g[i].count())){
            v=i;
        }
    }
    if(v==-1) return ret;
    d[v]=1;
    rep(i, n) g[i][v]=0;
    if(g[v].count()>1){
        BS vs=maximal_independent_set(g, d);
        if(ret.count()<vs.count()) ret=vs;
    }
    rep(i, n) if(g[v][i]){
        d[i]=1;
        rep(j, n) g[j][i]=0;
    }
    BS vs=maximal_independent_set(g, d);
    vs[v]=1;
    if(ret.count()<vs.count()) ret=vs;
    return ret;
}
