#pragma once
#include "./template.hpp"

//伝搬一切しないver
template<class F, F (*id)(), void (*cmpo)(const F&, F&)>
struct dual_segtree {
    dual_segtree(): dual_segtree(0) {}
    explicit dual_segtree(int n_): n(__bit_ceil(n_)),
        d(2 * n, id()) {}
    void apply(int l, int r, F f) {
        if(l == r) return;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l & 1) cmpo(f, d[l++]);
            if(r & 1) cmpo(f, d[--r]);
        }
    }
    F get(int i){
        F r=id();
        for(i+=n;i;i>>=1) cmpo(d[i], r);
        return r;
    }
private:
    int n;
    vector<F> d;
};