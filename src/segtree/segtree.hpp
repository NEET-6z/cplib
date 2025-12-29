#pragma once
#include "../template.hpp"

//https://github.com/KentaroMatsushita/icpc_library
template<class S, S (*op)(S, S), S (*e)()> struct segtree {
    int n;
    vector<S> d;
    segtree():segtree(1){}
    explicit segtree(int n_):segtree(vector<S>(n_, e())){}
    explicit segtree(const vector<S>& a):n(__bit_ceil(a.size())), d(n*2, e()){
        rep(i, si(a)) d[n+i]=a[i];
        for(int i=n;--i;) d[i]=op(d[i*2], d[i*2+1]);
    }
    void set(int i, S x){
        for(d[i+=n]=x;i>>=1;) d[i]=op(d[i*2], d[i*2+1]);
    }
    S get(int i){return d[i+n];}
    S prod(int l, int r){
        S L=e(), R=e();
        for(l+=n, r+=n;l<r;l>>=1, r>>=1){
            if(l&1) L=op(L, d[l++]);
            if(r&1) R=op(d[--r], R);
        }
        return op(L, R);
    }
    template<typename F> int max_right(int l, F f) const {
        if(l==n) return n;
        l+=n;
        S sm=e();
        do {
            while(~l&1) l>>=1;
            if(!f(op(sm, d[l]))){
                while(l<n){
                    l<<=1;
                    if(f(op(sm, d[l]))) sm=op(sm, d[l++]);
                }
                return l-n;
            }
            sm=op(sm, d[l++]);
        } while((l& -l)!=l);
        return n;
    }
    template<typename F> int min_left(int r, F f) const {
        if(!r) return 0;
        r+=n;
        S sm=e();
        do {
            r--;
            while(r>1 and r&1) r>>=1;
            if(!f(op(d[r], sm))){
                while(r<n){
                    r=(2*r+1);
                    if(f(op(d[r], sm))) sm=op(d[r--], sm);
                }
                return r+1-n;
            }
            sm=op(d[r], sm);
        } while((r& -r)!=r);
        return 0;
    }
};

template<class T> using SegtreeFrom=segtree<typename T::S, T::op, T::e>;