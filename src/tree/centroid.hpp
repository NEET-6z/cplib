//未完成

struct CentroidDecomposition {
    int N;
    vector<vector<int>> G,ch;
    vector<int> sub,par,used,id,cep;
    CentroidDecomposition(vector<vector<int>> G_,int root):N(si(G_)),G(G_),ch(N),sub(N),used(N,0),id(N),cep(N,0){
        dfs_build(root,-1);
        rep(i,N) rep(j,si(ch[i])) id[ch[i][j]]=j;
    }
    void dfs_sz(int v,int p){
        sub[v]=1;
        for(int e: G[v]){
            if(e==p||used[e]) continue;
            dfs_sz(e,v);
            sub[v]+=sub[e];
        }
    }
    int dfs_cent(int v,int p,int n){
        for(int e: G[v]){
            if(e==p||used[e]) continue;
            if(sub[e]>n/2) return dfs_cent(e,v,n);
        }
        return v;
    }
    void dfs_build(int v,int p){
        dfs_sz(v,-1);
        int c=dfs_cent(v,-1,sub[v]);
        par[c]=p;
        if(p!=-1) ch[p].push_back(c);
        used[c]=1;
        for(int e: G[c]){
            if(used[e]) continue;
            build_tree(e,c);
        }
    }

    void dfs_cep(int v){
        for(int e: ch[v]){
            cep[e]=cep[v]+1;
            dfs(dfs,e);
        }
    }
}
