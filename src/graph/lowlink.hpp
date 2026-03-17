#include "../template.hpp"

struct LowLink{
    vector<vector<int>> G;
    vector<int> ord,low,vis,isa;    
    int dfs(int v, int p, int t){
        vis[v]=1;
        ord[v]=t++;
        low[v]=ord[v];
        int cnt=0;
        for(int e: G[v]){
            if(!vis[e]){
                cnt++;
                t=dfs(e,v,t);
                chmin(low[v], low[e]);
                if(~p&&ord[v]<=low[e])isa[v]=1;
                if(p==-1&&cnt==2)isa[v]=1;
            }
            else if(e!=p){
                chmin(low[v],ord[e]);
            }
        }
        return t;
    }
    
    LowLink(vector<vector<int>> G): G(G) {
        int N=si(G);
        ord.assign(N,0);
        low.assign(N,0);
        vis.assign(N,0);
        isa.assign(N,0);
        int t=0;
        rep(i,si(G)){
            if(!vis[i]){
                t=dfs(i,-1,t);
            }
        }
    }
    bool is_bridge(int u, int v){
        if(ord[u]>ord[v])swap(u,v);
        return ord[u]<low[v];
    }
};
