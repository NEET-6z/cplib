#pragma once
#include "template.hpp"

template<class S, S (*op)(S, S), S (*e)(), class F, S (*mpp)(F, S),
         F (*cmpo)(F, F), F (*id)()>
struct lazy_segtree {
    lazy_segtree(): lazy_segtree(0) {}
    explicit lazy_segtree(int n): lazy_segtree(vector<S>(n, e())) {}
    explicit lazy_segtree(const vector<S> &v):
        n(__bit_ceil(si(v))),
        log(__countr_zero(n)),
        d(2 * n, e()),
        lz(n, 2 * n) {
        rep(i, si(v)) d[n + i] = v[i];
        for(int i = n; --i;) update(i);
    }
    void set(int p, S x) {
        p += n;
        PUSH(p);
        d[p] = x;
        for(int i = 1; i <= log; i++) update(p >> i);
    }
    S get(int p) {
        p += n;
        PUSH(p);
        return d[p];
    }
    S prod(int l, int r) {
        if(l == r) return e();
        l += n, r += n;
        for(int i = log + 1; --i;) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) sml = op(sml, d[l++]);
            if(r & 1) smr = op(d[--r], smr);
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    void apply(int p, F f) {
        p += n;
        PUSH(p);
        d[p] = mpp(f, d[p]);
        for(int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        if(l == r) return;
        l += n, r += n;

        for(int i = log + 1; --i;) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        int ml = l, mr = r;
        while(l < r) {
            if(l & 1) all_apply(l++, f);
            if(r & 1) all_apply(--r, f);
            l >>= 1, r >>= 1;
        }
        l = ml, r = mr;
        for(int i = 1; i <= log; i++) {
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    template<class G> int max_right(int l, G g) {
        assert(g(e()));
        if(l == n) return n;
        l += n;
        PUSH(l);
        S sm = e();
        do {
            while(~l & 1) l >>= 1;
            if(!g(op(sm, d[l]))) {
                while(l < n) {
                    push(l);
                    l <<= 1;
                    if(g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - n;
            }
            sm = op(sm, d[l]);
            l++;
        } while((l & -l) != l);
        return n;
    }
    template<class G> int min_left(int r, G g) {
        assert(g(e()));
        if(r == 0) return 0;
        r += n;
        PUSH(r - 1);
        S sm = e();
        do {
            r--;
            while(r > 1 && r & 1) r >>= 1;
            if(!g(op(d[r], sm))) {
                while(r < n) {
                    push(r);
                    r = (2 * r + 1);
                    if(g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - n;
            }
            sm = op(d[r], sm);
        } while((r & -r) != r);
        return 0;
    }
private:
    int n, log;
    vector<S> d;
    vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mpp(f, d[k]);
        if(k < n) lz[k] = cmpo(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
    void PUSH(int k) {
        for(int i = log + 1; --i;) push(k >> i);
    }
};
