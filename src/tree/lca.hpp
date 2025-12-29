#include "../template.hpp"

namespace LCA_SPACE {
const int L=18;
vector<int> G[1<<L];
int up[1<<L][L],dep[1<<L];
void dfs(int v=0, int p=-1){
    up[v][0]=p;
    for(int i=1;i<L;i++) up[v][i]=up[up[v][i-1]][i-1];
    for(int u: G[v]) if(u!=p) dep[u]=dep[v]+1,dfs(u,v);
}
int lca(int a, int b){
    if(dep[a]<dep[b]) swap(a,b);
    for(int i=L;i--;) if(dep[a]-(1<<i)>=dep[b]) a=up[a][i];
    if(a==b) return a;
    for(int i=L;i--;) if(up[a][i]!=up[b][i]) a=up[a][i], b=up[b][i];
    return up[a][0];
}
}