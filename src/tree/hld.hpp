#pragma once
#include "../template.hpp"

struct HLD {
    vector<vector<int>> G;
    int N, T;
    vector<int> par, sub, order, head, dep;
    HLD(vector<vector<int>> G_, int root=0):G(G_), N(si(G)), T(0), par(N), sub(N), order(N), head(N), dep(N){
        dep[root]=0;
        dfs_hld(root, root);
        head[root]=root;
        dfs2(root);
    }
    void dfs_hld(int v, int p){
        par[v]=p;
        sub[v]=1;
        if(auto it=find(all(G[v]), p);it!=G[v].end()) G[v].erase(it);
        for(auto& e: G[v]){
            dep[e]=dep[v]+1;
            dfs_hld(e, v);
            sub[v]+=sub[e];
            if(sub[e]>sub[G[v][0]]) swap(e, G[v][0]);
        }
    }
    void dfs2(int v){
        order[v]=T++;
        for(auto& e: G[v]){
            head[e]=(G[v][0]==e?head[v]:e);
            dfs2(e);
        }
    }
    int lca(int u, int v){
        while(head[u]!=head[v]){
            if(order[u]<order[v]) swap(u, v);
            u=par[head[u]];
        }
        return (order[u]<order[v]?u:v);
    }

    vector<pair<int, int>> path_decompose_commutative(int u, int v, bool edge=1){
        vector<pair<int, int>> ret;
        while(head[u]!=head[v]){
            if(order[u]<order[v]) swap(u, v);
            ret.push_back({order[head[u]], order[u]+1});
            u=par[head[u]];
        }
        if(order[u]>order[v]) swap(u, v);
        ret.push_back({order[u], order[v]+(!edge)});
        return ret;
    }
    vector<pair<int, int>> up_decompose(int u, int l){
        vector<pair<int, int>> ret;
        while(head[u]!=head[l]){
            ret.emplace_back(order[head[u]], order[u]+1);
            u=par[head[u]];
        }
        if(u!=l) ret.emplace_back(order[l]+1, order[u]+1);
        return ret;
    }
    vector<pair<int, int>> path_decompose(int u, int v, bool edge=1){
        //[N:2N) 逆順
        int l=lca(u, v);
        vector<pair<int, int>> L=up_decompose(u, l);
        vector<pair<int, int>> R=up_decompose(v, l);
        reverse(R.begin(), R.end());
        vector<pair<int, int>> ret;
        for(auto&[f, s]:L) ret.emplace_back(2*N-s, 2*N-f);
        if(!edge) ret.emplace_back(order[l], order[l]+1);
        for(auto&[f, s]:R) ret.emplace_back(f, s);
        return ret;
    }
};