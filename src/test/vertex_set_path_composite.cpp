#include "../math/modint.hpp"
#include "../segtree/segtree.hpp"
#include "../tree/hld.hpp"

using mint=modint<>;

struct S {
    pair<mint,mint> l,r;
    S(int a=1,int b=0){
        l.fi=r.fi=a;
        l.se=r.se=b;
    }
};
S op(S l,S r){
    S s;
    s.l.fi=l.l.fi*r.l.fi;
    s.l.se=l.l.se*r.l.fi+r.l.se;
    s.r.fi=l.r.fi*r.r.fi;
    s.r.se=r.r.se*l.r.fi+l.r.se;
    return s;
}
S e(){
    return {1,0};
}

int main(){
    int N,Q;
    cin>>N>>Q;
    vector<int> A(N),B(N);
    rep(i,N) cin>>A[i]>>B[i];
    vector<vector<int>> G(N);
    rep(i,N-1){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    segtree<S,op,e> seg(N);
    HLD hld(G);
    rep(i,N) seg.set(hld.order[i],S(A[i],B[i]));
    while(Q--){
        int t;
        cin>>t;
        if(t==0){
            int p,c,d;
            cin>>p>>c>>d;
            seg.set(hld.order[p],S(c,d));
        }
        else{
            int u,v,x;
            cin>>u>>v>>x;
            int l=hld.lca(u,v);

            S s=seg.get(hld.order[l]);
            for(auto [l,r]:hld.up_decompose(u,l)|views::reverse){
                s=op(s,seg.prod(l,r));
            }
            swap(s.l,s.r);
            for(auto [l,r]:hld.up_decompose(v,l)|views::reverse){
                s=op(s,seg.prod(l,r));
            }
            cout<<s.l.fi*x+s.l.se<<"\n";
        }
    }
}
