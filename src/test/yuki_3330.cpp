#define PROBLEM "https://yukicoder.me/problems/no/3330"

#include "../segtree/segtree.hpp"

template<typename K, class S, S (*op)(S, S), S (*e)()> struct segtree_2d {
    int n;
    vector<segtree<S, op, e>> d;
    vector<K> xs;
    vector<vector<K>> ys;
    vector<pair<K, K>> xp;
    vector<vector<pair<K,K>>> yp;
    segtree_2d() {}
    void add_point(K x, K y) { xp.push_back({x, y});}

    void build() {
        sort(all(xp));
        xp.erase(unique(all(xp)), xp.end());
        n = __bit_ceil(si(xp));
        for(auto [x,y]:xp)xs.push_back(x);
        yp.resize(2 * n);
        ys.resize(2 * n);
        rep(i, si(xp)) {
            yp[n + i] = {make_pair(xp[i].se,xp[i].fi)};
            ys[n + i] = {xp[i].se};
        }
        for(int i = n; --i;) {
            merge(all(yp[i * 2]), all(yp[i * 2 + 1]), back_inserter(yp[i]));
            merge(all(ys[i * 2]), all(ys[i * 2 + 1]), back_inserter(ys[i]));
        }
        d.resize(2 * n);
        for(int i = 1; i < 2 * n; i++) {
            d[i] = segtree<S, op, e>(si(yp[i]));
        }
    }

    void set(K x, K y, S v) {
        auto it = lower_bound(all(xp), make_pair(x, y));
        assert(it != xp.end() && it->fi == x && it->se == y);
        int k = it - xp.begin();
        for(k += n; k; k >>= 1) {
            auto it2 = lower_bound(all(yp[k]), make_pair(y,x));
            assert(it2 != yp[k].end());
            int id = it2 - yp[k].begin();
            d[k].set(id, v);
        }
    }
    S get(K x, K y) {
        auto it = lower_bound(all(xp), make_pair(x, y));
        assert(it != xp.end() && it->fi == x && it->se == y);
        int k = it - xp.begin();
        k += n;
        auto it2 = lower_bound(all(yp[k]), make_pair(y,x));
        assert(it2 != yp[k].end());
        int id = it2 - yp[k].begin();
        return d[k].get(id);
    }
    void apply(K x, K y, S v){
        set(x,y,op(get(x,y),v));
    }

    S range(K lv, K rv, K dv, K uv) {
        if(dv >= uv) return e();
        int l = lower_bound(all(xs), lv) - xs.begin();
        int r = lower_bound(all(xs), rv) - xs.begin();
        S sml = e(), smr = e();
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                int li = lower_bound(all(ys[l]), dv) - ys[l].begin();
                int ri = lower_bound(all(ys[l]), uv) - ys[l].begin();
                sml = op(sml, d[l].prod(li, ri));
                l++;
            }
            if(r & 1) {
                --r;
                int li = lower_bound(all(ys[r]), dv) - ys[r].begin();
                int ri = lower_bound(all(ys[r]), uv) - ys[r].begin();
                smr = op(d[r].prod(li, ri), smr);
            }
        }
        return op(sml, smr);
    }
};

long op(long l, long r){
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
    rep(i,N)cin>>A[i];
    vector<int> P(K),X(K);
    rep(i,K)cin>>P[i]>>X[i],P[i]--;
    vector<array<int,5>> q(Q);
    rep(i,Q){
        rep(j,4)cin>>q[i][j],q[i][j]-=(j%2==0);
        q[i][4]=i;
    }
    sort(all(q),greater<>());

    segtree_2d<int,long,op,e> seg;
    rep(i,K) seg.add_point(P[i], i);
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
                seg.set(P[j], st[P[j]].top().se, 0);
                st[P[j]].pop();
            }
            if(st[P[j]].size()){
                seg.set(P[j], st[P[j]].top().se, st[P[j]].top().fi-X[j]);
            }
            seg.set(P[j], j, X[j]-A[P[j]]);
            st[P[j]].push({X[j],j});
        }
        ans[qi]=seg.range(D,U,-1,R);
    }
    rep(i,Q)cout<<ans[i]<<"\n";
}