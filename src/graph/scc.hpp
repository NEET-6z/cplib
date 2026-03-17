#include"../template.hpp"

struct scc_graph{
    vector<vector<int>> G,H;
    vector<int> vis;
    stack<int> st;
    int N;
    scc_graph(int n): N(n), G(N),H(N),vis(N,0) {}
    void add_edge(int u, int v){
        G[u].push_back(v);
        H[v].push_back(u);
    }
    void dfs(int v){
        if(vis[v]) return ;
        vis[v]=1;
        for(int e: G[v])dfs(e);
        st.push(v);
    }
    void dfss(int v, vector<int> &V){
        if(vis[v]) return ;
        V.push_back(v);
        for(int e: H[v]){
            dfss(e, V);
        }
    }
    vector<vector<int>> scc(){
        rep(i,N)if(!vis[i])dfs(i);
        fill(all(vis),0);
        vector<vector<int>> gr;
        while(si(st)){
            int v=st.top();
            st.pop();
            if(vis[v]) continue;
            gr.push_back({});
            dfss(v, gr.back());
        }
        return gr;
    }
};