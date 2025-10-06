#include "segtree.hpp"

template<typename K, class S, S (*op)(S, S), S (*e)()> struct segtree_2d {
    int n;
    vector<segtree<S, op, e>> d;
    vector<vector<K>> ys;
    vector<pair<K, K>> ps;
    segtree_2d() {}
    void add_point(K x, K y) { ps.push_back({x, y}); }

    void build() {
        sort(all(ps));
        ps.erase(unique(all(ps)), ps.end());
        n = __bit_ceil(si(ps));
        ys.resize(2 * n);
        rep(i, si(ps)) ys[n + i] = {ps[i].se};
        for(int i = n; --i;) merge(all(ys[i * 2]), all(ys[i * 2 + 1]), back_inserter(ys[i]));

        d.resize(2 * n);
        for(int i = 1; i < 2 * n; i++) {
            d[i] = segtree<S, op, e>(si(ys[i]) + 1);
        }
    }

    void set(K x, K y, S v) {
        auto it = lower_bound(all(ps), make_pair(x, y));
        assert(it != ps.end() && it->fi == x && it->se == y);
        int k = it - ps.begin();
        for(k += n; k; k >>= 1) {
            auto it = lower_bound(all(ys[k]), y);
            assert(it != ys[k].end());
            int id = it - ys[k].begin();
            d[k].set(id, v);
        }
    }
    void add(K x, K y, S v) {
        auto it = lower_bound(all(ps), make_pair(x, y));
        assert(it != ps.end() && it->fi == x && it->se == y);
        int k = it - ps.begin();
        for(k += n; k; k >>= 1) {
            auto it = lower_bound(all(ys[k]), y);
            assert(it != ys[k].end());
            int id = it - ys[k].begin();
            d[k].set(id, op(d[k].get(id), v));
        }
    }

    S range(K lv, K rv, K dv, K uv) {
        if(dv >= uv) return e();
        int l = lower_bound(all(ps), make_pair(lv, -1)) - ps.begin();
        int r = lower_bound(all(ps), make_pair(rv, -1)) - ps.begin();

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