#include "../template.hpp"

struct scc_graph {
    int N;
    vector<vector<int>> G,H;
    vector<int> vis;
    stack<int> st;
    scc_graph(int n):N(n),G(N),H(N) {}
    void add_edge(int u,int v){
        G[u].push_back(v);
        H[v].push_back(u);
    }
    void dfs(int v){
        if(vis[v]) return;
        vis[v]=1;
        for(int e: G[v]) dfs(e);
        st.push(v);
    }
    void dfss(int v,vector<int> &V){
        if(vis[v]) return;
        vis[v]=1;
        V.push_back(v);
        for(int e: H[v]){
            dfss(e,V);
        }
    }
    vector<vector<int>> scc(){
        vis.assign(N,0);
        rep(i,N) if(!vis[i]) dfs(i);
        vis.assign(N,0);
        vector<vector<int>> gr;
        while(si(st)){
            int v=st.top();
            st.pop();
            if(vis[v]) continue;
            gr.push_back({});
            dfss(v,gr.back());
        }
        return gr;
    }
};