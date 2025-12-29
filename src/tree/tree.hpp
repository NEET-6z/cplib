#pragma once
#include "../template.hpp"

struct Tree {
    int N,L;
    vector<vector<int>> G, P;
    vector<int> dep;
    Tree(vector<vector<int>> G_, int root=0):N(si(G_)), G(G_), dep(N){
        L=32-__builtin_clz(N);
        P.assign(L, vector<int>(N));
        dfs(root, -1, 0);
        rep(k,L-1){
            rep(i,N){
                if(P[k][i]==-1) P[k+1][i]=-1;
                else P[k+1][i]=P[k][P[k][i]];
            }
        }
    }
    void dfs(int v, int p, int d){
        dep[v]=d;
        P[0][v]=p;
        for(int e: G[v]) if(e!=p) dfs(e, v, d+1);
    }
    int lca(int u, int v){
        if(dep[u]>dep[v]) swap(u, v);
        rep(k, L) if((dep[v]-dep[u])>>k&1) v=P[k][v];
        if(u==v) return u;
        for(int k=L;k--;)
            if(P[k][u]!=P[k][v]){
                u=P[k][u];
                v=P[k][v];
            }
        return P[0][u];
    }
    int dist(int u, int v){
        int l=lca(u, v);
        return dep[u]+dep[v]-2*dep[l];
    }
    int kth_ancestor(int v, int k){
        for(auto p: P){
            if(k<=0||v==-1) break;
            if(k&1){
                v=p[v];
            }
            k>>=1;
        }
        return v;
    }
    int kth_on_path(int u, int v, int k){
        int l=lca(u, v);
        int du=dep[u]-dep[l];
        int dv=dep[v]-dep[l];
        int dist=du+dv;
        if(k>=dist) return v;
        if(k<=du) return kth_ancestor(u, k);
        int r=k-du;
        return kth_ancestor(v, dv-r);
    };

    int cond_ancestor(int v, function<bool(int)> f){
        for(int k=L;k--;){
            if(f(P[k][v])) v=P[k][v];
        }
        return v;
    }
};
