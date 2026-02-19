#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../tree/hld.hpp"
#include "../structure/fenwick_tree.hpp"

int main(){
    int N,Q;
    cin>>N>>Q;
    vector<int> A(N);
    rep(i,N) cin>>A[i];
    vector<vector<int>> G(N);
    rep(i,N-1){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    HLD hld(G);
    fenwick_tree<long> bit(N);
    rep(i,N) bit.add(hld.order[i],A[i]);
    rep(i,Q){
        int t;
        cin>>t;
        if(t==0){
            int p,x;
            cin>>p>>x;
            bit.add(hld.order[p],x);
        }
        else{
            int u,v;
            cin>>u>>v;
            long cur=0;
            for(auto [l,r]: hld.path_decompose(u,v,false)){
                cur+=bit.sum(l,r);
            }
            cout<<cur<<"\n";
        }
    }
}