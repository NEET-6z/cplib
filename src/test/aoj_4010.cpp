#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=4010"
#include "../segtree/persistent_segtree.hpp"

long op(long l, long r){return l+r;}
long e(){return 0l;}

using Seg=persistent_segtree<long, op, e>;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int N, Q;
    cin>>N>>Q;
    vector<long> A(N);ziss
    rep(i, N) cin>>A[i];
    Seg seg(N);
    vector<Seg::Node> root(N, nullptr);
    root[0]=seg.build(A);
    rep(i, N-1) root[i+1]=root[i];
    while(Q--){
        int o;cin>>o;
        if(o==1){
            int x, y;
            cin>>x>>y;
            x--;y--;
            root[y]=root[x];
        }
        if(o==2){
            int x, s, y, t;
            cin>>x>>s>>y>>t;
            x--;s--;y--;t--;
            long a=seg.get(root[x], s);
            long b=seg.get(root[y], t);
            root[x]=seg.set(root[x], s, b);
            root[y]=seg.set(root[y], t, a);
        }
        if(o==3){
            int x, s, t;
            cin>>x>>s>>t;
            x--;s--;
            cout<<seg.prod(root[x], s, t)<<"\n";
        }
    }
}