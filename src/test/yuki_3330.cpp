#define PROBLEM "https://yukicoder.me/problems/no/3330"
#include "../segtree/segtree2d.hpp"

long op(long l,long r){
    return l+r;
}
long e(){
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N,K,Q;
    cin>>N>>K>>Q;
    vector<int> A(N);
    rep(i,N) cin>>A[i];
    vector<int> P(K),X(K);
    rep(i,K) cin>>P[i]>>X[i],P[i]--;
    vector<array<int,5>> q(Q);
    rep(i,Q){
        rep(j,4) cin>>q[i][j],q[i][j]-=(j%2==0);
        q[i][4]=i;
    }
    sort(all(q),greater<>());

    segtree_2d<int,long,op,e> seg;
    rep(i,K) seg.add_point(P[i],i);
    rep(i,N) seg.add_point(i,-1);
    seg.build();
    rep(i,N) seg.set(i,-1,A[i]);

    vector<stack<pair<int,int>>> st(N);
    vector<long> ans(Q);
    int j=K;
    for(auto [L,R,D,U,qi]:q){
        while(j>L){
            j--;
            if(A[P[j]]>=X[j]) continue;
            while(st[P[j]].size()&&X[j]>=st[P[j]].top().fi){
                seg.set(P[j],st[P[j]].top().se,0);
                st[P[j]].pop();
            }
            if(st[P[j]].size()){
                seg.set(P[j],st[P[j]].top().se,st[P[j]].top().fi-X[j]);
            }
            seg.set(P[j],j,X[j]-A[P[j]]);
            st[P[j]].push({X[j],j});
        }
        ans[qi]=seg.range(D,U,-1,R);
    }
    rep(i,Q) cout<<ans[i]<<"\n";
}